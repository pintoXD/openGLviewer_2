/*
 freeglut linux
    gcc  cmain.c KeyboardM.c  -o linux_bi -lglut -lGL -lGLU 
 mac 
    gcc cmain.c -o cwindow  -framework OpenGL -framework GLUT
    gcc cmain.c cloud.c ogl.c KeyboardM.c  -o mac_bi  -framework OpenGL -framework GLUT  
    
                          -----main-----
                        /                \  
                       /                  \
                openCloud                    oGL
                   |                    /     |    \   
                   |                   /      |     \
                 vars*           keyboard   vars*     mouse
                                    |                   |
                                    |                   |
                                   vars*               vars*


[1][x] ifndef & define in vars.h caousing problem
[ ] problem with vertex array_ogl key board functions doens't work
[ ] isolate keyboard functions
[ ] remove all from cmain and isolate the main function
    
    */


#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include "cmain.h"
#include "ogl.h"
#include "KeyboardM.h"



int main(int argc, char** argv)
{
        populate_array_c();
        defualt_body(argc, argv);

        return 0;
}


void defualt_body(int argc, char** argv)
{
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_SINGLE);
        glutInitWindowSize(800, 600);
        glutInitWindowPosition(500, 10);
        glutCreateWindow("Hello world!");

        glutDisplayFunc( display_vertex_array ); //

        glutSpecialFunc( press_arrow_key );
        glutKeyboardFunc( press_abc_key );
        glutMainLoop();
        
}

void press_arrow_key(int key, int x, int y)
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


void press_abc_key(unsigned char key, int x, int y)
{
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

}


void display_vertex_array(void) 
{       
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1, 1, 1);

        glLoadIdentity();
        gluLookAt(0, 0, 0,
                  0, 0, -5,
                  0, 1, 0);


        glScalef(1*OGL_zoomFactor, OGL_scaleY*OGL_zoomFactor, 1*OGL_zoomFactor);
        glTranslatef(OGL_x_desplacement, OGL_y_desplacement, OGL_z_desplacement);
        
        glRotatef(OGL_x_rotation_angle, 1, 0, 0);
        glRotatef(OGL_y_rotation_angle, 0, 1, 0);  
       
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
