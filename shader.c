#include "shader.h"

char *get_shader_source(const char *path)
{
    FILE *f = fopen(path, "r");

    if(!f)
    {
        printf("Failed to load file\n");
        return NULL;
    }

    /* gets the size of the file as the EOF position */
    fseek(f, 0, SEEK_END);
    uint32_t eof = ftell(f);
    rewind(f);
    
    char *shader_source = malloc(eof + 1);
    fread(shader_source, 1, eof, f);
    shader_source[eof] = '\0';

    return shader_source;
}

GLint get_shader(const char *shader_source, uint32_t shader_type)
{
    /* Shader creation, source setting, compilation */
    GLint shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, &shader_source, NULL);
    glCompileShader(shader);

    GLint success;
    GLchar log[512];

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, log);
        printf("%s %s\n", "Failed to compile shader: ", log);
        return -1;
    }

    return shader;
}

GLint get_program(GLint *shaders, GLuint count)
{
    /* Shader attachment, program linking */
    GLint program = glCreateProgram();
    
    for(GLuint i = 0; i < count; i++)
        glAttachShader(program, shaders[i]);

    glLinkProgram(program);

    GLint success;
    GLchar log[512];

    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if(!success)
    {
        glGetProgramInfoLog(program, 512, NULL, log);
        printf("%s\n", "Failed to link program: ", log);
        return -1;
    }

    return program;
}