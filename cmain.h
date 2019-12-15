#ifndef CMAIN_H

#ifdef __APPLE__
    #define GL_SILENCE_DEPRECATION 
    #include <GLUT/glut.h>         
#endif
#ifdef __linux__
    #include <GL/glut.h>         
#endif

#include <stdio.h>
#include <errno.h>

// used to test vertex array functions
static GLfloat vertices2[] = { 0,   0, 1,
                             0.5,   0, 1,
                             0.5, 0.5, 1,
                               0, 0.8, 1,
                             2.0, 2.5, 1,
                             3.5, 3.5, 1};


static GLdouble *vertex_ptr;
static int vertex_count;

static GLfloat scaleY = -0.9;

static GLfloat zoomFactor = 1.0;

static GLfloat x_desplacement = 0.0; //fir glTranslatef 
static GLfloat y_desplacement = 0.0;
static GLfloat z_desplacement = 0.0;

static GLfloat x_rotation_angle = 0.0;
static GLfloat y_rotation_angle = 0.0;

void defualt_body(int argc, char** argv);

void displayMe2(void);

void populate_array();

void display_vertex_array(void);

void press_arrow_key(int key, int x, int y);

void press_abc_key(unsigned char key, int x, int y);

void increase_y_scale(void);

void decrease_y_scale(void);
//-----------------------------------


void press_arrow_key(int key, int x, int y);

void rotate_x_axis_positive(void);
void rotate_x_axis_negative(void);

void rotate_y_axis_positive(void);
void rotate_y_axis_negative(void);

//----------------------------

void draw_cloud(FILE * cloudFile);
// draw cloud with most primitive openGL function
// for painting glVertex()
//


void displayMe_WITH_POITER(FILE * cloudFile);
// draw point cloud after it's been stored in
// a array
//

int open_cloud_file();
// middleware 
// yet to be 


int open_cloud_file();
// potentially useful
// 
//


int open_cloud_n_print(FILE *  cloudFile);
//  prints file contents on prompt
//
//

void print_3d_array(void *ptrToArray, int begin, int end);
//  facilitate array population analisys
//
//

void display_vertex_array_element(void);
// unproductive aprouch to displaying a cloud
//
// 




#endif // CMAIN_H