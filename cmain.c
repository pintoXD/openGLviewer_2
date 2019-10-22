
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
 
void displayMe(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);
       
        glVertex3f(0.5, 0.0, 0.5);
        glVertex3f(0.5, 0.0, 0.0);
        glVertex3f(0.0, 0.5, 0.0);
        glVertex3f(0.0, 0.0, 0.5);
    glEnd();
    //glPointSize(10.0);  // doesn't work as I expected
    glBegin(GL_POINTS);
        glVertex3f(0.5, 0.0, 0.5);
    glEnd();
    glFlush();
}

int open_cloud_file()
{
    //open the cloud file
}

void read_cloud_line()
{
    // operatins read each cloud line
}

void draw_cloud()
{
    // use openGl vertex to draw 
}

void defualtBody(int argc, char** argv)
{
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_SINGLE);
        glutInitWindowSize(800, 600);
        glutInitWindowPosition(100, 100);
        glutCreateWindow("Hello world!");
        glutDisplayFunc(displayMe);
        glutMainLoop();

        /* 
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_SINGLE);
        glutInitWindowSize(800, 600);
        glutInitWindowPosition(100, 100);
        glutCreateWindow("Hello world!");
        glutDisplayFunc(displayMe);
        glutMainLoop(); 
        */
        
}



int main(int argc, char** argv)
{
        //defualtBody(argc, argv);
        

        FILE *cloudFile;
        cloudFile = fopen ("./1cloud.xyz","r");

        if (cloudFile == NULL) {
                printf ("File not created okay, errno = %d\n", errno);
                return 1;
        }
        fclose (cloudFile);
        printf ("File opened okay\n");
        return 0;
        
        return 0;
}