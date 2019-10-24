
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


void displayMe2(void) 
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

                //while( cursor != EOF ) //
                for(int i = 1, cursor = 0; cursor != EOF; i++) 
                {       
                        cursor = fscanf(cloudFile, "%lf %lf %lf \n", &x, &y, &z);
                        glVertex3f(x, -y, z);
                        
                        
                        // printf("%d - %lf %lf %lf \n",i , x, y, z);
                        // i++;
                 }
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
        glutDisplayFunc(displayMe2);
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
        printf("hello openGL");
        defualtBody(argc, argv);

        
        // double x, y, z;
        // x = y = z = 0;

        // FILE *cloudFile;
        // cloudFile = fopen ("./cloud_f.xyz","r");

        // if (cloudFile == NULL) {
        //         printf ("File not created okay, errno = %d\n", errno);
        //         return 1;
        // }
//      
        
        // int i = 1;
        // int cursor = 0; 
        // while( cursor != EOF ) //for(int i = 1; i <= 300000; i++)
        // {       
        //         cursor = fscanf(cloudFile, "%lf %lf %lf \n", &x, &y, &z);
        //         printf("%d - %lf %lf %lf \n",i , x, y, z);
        //         i++;
        // }
                

//
        // fclose (cloudFile);
        // printf ("File opened okay\n");
        // return 0;
        
        return 0;
}