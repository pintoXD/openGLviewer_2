#ifndef OGL_H
#define OGL_H


#ifdef __APPLE__
    #define GL_SILENCE_DEPRECATION 
    #include <GLUT/glut.h>         
#endif
#ifdef __linux__
    #include <GL/glut.h>         
#endif

#include <stdio.h>

#include "vars.h"
#include "KeyboardM.h"

void defualt_body_ogl(int argc, char** argv);

//next 2 callbacks must be in the same file where the first window is created
// there's much to learn in OPENGL archtecture
void press_arrow_key_ogl(int key, int x, int y);
void press_abc_key_ogl(unsigned char key, int x, int y);


void display_vertex_array_ogl(void);

void display_vertex_array(void);


#endif //OGL_H
