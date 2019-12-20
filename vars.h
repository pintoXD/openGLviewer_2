#ifndef KEYBOARDM_H
#define KEYBOARDM_H

// DEFINIÇÃO PODERA SER ISOLADA EM UM UNICO ARQUIVO
#ifdef __APPLE__
    #define GL_SILENCE_DEPRECATION 
    #include <GLUT/glut.h>         
#endif
#ifdef __linux__
    #include <GL/glut.h>         
#endif



GLdouble *vertex_ptr_cloud;
int       vertex_count_cloud;

//
static GLfloat OGL_scaleY = -0.9;
static GLfloat OGL_zoomFactor = 1.0;

static GLfloat OGL_x_desplacement = 0.0;  
static GLfloat OGL_y_desplacement = 0.0;
static GLfloat OGL_z_desplacement = 0.0;

static GLfloat OGL_x_rotation_angle = 0.0;
static GLfloat OGL_y_rotation_angle = 0.0;

#endif //KEYBOARDM_H