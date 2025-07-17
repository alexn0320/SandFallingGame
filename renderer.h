#ifndef RENDERER_H
#define RENDERER_H

#include "glad/glad.h"

/* rendering related functionality */

/* Returns the VAO used for rendering which is initialised with the quad representing the grid */
GLuint init_renderer(GLuint grid_width, GLuint grid_height, GLuint screen_width, GLuint screen_height, GLuint cell_size);

#endif