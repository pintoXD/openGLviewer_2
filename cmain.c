
/*
 works create script for it
 gcc cmain.c -o cwindow -lglut -lGLUT -lGL //nao funciona mais
 possivelmente estou usando freeglut
 gcc cmain.c -o cwindow -lglut -lGL // funciona  
 Fazer rodar no mac  */

#ifdef __APPLE__
    #define GL_SILENCE_DEPRECATION 
    #include <GLUT/glut.h>         
#endif
#ifdef __linux__
    #include <GL/glut.h>         
#endif

#include <stdio.h>
#include <errno.h>

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
    //open the cloud file
}

int open_cloud_n_print(FILE *  cloudFile)
{
        double x, y, z;
        x = y = z = 0;

        for (int i = 1, cursor = 0; cursor != EOF; i++) {       
                cursor = fscanf(cloudFile, "%lf %lf %lf \n", &x, &y, &z);
                printf("%d - %lf %lf %lf \n",i , x, y, z);
        } 
}

void read_cloud_line()
{
    // operatins read each cloud line
}


void displayMe2(void) // nao adianta fazer alterações na assinatura dessa funçaõ 
// callback e funções de desenhar
{   
        double x, y, z;
        x = y = z = 0;

        FILE *cloudFile;
        cloudFile = fopen ("./cloud_f.xyz","r");

        if (cloudFile == NULL) {
                printf ("File not created okay, errno = %d\n", errno);
                //return 1;
        }

        glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_POINTS);
                for(int i = 1, cursor = 0; cursor != EOF; i++) {       
                        cursor = fscanf(cloudFile, "%lf %lf %lf \n", &x, &y, &z);
                        glVertex3f(0.25*x, -0.25*y, 0.25*z);
                        //glVertex3f(x, -factor*y, factor*z);
                }
        glEnd();
        glFlush();
}

static GLint vertices[] = { 25, 25,
                            100, 325,
                            175, 25,
                            175, 325,
                            250, 25,
                            325, 325 };

static GLint vertices2[] = { 0, 0,
                            0.5, 0,
                            0.5, 0.5,
                            1.75, 3.25,
                            2.0, 2.5,
                            3.5, 3.5 };

void display_vertex_array(void) 
{
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        

   
        glColor3f(1, 1, 1);
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(2, GL_INT, 0, vertices);
        
/*        
        glBegin(GL_POLYGON);
                // glArrayElement(0);
                // glArrayElement(1);
                // glArrayElement(2);

                glVertex3f(0.0, 0.0, 0.0);
                glVertex3f(0.5, 0.0, 0.0);
                glVertex3f(0.0, 0.5, 0.0);
        glEnd();
        glFlush();
*/

        glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_TRIANGLES);
                // glVertex2f(0.0, 0.0);
                // glVertex2f(0.5, 0.0);
                // glVertex2f(0.5, 0.5);
                glArrayElement(vertices[1]);
                glArrayElement(3);
                glArrayElement(5);

        glEnd();
        glFlush();
} 

void defualtBody(int argc, char** argv)
{
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_SINGLE);
        glutInitWindowSize(800, 600);
        glutInitWindowPosition(100, 100);
        glutCreateWindow("Hello world!");


        glutDisplayFunc(display_vertex_array);
        glutMainLoop();

 /* 
       
        */
        
}


int main(int argc, char** argv)
{
        

        //printf("hello openGL\n");
        defualtBody(argc, argv);
        
        return 0;
}