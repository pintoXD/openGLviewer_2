#include "ogl.h"

void defualt_body_ogl(int argc, char** argv)
{
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_SINGLE);
        glutInitWindowSize(800, 600);
        glutInitWindowPosition(500, 10);
        glutCreateWindow("Hello world!");

        glutDisplayFunc( display_vertex_array_ogl ); // colocar a funcao que funciona em outro arquivo

        glutSpecialFunc( press_arrow_key_ogl );
        glutKeyboardFunc( press_abc_key_ogl );

        glutMouseFunc( mouse_pt_plot );

        glutMainLoop();
        
}

//
//
void mouse_pt_plot( GLint button, GLint action, GLint xMouse, GLint yMouse)
{
        if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN) {
                plot_point(xMouse/100, yMouse/100);
                /*
                        meu valores aparecem na tela mas não são persitentes
                        explicação: eu estou redesenhando a tela e nao tenho dentro da minha 
                        estrutura de callback nenhuma referencia para esses valores gerados 
                        pelo meu plot_point()
                */
                printf("%d - %d\n", xMouse, yMouse);
                

        }
        glFlush();
}

void plot_point(GLint x, GLint y)
{
        glColor3f(1, 0, 0);

        glBegin(GL_POLYGON);
                glVertex3f(-1.0f, 1.0f, 0.0f);	// Top Left
                glVertex3f( 1.0f, 1.0f, 0.0f);  
                glVertex3f(x, y, 0);
        glEnd();
 // vai ser dificil fazer essa funçao funcionar 
 // porem quando ela funcioanr vou ter um dominio melhor da tela
}
//
//

void display_vertex_array_ogl(void) 
{       
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1, 1, 1);

        glLoadIdentity();
        gluLookAt(eyeX, eyeY, eyeZ,
                  centerX, centerY, centerZ,
                  upX, upY, upZ);


        glScalef(1*OGL_zoomFactor, OGL_scaleY*OGL_zoomFactor, 1*OGL_zoomFactor);
        glTranslatef(OGL_x_desplacement, OGL_y_desplacement, OGL_z_desplacement);
        
        glRotatef(OGL_y_rotation_angle, 0, 1, 0);  
        glRotatef(OGL_x_rotation_angle, 1, 0, 0);
       
        glEnableClientState(GL_VERTEX_ARRAY); 
                                         
        glVertexPointer(3, GL_DOUBLE, 0, vertex_ptr_cloud);


        unsigned int index[vertex_count_cloud];
        for (int i = 0 ; i < vertex_count_cloud; i++) {
                index[i] = i;
        }

        glDrawElements(GL_POINTS, vertex_count_cloud, GL_UNSIGNED_INT, index);
      
        glDisableClientState(GL_VERTEX_ARRAY);
        glFlush();
} 




void press_arrow_key_ogl(int key, int x, int y)
{
        if(key == GLUT_KEY_LEFT)
                translate_negative_x_m(&OGL_x_desplacement);  
        else if(key == GLUT_KEY_RIGHT)
                translate_positive_x_m(&OGL_x_desplacement);
        else if(key == GLUT_KEY_DOWN){
                printf("Down key is pressed\n");
                translate_positive_y_m(&OGL_y_desplacement);
        }
        else if(key == GLUT_KEY_UP){
                printf("Up key is pressed\n");
                translate_negative_y_m(&OGL_y_desplacement);
        }
        
}

void press_abc_key_ogl(unsigned char key, int x, int y)
{
        printf("%d\n", key);
        if(key == 'i') {
                printf("i key pressed\n");
                zoom_in_m(&OGL_zoomFactor);
        }
        else if(key == 'o') {
                printf("i key pressed\n");
                zoom_out_m(&OGL_zoomFactor);
        }
        else if(key == 'k') {
                rotate_x_axis_positive_m(&OGL_x_rotation_angle);
        }
        else if(key == 'l') {
                rotate_x_axis_negative_m(&OGL_x_rotation_angle);
        }
        else if(key == 'n') {
                rotate_y_axis_positive_m(&OGL_y_rotation_angle);
        }
        else if(key == 'm') {
                rotate_y_axis_negative_m(&OGL_y_rotation_angle);
        }


        else if(key == 32) {
                state = state * -1;
        }
        else if(key == 'e' && state > 0 ) {
                eyeX = eyeX + 0.03;
                glutPostRedisplay();
        }
        else if(key == 'e' && state < 0 ) {
                eyeX = eyeX - 0.03;
                glutPostRedisplay();
        }
        else if(key == 'r' && state > 0 ) {
                eyeY = eyeY + 0.03;
                glutPostRedisplay();
        }
        else if(key == 'r' && state < 0 ) {
                eyeY = eyeY - 0.03;
                glutPostRedisplay();
        }
        else if(key == 't' && state > 0 ) {
                eyeZ = eyeZ + 0.03;
                glutPostRedisplay();
        }
        else if(key == 't' && state < 0 ) {
                eyeZ = eyeZ - 0.03;
                glutPostRedisplay();
        }

        else if(key == 's' && state > 0 ) {
                centerX = centerX + 0.03;
                glutPostRedisplay();
        }
        else if(key == 's' && state < 0 ) {
                centerX = centerX - 0.03;
                glutPostRedisplay();
        }
        else if(key == 'd' && state > 0 ) {
                centerY = centerY + 0.03;
                glutPostRedisplay();
        }
        else if(key == 'd' && state < 0 ) {
                centerY = centerY - 0.03;
                glutPostRedisplay();
        }
        else if(key == 'f' && state > 0 ) {
                centerZ = centerZ + 0.03;
                glutPostRedisplay();
        }
        else if(key == 'f' && state < 0 ) {
                centerZ = centerZ - 0.03;
                glutPostRedisplay();
        }

        else if(key == 'x' && state > 0 ) {
                upX = upX + 0.03;
                glutPostRedisplay();
        }
        else if(key == 'x' && state < 0 ) {
                upX = upX - 0.03;
                glutPostRedisplay();
        }
        else if(key == 'c' && state > 0 ) {
                upY = upY + 0.03;
                glutPostRedisplay();
        }
        else if(key == 'c' && state < 0 ) {
                upY = upY - 0.03;
                glutPostRedisplay();
        }
        else if(key == 'v' && state > 0 ) {
                upZ = upZ + 0.03;
                glutPostRedisplay();
        }
        else if(key == 'v' && state < 0 ) {
                upZ = upZ - 0.03;
                glutPostRedisplay();
        }


       


}

