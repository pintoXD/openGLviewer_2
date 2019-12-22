#include "KeyboardM.h"


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

