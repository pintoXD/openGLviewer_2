#ifndef KEYBOARDM_H
#define KEYBOARDM_H

#ifdef __APPLE__
    #define GL_SILENCE_DEPRECATION 
    #include <GLUT/glut.h>         
#endif
#ifdef __linux__
    #include <GL/glut.h>         
#endif



GLdouble *vertex_ptr_cloud;
int       vertex_count_cloud;

#endif //KEYBOARDM_H