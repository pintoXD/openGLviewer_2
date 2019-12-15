#ifdef __APPLE__
    #define GL_SILENCE_DEPRECATION 
    #include <GLUT/glut.h>         
#endif
#ifdef __linux__
    #include <GL/glut.h>         
#endif

#include "KeyboardM.h"
#include "cmain.h" // necessary to access global variables

// nao funciona direito talvez glut redisplay esteja com problemas
// void press_arrow_key_m(int key, int x, int y)
// {
//         if(key == GLUT_KEY_LEFT) {
//                 translate_negative_x_m(&x_desplacement);
//                 printf("xx é %f\n", x_desplacement); 
//         } 
//         else if(key == GLUT_KEY_RIGHT)
//                 translate_positive_x_m(&x_desplacement);
//         else if(key == GLUT_KEY_DOWN){
//                 printf("Down key is pressed\n");
//                 translate_positive_y_m(&y_desplacement);
//         }
//         else if(key == GLUT_KEY_UP){
//                 printf("Up key is pressed\n");
//                 translate_negative_y_m(&y_desplacement);
//         }  
// }



void translate_negative_x_m(GLfloat *x_desplacement)
{
        *x_desplacement = (*x_desplacement) - 0.03;
        glutPostRedisplay();
}

void translate_positive_x_m(GLfloat *x_desplacement)
{
        *x_desplacement = (*x_desplacement) + 0.03;
        glutPostRedisplay();
}

void translate_positive_y_m(GLfloat *y_desplacement)
{
        *y_desplacement = (*y_desplacement) + 0.03;
        glutPostRedisplay();
}

void translate_negative_y_m(GLfloat *y_desplacement)
{
        *y_desplacement = (*y_desplacement) - 0.03;
        glutPostRedisplay();
}

//--------------------------------------------------------------------------------------
// [ ] global variable + glScale()
void zoom_in_m(GLfloat *zoomFactor)
{
        *zoomFactor = (*zoomFactor) / 0.98;
        glutPostRedisplay();
}

void zoom_out_m(GLfloat *zoomFactor)
{
        *zoomFactor = (*zoomFactor) * 0.98;
        glutPostRedisplay();
}