#ifndef KEYBOARDM_H
#define KEYBOARDM_H

#ifdef __APPLE__
    #define GL_SILENCE_DEPRECATION 
    #include <GLUT/glut.h>         
#endif
#ifdef __linux__
    #include <GL/glut.h>         
#endif

void press_arrow_key_m(int , int , int );

void zoom_in_m(GLfloat *);
void zoom_out_m(GLfloat *);

void translate_negative_x_m(GLfloat *);
void translate_positive_x_m(GLfloat *);

void translate_negative_y_m(GLfloat *);
void translate_positive_y_m(GLfloat *);

void rotate_x_axis_positive_m(GLfloat *);
void rotate_x_axis_negative_m(GLfloat *);

void rotate_y_axis_positive_m(GLfloat *);
void rotate_y_axis_negative_m(GLfloat *);


#endif // KEYBOARD_H