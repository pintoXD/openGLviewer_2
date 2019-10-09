
// works create script for it
// gcc cmain.c -o cwindow -lglut -lGLUT -lGL
// Fazer rodar no mac

#ifdef __APPLE__
    #define GL_SILENCE_DEPRECATION // mac
    #include <GLUT/glut.h>         // mac
#endif
#ifdef __linux__
    #include <GL/glut.h>         // mac
#endif
 
void displayMe(void)
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
 
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(400, 300);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Hello world!");
    glutDisplayFunc(displayMe);
    glutMainLoop();
    return 0;
}