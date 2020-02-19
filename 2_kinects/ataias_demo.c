/* ataias_demo.c
 * Program to open two Kinect data at once
 *  [ ] opened the two kinects, the image of one with the depdth of a second 
 *  gcc ataias_demo.c  -o main -lpthread  -lfreenect -lfreenect_sync -lGL -lGLU -lglut -lm
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "libfreenect.h"
#include <math.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <pthread.h>

#define DEV1 0
#define DEV2 1

pthread_t freenect_thread;
volatile int die = 0;

int g_argc;
char **g_argv;

int window;

pthread_mutex_t gl_backbuf_mutex = PTHREAD_MUTEX_INITIALIZER;

// back: owned by libfreenect (implicit for depth)
// mid: owned by callbacks, "latest frame ready"
// front: owned by GL, "currently being drawn"
uint8_t *depth_mid01, *depth_front01;
uint8_t *rgb_back01, *rgb_mid01, *rgb_front01;

GLuint gl_depth_tex;
GLuint gl_rgb_tex;

uint8_t *depth_mid02, *depth_front02;
uint8_t *rgb_back02, *rgb_mid02, *rgb_front02;

//GLuint gl_depth_tex02;
//GLuint gl_rgb_tex02;

int k1_angle = 0;
int k2_angle = 0;

freenect_context *k1_ctx, *k2_ctx;
freenect_device *k1_dev, *k2_dev;
freenect_usb_context *k1_usb_ctx, *k2_usb_ctx;

freenect_video_format requested_format = FREENECT_VIDEO_RGB;
freenect_video_format current_format = FREENECT_VIDEO_RGB;

pthread_cond_t gl_frame_cond = PTHREAD_COND_INITIALIZER;
int got_rgb01 = 0;
int got_depth01 = 0;
int got_rgb02 = 0;
int got_depth02 = 0;

void DrawGLScene()
{
	pthread_mutex_lock(&gl_backbuf_mutex);

	// When using YUV_RGB mode, RGB frames only arrive at 15Hz, so we shouldn't force them to draw in lock-step.
	// However, this is CPU/GPU intensive when we are receiving frames in lockstep.
	if (current_format == FREENECT_VIDEO_YUV_RGB) {
		while (!got_depth01 && !got_rgb01 && !got_depth02 && !got_rgb02) {
			pthread_cond_wait(&gl_frame_cond, &gl_backbuf_mutex);
		}
	} else {
		while ((!got_depth01 || !got_rgb01 || !got_depth02 || !got_depth02) && requested_format != current_format) {
			pthread_cond_wait(&gl_frame_cond, &gl_backbuf_mutex);
		}
	}

	if (requested_format != current_format) {
		pthread_mutex_unlock(&gl_backbuf_mutex);
		return;
	}

	uint8_t *tmp;

	if (got_depth01) {
		tmp = depth_front01;
		depth_front01 = depth_mid01;
		depth_mid01 = tmp;
		got_depth01 = 0;
	}
	if (got_rgb01) {
		tmp = rgb_front01;
		rgb_front01 = rgb_mid01;
		rgb_mid01 = tmp;
		got_rgb01 = 0;
	}

	if (got_depth02) {
		tmp = depth_front02;
		depth_front02 = depth_mid02;
		depth_mid02 = tmp;
		got_depth02 = 0;
	}
	if (got_rgb02) {
		tmp = rgb_front02;
		rgb_front02 = rgb_mid02;
		rgb_mid02 = tmp;
		got_rgb02 = 0;
	}
	pthread_mutex_unlock(&gl_backbuf_mutex);

	glBindTexture(GL_TEXTURE_2D, gl_depth_tex);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 640, 480, 0, GL_RGB, GL_UNSIGNED_BYTE, depth_front02); //aqui eu escolho o que aparece de profundidade!

	glBegin(GL_TRIANGLE_FAN);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glTexCoord2f(0, 0); glVertex3f(0,0,0);
	glTexCoord2f(1, 0); glVertex3f(640,0,0);
	glTexCoord2f(1, 1); glVertex3f(640,480,0);
	glTexCoord2f(0, 1); glVertex3f(0,480,0);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, gl_rgb_tex);
	if (current_format == FREENECT_VIDEO_RGB || current_format == FREENECT_VIDEO_YUV_RGB)
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 640, 480, 0, GL_RGB, GL_UNSIGNED_BYTE, rgb_front01); //aqui eu escolho o que aparece de rgb!
	else
		glTexImage2D(GL_TEXTURE_2D, 0, 1, 640, 480, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, rgb_front01+640*4); //cuidado aqui

	glBegin(GL_TRIANGLE_FAN);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glTexCoord2f(0, 0); glVertex3f(640,0,0);
	glTexCoord2f(1, 0); glVertex3f(1280,0,0);
	glTexCoord2f(1, 1); glVertex3f(1280,480,0);
	glTexCoord2f(0, 1); glVertex3f(640,480,0);
	glEnd();

	glutSwapBuffers();
}

void keyPressed(unsigned char key, int x, int y)
{
	if (key == 27) {
		die = 1;
		pthread_join(freenect_thread, NULL);
		glutDestroyWindow(window);
		free(depth_mid01);
		free(depth_front01);
		free(rgb_back01);
		free(rgb_mid01);
		free(rgb_front01);

		free(depth_mid02);
		free(depth_front02);
		free(rgb_back02);
		free(rgb_mid02);
		free(rgb_front02);

		exit(0);
	}
	if (key == 'w') {
		k1_angle++;
		if (k1_angle > 30) {
			k1_angle = 30;
		}
	}
	if (key == 's') {
		k1_angle = 0;
	}
	if (key == 'f') {
		if (requested_format == FREENECT_VIDEO_IR_8BIT)
			requested_format = FREENECT_VIDEO_RGB;
		else if (requested_format == FREENECT_VIDEO_RGB)
			requested_format = FREENECT_VIDEO_YUV_RGB;
		else
			requested_format = FREENECT_VIDEO_IR_8BIT;
	}
	if (key == 'x') {
		k1_angle--;
		if (k1_angle < -30) {
			k1_angle = -30;
		}
	}

    	if (key == 'e') {
		k2_angle++;
		if (k2_angle > 30) {
			k2_angle = 30;
		}
	}
	if (key == 'd') {
		k2_angle = 0;
	}
    	if (key == 'c') {
		k2_angle--;
		if (k2_angle < -30) {
			k2_angle = -30;
		}
	}

    /*organize essa hist?ria de f_dev... fa?a essas cores serem indepente de kinect para kinect, podendo ser escolhidas arbitrariamente*/
	if (key == '1') {
		freenect_set_led(k1_dev,LED_GREEN);
	}
	if (key == '2') {
		freenect_set_led(k2_dev,LED_RED);
	}
	if (key == '3') {
		freenect_set_led(k1_dev,LED_YELLOW);
	}
	if (key == '4') {
		freenect_set_led(k2_dev,LED_BLINK_GREEN);
	}
	if (key == '5') {
		// 5 is the same as 4
		freenect_set_led(k1_dev,LED_BLINK_GREEN);
	}
	if (key == '6') {
		freenect_set_led(k2_dev,LED_BLINK_RED_YELLOW);
	}
	if (key == '0') {
		freenect_set_led(k1_dev,LED_OFF);
	}
	if (key == '9') {
		freenect_set_led(k2_dev,LED_OFF);
	}
	freenect_set_tilt_degs(k1_dev, k1_angle);
    freenect_set_tilt_degs(k2_dev, k2_angle);
}

void ReSizeGLScene(int Width, int Height)
{
	glViewport(0,0,Width,Height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho (0, 1280, 480, 0, -1.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void InitGL(int Width, int Height)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0);
	glDepthFunc(GL_LESS);
    glDepthMask(GL_FALSE);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
    glDisable(GL_ALPHA_TEST);
    glEnable(GL_TEXTURE_2D);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glShadeModel(GL_FLAT);

	glGenTextures(1, &gl_depth_tex);
	glBindTexture(GL_TEXTURE_2D, gl_depth_tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glGenTextures(1, &gl_rgb_tex);
	glBindTexture(GL_TEXTURE_2D, gl_rgb_tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	ReSizeGLScene(Width, Height);
}

void *gl_threadfunc(void *arg)
{
	printf("GL thread\n");

	glutInit(&g_argc, g_argv);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
	glutInitWindowSize(1280, 480);
	glutInitWindowPosition(0, 0);

	window = glutCreateWindow("LibFreenect");

	glutDisplayFunc(&DrawGLScene);
	glutIdleFunc(&DrawGLScene);
	glutReshapeFunc(&ReSizeGLScene);
	glutKeyboardFunc(&keyPressed);

	InitGL(1280, 480);

	glutMainLoop();

	return NULL;
}

uint16_t t_gamma[2048];

void depth_cb01(freenect_device *dev, void *v_depth, uint32_t timestamp){

	int i;
	uint16_t *depth = (uint16_t*)v_depth;

	pthread_mutex_lock(&gl_backbuf_mutex);
	for (i=0; i<640*480; i++) {
		int pval = t_gamma[depth[i]];
		int lb = pval & 0xff;
			depth_mid01[3*i+0] = 255-lb;
			depth_mid01[3*i+1] = 255-lb;
			depth_mid01[3*i+2] = 255-lb;
	}

	got_depth01++;
	pthread_cond_signal(&gl_frame_cond);
	pthread_mutex_unlock(&gl_backbuf_mutex);
}

void depth_cb02(freenect_device *dev, void *v_depth, uint32_t timestamp){

	int i;
	uint16_t *depth = (uint16_t*)v_depth;

	pthread_mutex_lock(&gl_backbuf_mutex);
	for (i=0; i<640*480; i++) {
		int pval = t_gamma[depth[i]];
		int lb = pval & 0xff;
			depth_mid02[3*i+0] = 255-lb;
			depth_mid02[3*i+1] = 255-lb;
			depth_mid02[3*i+2] = 255-lb;
	}

	got_depth02++;
	pthread_cond_signal(&gl_frame_cond);
	pthread_mutex_unlock(&gl_backbuf_mutex);
}

void rgb_cb01(freenect_device *dev, void *rgb, uint32_t timestamp)
{
	pthread_mutex_lock(&gl_backbuf_mutex);

	// swap buffers
	assert (rgb_back01 == rgb);
	rgb_back01 = rgb_mid01;
	freenect_set_video_buffer(dev, rgb_back01);
	rgb_mid01 = (uint8_t*)rgb;

	got_rgb01++;
	pthread_cond_signal(&gl_frame_cond);
	pthread_mutex_unlock(&gl_backbuf_mutex);
}
void rgb_cb02(freenect_device *dev, void *rgb, uint32_t timestamp)
{
	pthread_mutex_lock(&gl_backbuf_mutex);

	// swap buffers
	assert (rgb_back02 == rgb);
	rgb_back02 = rgb_mid02;
	freenect_set_video_buffer(dev, rgb_back02);
	rgb_mid02 = (uint8_t*)rgb;

	got_rgb02++;
	pthread_cond_signal(&gl_frame_cond);
	pthread_mutex_unlock(&gl_backbuf_mutex);
}

void *freenect_threadfunc(void *arg)
{
//	int accelCount_1 = 0;
//	int accelCount_2 = 0;

	/*Kinect 1*/
	freenect_set_tilt_degs(k1_dev,k1_angle);
	freenect_set_led(k1_dev,LED_RED);
	freenect_set_depth_callback(k1_dev, depth_cb01);
	freenect_set_video_callback(k1_dev, rgb_cb01);
	freenect_set_video_mode(k1_dev, freenect_find_video_mode(FREENECT_RESOLUTION_MEDIUM, current_format));
	freenect_set_depth_mode(k1_dev, freenect_find_depth_mode(FREENECT_RESOLUTION_MEDIUM, FREENECT_DEPTH_11BIT));
	freenect_set_video_buffer(k1_dev, rgb_back01);

	freenect_start_depth(k1_dev);
	freenect_start_video(k1_dev);

	/*Kinect 2*/
	freenect_set_tilt_degs(k2_dev,k2_angle);
	freenect_set_led(k2_dev,LED_RED);
	freenect_set_depth_callback(k2_dev, depth_cb02);
	freenect_set_video_callback(k2_dev, rgb_cb02);
	freenect_set_video_mode(k2_dev, freenect_find_video_mode(FREENECT_RESOLUTION_MEDIUM, current_format));
	freenect_set_depth_mode(k2_dev, freenect_find_depth_mode(FREENECT_RESOLUTION_MEDIUM, FREENECT_DEPTH_11BIT));
	freenect_set_video_buffer(k2_dev, rgb_back02);

	freenect_start_depth(k2_dev);
	freenect_start_video(k2_dev);

	printf("'w'-tilt up, 's'-level, 'x'-tilt down, '0'-'6'-select LED mode, 'f'-video format\n");
	printf("'e'-tilt up, 'd'-level, 'c'-tilt down, '0'-'6'-select LED mode, 'f'-video format\n");

	while (!die && freenect_process_events(k1_ctx) >= 0 && freenect_process_events(k2_ctx)>=0 ) {
		//Throttle the text output

		if (requested_format != current_format) {

			freenect_stop_video(k1_dev);
			freenect_set_video_mode(k1_dev, freenect_find_video_mode(FREENECT_RESOLUTION_MEDIUM, requested_format));
			freenect_start_video(k1_dev);

			freenect_stop_video(k2_dev);
			freenect_set_video_mode(k2_dev, freenect_find_video_mode(FREENECT_RESOLUTION_MEDIUM, requested_format));
			freenect_start_video(k2_dev);

			current_format = requested_format;
		}
	}

	printf("\nshutting down streams...\n");

	freenect_stop_depth(k1_dev);
	freenect_stop_depth(k2_dev);
	freenect_stop_video(k1_dev);
	freenect_stop_video(k2_dev);
	freenect_close_device(k1_dev);
	freenect_close_device(k2_dev);
	freenect_shutdown(k1_ctx);
	freenect_shutdown(k2_ctx);

	printf("-- done!\n");
	return NULL;
}
/*
 * A fun??o main apresentada aqui tem algumas diferen?as em rela??o a mesma que se encontra em glview.c
 * A principal diferen?a ? que l? a fun??o se preocupa com o trabalho para um kinect
 * enquanto aqui existe a cria??o de dois contextos, portanto, para dois kinects
 */
int main(int argc, char **argv){

	int res;

	depth_mid01 = (uint8_t*)malloc(640*480*3);
	depth_front01 = (uint8_t*)malloc(640*480*3);
	rgb_back01 = (uint8_t*)malloc(640*480*3);
	rgb_mid01 = (uint8_t*)malloc(640*480*3);
	rgb_front01 = (uint8_t*)malloc(640*480*3);

	depth_mid02 = (uint8_t*)malloc(640*480*3);
	depth_front02 = (uint8_t*)malloc(640*480*3);
	rgb_back02 = (uint8_t*)malloc(640*480*3);
	rgb_mid02 = (uint8_t*)malloc(640*480*3);
	rgb_front02 = (uint8_t*)malloc(640*480*3);

    printf("Kinect camera test\n");


	int i;
	for (i=0; i<2048; i++) {
		float v = i/2048.0;
		v = powf(v, 3)* 6;
		t_gamma[i] = v*6*256;
	}

	g_argc = argc;
	g_argv = argv;

	if (
        (freenect_init(&k1_ctx, k1_usb_ctx) < 0) ||
        (freenect_init(&k2_ctx, k2_usb_ctx) < 0)
        ) {
		printf("freenect_init() failed\n");
		return 1;
	}

	freenect_set_log_level(k1_ctx, FREENECT_LOG_DEBUG);
    freenect_set_log_level(k2_ctx, FREENECT_LOG_DEBUG);

    /*Al?m de motor e c?mera, tem-se o ?udio do kinect, isto n?o est? sendo considerado aqui.*/
    freenect_select_subdevices(k1_ctx, (freenect_device_flags)(FREENECT_DEVICE_MOTOR | FREENECT_DEVICE_CAMERA));
    freenect_select_subdevices(k2_ctx, (freenect_device_flags)(FREENECT_DEVICE_MOTOR | FREENECT_DEVICE_CAMERA));

    int nr_devices = freenect_num_devices (k1_ctx); /*Suposi??o ? que o n?mero de dispositivos ? a soma dos dois contextos*/
//    nr_devices = nr_devices + freenect_num_devices(k2_ctx);
	printf ("Number of devices found: %d\n", nr_devices);

	if (nr_devices < 1) {
		freenect_shutdown(k1_ctx);
        freenect_shutdown(k2_ctx);
		return 1;
	}

	if (freenect_open_device(k1_ctx, &k1_dev, DEV1) < 0) {
		printf("Could not open device 1\n");
		freenect_shutdown(k1_ctx);
		return 1;
	}

    if (freenect_open_device(k2_ctx, &k2_dev, DEV2) < 0) {
		printf("Could not open device 2\n");
		freenect_shutdown(k2_ctx);
		return 1;
	}

	res = pthread_create(&freenect_thread, NULL, freenect_threadfunc, NULL);
	if (res) {
		printf("pthread_create failed\n");
		freenect_shutdown(k1_ctx);
		freenect_shutdown(k2_ctx);
		return 1;
	}
	gl_threadfunc(NULL);
return(0);
}
