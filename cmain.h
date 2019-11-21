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

void defualt_body(int argc, char** argv);

void displayMe2(void);

void populate_array();

void display_vertex_array(void);

void press_arrow_key(int key, int x, int y);


//-----------------------------------

void draw_cloud(FILE * cloudFile);
// draw cloud with most primitive openGL function
// for painting glVertex()
//


void displayMe_WITH_POITER(FILE * cloudFile);
// draw point cloud after it's been stored in
// a array
//

int open_cloud_file();
// middleware 
// yet to be 


int open_cloud_file();
// potentially useful
// 
//


int open_cloud_n_print(FILE *  cloudFile);
//  prints file contents on prompt
//
//

void print_3d_array(void *ptrToArray, int begin, int end);
//  facilitate array population analisys
//
//

void display_vertex_array_element(void);
// unproductive aprouch to displaying a cloud
//
// 




#endif // CMAIN_H