#include "KeyboardM.h"
#include <stdio.h>
//#include "cmain.h" 


void press_arrow_key_m(int key, int x, int y)
{
        if(key == GLUT_KEY_LEFT)
                translate_negative_x_m(&OGL_x_desplacement);  
        else if(key == GLUT_KEY_RIGHT)
                translate_positive_x_m(&OGL_x_desplacement);
        else if(key == GLUT_KEY_DOWN){
                printf("Down key is pressed - %f\n", OGL_y_desplacement);
                translate_positive_y_m(&OGL_y_desplacement);
        }
        else if(key == GLUT_KEY_UP){
                printf("Up key is pressed - %f\n", OGL_y_desplacement);
                translate_negative_y_m(&OGL_y_desplacement);
        }  
}

//------------------------------

void translate_negative_x_m(GLfloat *x_desplacement)
{
        *x_desplacement = (*x_desplacement) - 0.03;
        glutPostRedisplay();
}

void translate_positive_x_m(GLfloat *x_desplacement)
{
        *x_desplacement = (*x_desplacement) + 0.03;
        glutPostRedisplay();
}

void translate_positive_y_m(GLfloat *y_desplacement)
{
        *y_desplacement = (*y_desplacement) + 0.03;
        glutPostRedisplay();
}

void translate_negative_y_m(GLfloat *y_desplacement)
{
        *y_desplacement = (*y_desplacement) - 0.03;
        glutPostRedisplay();
}

//--------------------------------------------------------------------------------------
void zoom_in_m(GLfloat *zoomFactor)
{
        *zoomFactor = (*zoomFactor) / 0.98;
        glutPostRedisplay();
}

void zoom_out_m(GLfloat *zoomFactor)
{
        *zoomFactor = (*zoomFactor) * 0.98;
        glutPostRedisplay();
}

// -------------------------------------
void rotate_x_axis_positive_m(GLfloat *x_rotation_angle)
{
        *x_rotation_angle = (*x_rotation_angle) + 0.5;
        glutPostRedisplay(); 
}

void rotate_x_axis_negative_m(GLfloat *x_rotation_angle)
{
        *x_rotation_angle = (*x_rotation_angle) - 0.5;
        glutPostRedisplay(); 
}

void rotate_y_axis_positive_m(GLfloat *y_rotation_angle)
{
        *y_rotation_angle = (*y_rotation_angle) + 0.5;
        glutPostRedisplay(); 
}

void rotate_y_axis_negative_m(GLfloat *y_rotation_angle)
{
        *y_rotation_angle = (*y_rotation_angle) - 0.5;
        glutPostRedisplay(); 
}

