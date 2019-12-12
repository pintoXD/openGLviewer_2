/*
 create script for it
 freeglut linux
    gcc cmain.c -o cwindow -lglut -lGL -lGLU // deve incluir glu  
 mac 
    gcc cmain.c -o cwindow  -framework OpenGL -framework GLUT */

#ifdef __APPLE__
    #define GL_SILENCE_DEPRECATION 
    #include <GLUT/glut.h>         
#endif
#ifdef __linux__
    #include <GL/glut.h>         
#endif

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include "cmain.h"


int main(int argc, char** argv)
{
        populate_array();
        defualt_body(argc, argv);


        /*/     
                //test for static array of points
        
                populate_array();
                print_3d_array(vertex_ptr, 12360, 12400);
                printf("%d\n\n", vertex_count);
                //*/

        return 0;
}

void populate_array() 
{
        /*
            1 - abrir nuvem
            2 - contar numero de linhas
            3 - usar o numero de linhas para alocar dinamicamente meu vetor
            4 - popular o vetor
            sera nescessario o numero de linhas do arquivo ?
        */      
        FILE *cloudFile;
        cloudFile = fopen ("./clouds/cloud_f.xyz","r");

        if (cloudFile == NULL) {
                printf ("File not created okay, errno = %d\n", errno);
                //return 1;
        }

        int linesCount = 0;
           for (char c = getc(cloudFile); c != EOF; c = getc(cloudFile)) {
                if (c == '\n')
                        linesCount = linesCount + 1;
        }
        vertex_count = linesCount;

        rewind(cloudFile);
        /*
                //nao vou usar o mais 1 pq eu ja vou usar o array o tamanho certo 
                // devo encontrar outa estrutura para armazenar o numero de linhas

                //((float *)vertices_ptr)[0] = linesCount;
                o problema disso é que eu devo passar o meu vetor para o a função
                glDrawElements que desenha todos os pontos
                +3 por causa do modo de abrir fscanf
        */
        // test if can access this array with DrawElements
        GLdouble *vertices_ptr;
        vertices_ptr = malloc(sizeof(GLdouble)*linesCount*3+3);
        
        for (int i = 1, cursor = 0; cursor != EOF; i++) {       
                cursor = fscanf(cloudFile, "%lf %lf %lf \n",  &((GLdouble *)vertices_ptr)[3*(i-1)    ], 
                                                              &((GLdouble *)vertices_ptr)[3*(i-1) + 1], 
                                                              &((GLdouble *)vertices_ptr)[3*(i-1) + 2]);
        } 
        vertex_ptr = vertices_ptr;
        
        // print_3d_array(vertex_ptr, 12360, 12400);  //teste
        // printf("\n\n");
        // //printf("\n lines count: %i  ==  %f ", linesCount, ((float *)vertices_ptr)[3*16082*i]);
}


void defualt_body(int argc, char** argv)
{
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_SINGLE);
        glutInitWindowSize(800, 600);
        glutInitWindowPosition(100, 100);
        glutCreateWindow("Hello world!");

        glutDisplayFunc(display_vertex_array);

        glutSpecialFunc( press_arrow_key );
        glutKeyboardFunc( press_abc_key );
        glutMainLoop();
        
}

void press_arrow_key(int key, int x, int y)
{
        if(key == GLUT_KEY_LEFT)
                translate_negative_x();  
        else if(key == GLUT_KEY_RIGHT)
                translate_positive_x();
        else if(key == GLUT_KEY_DOWN){
                printf("Down key is pressed\n");
                translate_negative_y();
                //decrease_y_scale();
        }
        else if(key == GLUT_KEY_UP){
                printf("Up key is pressed\n");
                translate_positive_y();
                //increase_y_scale();
        }  
}



void press_abc_key(unsigned char key, int x, int y)
{
        if(key == 'a' ){
                printf("Left key is pressed\n");
        }  
                
        else if(key == 'd' )
                printf("Right key is pressed\n");
        else if(key == 's' )
                printf("Down key is pressed\n");
        else if(key == 'w')
                printf("Up key is pressed\n");
        
        else if(key == 'i') {
                printf("i key pressed\n");
                zoom_in_1();
        }
        else if(key == 'o') {
                printf("i key pressed\n");
                zoom_out_1();
        }
        else if(key == 'k') {
                rotate_x_axis_positive();
        }
        else if(key == 'l') {
                rotate_x_axis_negative();
        }
        else if(key == 'n') {
                rotate_y_axis_positive();
        }
        else if(key == 'm') {
                rotate_y_axis_negative();
        }

}
// ---------------------------------------------------
// [ ] global variable + glScale()
void zoom_in_1(void)
{
        zoomFactor = zoomFactor/0.98;
        glutPostRedisplay();
}

void zoom_out_1(void)
{
        zoomFactor = zoomFactor*0.98;
        glutPostRedisplay();
}
// ------------------------------------------------
// translate 
// not working

void translate_negative_x(void)
{
        x_desplacement = x_desplacement - 0.03;
        glutPostRedisplay();
}
void translate_positive_x(void)
{
        x_desplacement = x_desplacement + 0.03;
        glutPostRedisplay();
}


void translate_negative_y(void)
{
        y_desplacement = y_desplacement - 0.03;
        glutPostRedisplay();
}
void translate_positive_y(void)
{
        y_desplacement = y_desplacement + 0.03;
        glutPostRedisplay();
}
// ---------------------------------------------------
void rotate_x_axis_positive(void)
{
        x_rotation_angle = x_rotation_angle + 0.5;
        glutPostRedisplay();
}

void rotate_x_axis_negative(void)
{
        x_rotation_angle = x_rotation_angle - 0.5;
        glutPostRedisplay();
}


void rotate_y_axis_positive(void)
{
        y_rotation_angle = y_rotation_angle + 0.5;
        glutPostRedisplay();
}

void rotate_y_axis_negative(void)
{
        y_rotation_angle = y_rotation_angle - 0.5;
        glutPostRedisplay();
}


// ---------------------------------------------------

void increase_y_scale(void)
{
        scaleY = scaleY - 0.01;
        glutPostRedisplay();
}

void decrease_y_scale(void)
{
        scaleY = scaleY + 0.01;
        glutPostRedisplay();
}

//----------------------------------- display functions
void display_vertex_array(void) 
{       
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1, 1, 1);
//
        glLoadIdentity();
        gluLookAt(0, 0, 0,
                  0, 0, -5,
                  0, 1, 0);

        // play with gluLookAt 105 -> viewing 

        
        glScalef(1*zoomFactor, scaleY*zoomFactor, 1*zoomFactor);
        glTranslatef(x_desplacement, y_desplacement, z_desplacement);
        
        glRotatef(x_rotation_angle, 1, 0, 0);
        glRotatef(y_rotation_angle, 0, 1, 0);  
       

        // ideia on mouse event update glScalef()

//
        glEnableClientState(GL_VERTEX_ARRAY); 
                                         
        glVertexPointer(3, GL_DOUBLE, 0, vertex_ptr);


        unsigned int index[vertex_count];
        for (int i = 0 ; i < vertex_count; i++) {
                index[i] = i;
        }

        glDrawElements(GL_POINTS, vertex_count, GL_UNSIGNED_INT, index);
      
        glDisableClientState(GL_VERTEX_ARRAY);
        glFlush();
} 


void displayMe2(void) 
{   
        // 
        double x, y, z;
        x = y = z = 0;

        FILE *cloudFile;
        cloudFile = fopen ("./clouds/cloud_f.xyz","r");

        if (cloudFile == NULL) {
                printf ("File not created okay, errno = %d\n", errno);
                //return 1;
        }

        glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_POINTS);
                for(int i = 1, cursor = 0; cursor != EOF; i++) {       
                        cursor = fscanf(cloudFile, "%lf %lf %lf \n", &x, &y, &z);
                        glVertex3f(x, -y, z);
                        //glVertex3f(x, -factor*y, factor*z);
                }
        glEnd();
        glFlush();
}




// -----------------------------------------------------

void draw_cloud(FILE * cloudFile)
{       
        double x, y, z;
        x = y = z = 0;

        glBegin(GL_POINTS);
                for (int i = 1, cursor = 0; cursor != EOF; i++) {       
                        cursor = fscanf(cloudFile, "%lf %lf %lf \n", &x, &y, &z);
                        glVertex3f(x*30, y*-30, z*30);
                }
        glEnd();
}


void displayMe_WITH_POITER(FILE * cloudFile)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);
       
        glVertex3f(0.5, 0.0, 0.5);
        glVertex3f(0.5, 0.0, 0.0);
        glVertex3f(0.0, 0.5, 0.0);
        glVertex3f(0.0, 0.0, 0.5);
    glEnd();
    //glPointSize(10.0);  // doesn't work as I expected

    // draw_cloud(cloudFile);
    
    glFlush();
}


int open_cloud_file()
{
    return 1;//open the cloud file
}


int open_cloud_n_print(FILE *  cloudFile)
{
        double x, y, z;
        x = y = z = 0;

        for (int i = 1, cursor = 0; cursor != EOF; i++) {       
                cursor = fscanf(cloudFile, "%lf %lf %lf \n", &x, &y, &z);
                printf("%d - %lf %lf %lf \n",i , x, y, z);
        } 
        return 1;
}


void print_3d_array(void *ptrToArray, int begin, int end) 
{
        for (int i = begin; i <= end ;  i++) {
                printf("%d - %lf %lf %lf \n",i ,  ((double *)ptrToArray)[3*(i-1)    ], 
                                                  ((double *)ptrToArray)[3*(i-1) + 1], 
                                                  ((double *)ptrToArray)[3*(i-1) + 2]);
        }
}


void display_vertex_array_element(void) 
{       
        // função deveria imprimir usando glVertex para imprimir pontos
        // a partir de um array 

        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
   
        glColor3f(1, 1, 1);
        glEnableClientState(GL_VERTEX_ARRAY); 
       
        glVertexPointer(3, GL_DOUBLE, 0, vertex_ptr);
        
        glDrawElements(GL_POINTS, vertex_count, GL_UNSIGNED_INT, vertex_ptr);
        // glBegin(GL_POINTS);
        // //         glArrayElement(0);
        // //         glArrayElement(1);
        // //         glArrayElement(2);
        // //         glArrayElement(3);
        //         for (int i = 1000; i <= vertex_count; i++) {
        //                 glArrayElement(i);
        //         }

        //glEnd();

        glDisableClientState(GL_VERTEX_ARRAY);
        glFlush();
} 


// used to test vertex array functions
static GLfloat vertices2[] = { 0,   0, 1,
                             0.5,   0, 1,
                             0.5, 0.5, 1,
                               0, 0.8, 1,
                             2.0, 2.5, 1,
                             3.5, 3.5, 1};