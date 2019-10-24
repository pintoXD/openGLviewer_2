
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
/*    glBegin(GL_POLYGON);
       
        glVertex3f(0.5, 0.0, 0.5);
        glVertex3f(0.5, 0.0, 0.0);
        glVertex3f(0.0, 0.5, 0.0);
        glVertex3f(0.0, 0.0, 0.5);
    glEnd();
    //glPointSize(10.0);  // doesn't work as I expected
*/
    // draw_cloud(cloudFile);
    glBegin(GL_POINTS);
        glVertex3f(0.5, 0.0, 0.5);
    glEnd();
    glFlush();
}

void displayMe() 
{
        glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_POLYGON);
        
                glVertex3f(0.5, 0.0, 0.5);
                glVertex3f(0.5, 0.0, 0.0);
                glVertex3f(0.0, 0.5, 0.0);
                glVertex3f(0.0, 0.0, 0.5);
        glEnd();
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


void defualtBody(int argc, char** argv)
{
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_SINGLE);
        glutInitWindowSize(800, 600);
        glutInitWindowPosition(100, 100);
        glutCreateWindow("Hello world!");

        glutDisplayFunc(displayMe() );
        glutMainLoop();

/* 
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_SINGLE);
        glutInitWindowSize(800, 600);
        glutInitWindowPosition(100, 100);
        glutCreateWindow("Hello world!");
        glutDisplayFunc(displayMe);
        glutMainLoop(); }
        */
        
}



int main(int argc, char** argv)
{
        FILE *cloudFile;
        cloudFile = fopen ("./cloud_f.xyz","r");

        if (cloudFile == NULL) {
                printf ("File not created okay, errno = %d\n", errno);
                return 1;
        }
        //open_cloud_n_print(cloudFile);
        
        defualtBody(argc, argv);
    

       

/*
        for(int i = 1, cursor = 0; cursor != EOF; i++)
               
                cursor = fscanf(cloudFile, "%lf %lf %lf \n", &x, &y, &z);
                printf("%d - %lf %lf %lf \n",i , x, y, z);
*/      
        fclose (cloudFile);
        printf ("File opened okay\n");
        return 0;
        
        return 0;
}