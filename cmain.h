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


static GLdouble *vertex_ptr;
static int vertex_count;

void defualtBody(int argc, char** argv);

void displayMe2(void);

void populate_array();

#endif // CMAIN_H