#ifndef VARS_H
#define VARS_H

// DEFINIÇÃO PODERA SER ISOLADA EM UM UNICO ARQUIVO
#ifdef __APPLE__
    #define GL_SILENCE_DEPRECATION 
    #include <GLUT/glut.h>         
#endif
#ifdef __linux__
    #include <GL/glut.h>         
#endif

 GLdouble vpp[9];   // pelo jeito nao presisa ser statico
// static GLdouble vpp[] = {  -0.5, 0.5, 0, 
//                      0.5, 0.5, 0,
//                      0.5,    1, 0 };

//GLdouble vertex_ptr_persistent[] = {};

GLdouble *vertex_ptr_cloud; //give segmentation fault if STATIC
int       vertex_count_cloud;

// were all static I changed and it crashed 
//static GLfloat OGL_scaleY = -0.9;

// IF NOT STATIC LINKER ERROR
static GLfloat OGL_scaleY     = -0.9;
static GLfloat OGL_zoomFactor =  1.0;

static GLfloat OGL_x_desplacement = 0.0;  
static GLfloat OGL_y_desplacement = 0.0;
static GLfloat OGL_z_desplacement = 0.0;

static GLfloat OGL_x_rotation_angle = 0.0;
static GLfloat OGL_y_rotation_angle = 0.0;
static int mx = -1, my = -1;   // Prevous mouse coordinates

// ----------------------------
static GLfloat eyeX = 0.0; 
static GLfloat eyeY = 0.0; 
static GLfloat eyeZ = 0.0; 

static GLfloat centerX = 0.0; 
static GLfloat centerY = 0.0; 
static GLfloat centerZ =  -5;

static GLfloat upX = 0; 
static GLfloat upY = 1; 
static GLfloat upZ = 0; 


static char state = 2;


#endif //VARS_H