// gcc main.c -o window -lglut -lGL

#ifdef __APPLE__
    #define GL_SILENCE_DEPRECATION 
    #include <GLUT/glut.h>         
#endif
#ifdef __linux__
    #include <GL/glut.h>         
#endif

#include <stdio.h>
#include <string.h>

void viewer_open_cloud()
{
        
}

unsigned char helper_open_cloud_file()
{
        FILE *ptr;
        ptr = fopen("/home/latin/Desktop/JoaoPedro/draw_from_xyz_openGL/image1.xyz", "r");

        // meus prints so saem depois que eu fecho a aplicação
        // pelo botao de sair da janela criada, kill terminal não tem o mesmo efeito
        if (ptr == NULL) {
                printf("error\n");
        } else {
                printf("OK!");
        }

}


void viewer_draw() 
{
        helper_open_cloud_file();
        glBegin(GL_POLYGON);
                glVertex3f(0.5, 0.0, 0.5);
                glVertex3f(0.7, 0.0, 0.0);
                glVertex3f(0.0, 0.5, 0.0);
                glVertex3f(0.0, 0.0, 0.5);
        glEnd();
}

void jp_displayMe(void)
{
        helper_open_cloud_file();
        glClear(GL_COLOR_BUFFER_BIT);
        viewer_draw();
        glFlush();
}
 
int main(int argc, char** argv)
{
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_SINGLE);
        glutInitWindowSize(800, 600);
        glutInitWindowPosition(100, 100);
        glutCreateWindow("Open Cloud");

        glutDisplayFunc(jp_displayMe);
        glutMainLoop();
        return 0;
}