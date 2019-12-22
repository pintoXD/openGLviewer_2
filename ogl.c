#include "ogl.h"


void display_vertex_array_ogl(void) 
{       
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1, 1, 1);

        glLoadIdentity();
        gluLookAt(0, 0, 0,
                  0, 0, -5,
                  0, 1, 0);


        glScalef(1*OGL_zoomFactor, OGL_scaleY*OGL_zoomFactor, 1*OGL_zoomFactor);
        glTranslatef(OGL_x_desplacement, OGL_y_desplacement, OGL_z_desplacement);
        
        glRotatef(OGL_y_rotation_angle, 0, 1, 0);  
        glRotatef(OGL_x_rotation_angle, 1, 0, 0);
       
        glEnableClientState(GL_VERTEX_ARRAY); 
                                         
        glVertexPointer(3, GL_DOUBLE, 0, vertex_ptr_cloud);


        unsigned int index[vertex_count_cloud];
        for (int i = 0 ; i < vertex_count_cloud; i++) {
                index[i] = i;
        }

        glDrawElements(GL_POINTS, vertex_count_cloud, GL_UNSIGNED_INT, index);
      
        glDisableClientState(GL_VERTEX_ARRAY);
        glFlush();
} 