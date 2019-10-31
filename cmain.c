
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

static GLfloat vertices[30];

static GLfloat vertices2[] = { 0,   0, 1,
                             0.5,   0, 1,
                             0.5, 0.5, 1,
                               0, 0.8, 1,
                             2.0, 2.5, 1,
                             3.5, 3.5, 1};

void populate_array() 
{      
        FILE *cloudFile;
        cloudFile = fopen ("./cloud_f.xyz","r");

        if (cloudFile == NULL) {
                printf ("File not created okay, errno = %d\n", errno);
                //return 1;
        }
        
        int linesCount = 0;
        for (char c = getc(cloudFile); c != EOF; c = getc(cloudFile)) {
                if (c == '\n')
                        linesCount = linesCount + 1;
        }

        // rewind(cloudFile);
        fclose(cloudFile);
        cloudFile = fopen ("./cloud_f.xyz","r");
/*
        //nao vou usar o mais 1 pq eu ja vou usar o array o tamanho certo 
        // devo encontrar outa estrutura para armazenar o numero de linhas

        //((float *)vertices_ptr)[0] = linesCount;
        +3 por causa do modo de abrir fscanf
*/
        void *vertices_ptr = malloc(sizeof(double)*linesCount*3+3);
        
/* //povoar array
        pega todos os caracteres na linha ponto final, hifen etc


*/
        // linesCount
        double x, y, z;
        x = y = z = 0;

        // estava olhando nuvem errada

        for (int i = 1, cursor = 0; cursor != EOF; i++) {       
                //cursor = fscanf(cloudFile, "%lf %lf %lf \n", &x, &y, &z);
                cursor = fscanf(cloudFile, "%lf %lf %lf \n",  &((double *)vertices_ptr)[3*(i-1)    ], 
                                                              &((double *)vertices_ptr)[3*(i-1) + 1], 
                                                              &((double *)vertices_ptr)[3*(i-1) + 2]);
                
                printf("%d - %lf %lf %lf \n",i ,  ((double *)vertices_ptr)[3*(i-1)    ], 
                                                  ((double *)vertices_ptr)[3*(i-1) + 1], 
                                                  ((double *)vertices_ptr)[3*(i-1) + 2]);
        } 
        // for (int linha = 1; linha <= 2; linha++) {  

        //         fscanf(cloudFile, "%lf %lf %lf \n", &x, &y, &z);
                
                
        //                                         //     ((float *)vertices_ptr)[3*(linha-1)    ], 
        //                                         //     ((float *)vertices_ptr)[3*(linha-1) + 1], 
        //                                         //     ((float *)vertices_ptr)[3*(linha-1) + 2]);
                
        //         printf("%d - %lf %lf %lf \n", linha, x, y, z );
                
                
        //                                         //      ((float *)vertices_ptr)[3*(linha-1)    ], 
        //                                         //      ((float *)vertices_ptr)[3*(linha-1) + 1], 
        //                                         //      ((float *)vertices_ptr)[3*(linha-1) + 2]);
              
        // }
        printf("\n\n");

      
        // for(int i = 0; i <= 3; i++)
        //         printf("\n lines count: %i  ==  %f ", linesCount, ((float *)vertices_ptr)[3*16082*i]);


}

void display_vertex_array(void) 
{
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
   
        glColor3f(1, 1, 1);
        glEnableClientState(GL_VERTEX_ARRAY);
       
        glVertexPointer(3, GL_FLOAT, 0, vertices2);
        
        glBegin(GL_POINTS);
                glArrayElement(0);
                glArrayElement(1);
                glArrayElement(2);
                glArrayElement(3);

        glEnd();

        glDisableClientState(GL_VERTEX_ARRAY);
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
        //defualtBody(argc, argv);
   //     populate_array();

//
        FILE *cloudFile;
        cloudFile = fopen ("./cloud_f.xyz","r");

        open_cloud_n_print(cloudFile);
//*/
        return 0;
}