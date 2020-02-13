#include "cloud.h"

void populate_array_c() 
{      
        FILE *cloudFile;
        //cloudFile = fopen ("./clouds/cloud_f.xyz","r");
        cloudFile = fopen ("./clouds/cloud_captured_1.xyz","r");

        if (cloudFile == NULL) {
                printf ("File not created okay, errno = %d\n", errno);
        }

        int linesCount = 0;
           for (char c = getc(cloudFile); c != EOF; c = getc(cloudFile)) {
                if (c == '\n')
                        linesCount = linesCount + 1;
        }
        vertex_count_cloud = linesCount;

        rewind(cloudFile);

        GLdouble *vertices_ptr;
        vertices_ptr = malloc(sizeof(GLdouble)*linesCount*3+3);
        
        for (int i = 1, cursor = 0; cursor != EOF; i++) {       
                cursor = fscanf(cloudFile, "%lf %lf %lf \n",  &((GLdouble *)vertices_ptr)[3*(i-1)    ], 
                                                              &((GLdouble *)vertices_ptr)[3*(i-1) + 1], 
                                                              &((GLdouble *)vertices_ptr)[3*(i-1) + 2]);
        } 
        vertex_ptr_cloud = vertices_ptr;
}