#ifdef __APPLE__
    #define GL_SILENCE_DEPRECATION 
    #include <GLUT/glut.h>         
#endif
#ifdef __linux__
    #include <GL/glut.h>         
#endif

#include "KeyboardM.h"

// [ ] global variable + glScale()
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

void translate_negative_y_m(GLfloat *y_desplacement)
{
        *y_desplacement = (*y_desplacement) - 0.03;
        glutPostRedisplay();
}

void translate_positive_y_m(GLfloat *y_desplacement)
{
        *y_desplacement = (*y_desplacement) + 0.03;
        glutPostRedisplay();
}

