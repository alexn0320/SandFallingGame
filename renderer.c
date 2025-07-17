#include "renderer.h"

#include <stdio.h>

GLuint init_renderer(GLuint grid_width, GLuint grid_height, GLuint screen_width, GLuint screen_height, GLuint cell_size)
{
    GLfloat data[] = {

    };

    /* width * height cells, each with 6 vertices, each with 3 floats */
    /*GLfloat data[3 * 6 * grid_width * grid_height];

    GLuint x = 0;
    GLuint y = 0;
    GLuint flag = 1;

    while(flag)
    {
        if(x == screen_width)
        {
            x = 0;
            y++;
        }

        data[y * grid_width + x / cell_size] = x;
        data[y * grid_width + (x + 1) / cell_size] = x + cell_size;
        data[(y + 1) * grid_width + (x + 1) / cell_size] = x + cell_size;

        x += cell_size;
    
        if(x == screen_width && y == (screen_height - cell_size) / cell_size)
            flag = 0;
    }*/

    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO); 
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    return VAO;
}