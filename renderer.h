#ifndef RENDERER_H
#define RENDERER_H

#include "glad/glad.h"

/* rendering related functionality, which is done using the fragment shader and textures */

/* stores input/output texture data */
typedef struct 
{
    GLuint FBO_input;
    GLuint FBO_output;
    GLuint tex_input;
    GLuint tex_output;
    GLuint tex_width;
    GLuint tex_heigh;
} tex_buffer;

/* stores uniform locations */
typedef struct
{
    GLuint tex_input;
    GLuint tex_output;
} uniforms;

/* Returns the VAO used for rendering which is initialised with the quad representing the grid */
GLuint init_renderer();
/* Initializes the texture buffer */
void init_tex_buffer(tex_buffer *buffer);
/* Initializes the uniform locations*/
void init_uniforms(GLuint program, uniforms *unif);

#endif