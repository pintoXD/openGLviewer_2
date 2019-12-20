#ifndef OGL_H
#define OGL_H


#ifdef __APPLE__
    #define GL_SILENCE_DEPRECATION 
    #include <GLUT/glut.h>         
#endif
#ifdef __linux__
    #include <GL/glut.h>         
#endif

#include "vars.h"

void display_vertex_array_ogl(void);


#endif //OGL_H
