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


void draw_cloud(FILE * cloudFile);
 
void displayMe(FILE * cloudFile);

int open_cloud_file();

int open_cloud_n_print(FILE *cloudFile);

void read_cloud_line();


void defualtBody(int argc, char** argv, FILE * cloudFile);


#endif // CMAIN_H