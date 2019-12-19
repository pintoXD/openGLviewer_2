#ifndef CMAIN_H
#define CMAIN_H

#ifdef __APPLE__
    #define GL_SILENCE_DEPRECATION 
    #include <GLUT/glut.h>         
#endif
#ifdef __linux__
    #include <GL/glut.h>         
#endif

#include <stdio.h>
#include <errno.h>

static GLdouble *vertex_ptr;
static int vertex_count;

static GLfloat scaleY = -0.9;

static GLfloat zoomFactor = 1.0;

static GLfloat x_desplacement = 0.0;  
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


#endif // CMAIN_H