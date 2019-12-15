#ifndef KEYBOARDM_H


#ifdef __APPLE__
    #define GL_SILENCE_DEPRECATION 
    #include <GLUT/glut.h>         
#endif
#ifdef __linux__
    #include <GL/glut.h>         
#endif


void zoom_in_m(GLfloat *);
void zoom_out_m(GLfloat *);

void translate_negative_x_m(GLfloat *);
void translate_positive_x_m(GLfloat *);

void translate_negative_y_m(GLfloat *);
void translate_positive_y_m(GLfloat *);

#endif // KEYBOARD_H