#ifndef SHADER_H
#define SHADER_H

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#include "glad/glad.h"

/* Shader related functions */

/* Reads the source of the shader file */
char *get_shader_source(const char *path);
/* Creates shader from given source and type */
GLint get_shader(const char *shader_source, uint32_t shader_type);
/* Creates shader program from given shaders */
GLint get_program(GLint *shaders, GLuint count);

#endif