#ifdef __APPLE__
    #define GL_SILENCE_DEPRECATION 
    #include <GLUT/glut.h>         
#endif
#ifdef __linux__
    #include <GL/glut.h>         
#endif


void zoom_in_ptr(GLfloat *zoomFactor)
{
        *zoomFactor = (*zoomFactor)/0.98;
        glutPostRedisplay();
}