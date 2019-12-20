#ifndef CLOUD_H
#define CLOUD_H

// DEFINIÇÃO PODERA SER ISOLADA EM UM UNICO ARQUIVO
#ifdef __APPLE__
    #define GL_SILENCE_DEPRECATION 
    #include <GLUT/glut.h>         
#endif
#ifdef __linux__
    #include <GL/glut.h>         
#endif

//
#include "vars.h"

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
//

void populate_array_c();


#endif //CLOUD_H