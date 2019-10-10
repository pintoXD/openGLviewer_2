// gcc main.c -o window -lglut -lGL

#ifdef __APPLE__
    #define GL_SILENCE_DEPRECATION 
    #include <GLUT/glut.h>         
#endif
#ifdef __linux__
    #include <GL/glut.h>         
#endif

void draw() 
{
        glBegin(GL_POLYGON);
                glVertex3f(0.5, 0.0, 0.5);
                glVertex3f(0.7, 0.0, 0.0);
                glVertex3f(0.0, 0.5, 0.0);
                glVertex3f(0.0, 0.0, 0.5);
        glEnd();
}

void displayMe(void)
{
        glClear(GL_COLOR_BUFFER_BIT);
        draw();
        glFlush();
}
 
int main(int argc, char** argv)
{
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_SINGLE);
        glutInitWindowSize(800, 600);
        glutInitWindowPosition(100, 100);
        glutCreateWindow("Open Cloud");
        glutDisplayFunc(displayMe);
        glutMainLoop();
        return 0;
}