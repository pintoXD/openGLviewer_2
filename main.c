/*
 freeglut linux
    gcc  cmain.c KeyboardM.c  -o linux_bi -lglut -lGL -lGLU 
 mac 
    gcc main.c cloud.c ogl.c KeyboardM.c  -o mac_bi  -framework OpenGL -framework GLUT  
    
                          -----main-----
                        /               \  
                       /                 \
                 Cloud                     ogl
                   |                  /     |    \   
                   |                 /      |     \
                 vars*         keyboard   vars*     mouse

   * in vars.h variables used by openGL must be static, otherwise like 
   * fail with DUPLICATED SYMBOL
                                                    

   ** ogl -> must have the callbacks with global variables
                                          


   [1][x] ifndef & define in vars.h caousing problem
   [5][x] problem with vertex array_ogl key board functions doens't work
   [6][x] isolate keyboard functions
   [4][x] remove all from cmain and isolate the main function
   
   [ ]    PROBLEMS with the OGL callbacks 
   [2][x] display vertex array finction
   [3][x] keyborad callback function 


   [ ]    MOUSE 
   [ ][ ] glutLookAt -> with variables in vars.h to make proportional calcs
   [ ][ ] 

   [ ]    multiple clouds with its different collors
   [ ][ ] this will encadiate new problems of archetecture
   [ ][ ] apply comands on different clouds  
    
*/

#include "ogl.h"
#include "cloud.h"


int main(int argc, char** argv)
{
        populate_array_c();
        defualt_body_ogl(argc, argv);

        return 0;
}
