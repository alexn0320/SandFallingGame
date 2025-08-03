#ifndef RENDERER_H
#define RENDERER_H

#include "glad/glad.h"
#include <string.h>

/* rendering related functionality */

typedef struct 
{
    GLuint VAO;
    GLuint texture;
} renderer;

/* Returns the VAO used for rendering which is initialised with the quad representing the grid */
renderer init_renderer();

#endif