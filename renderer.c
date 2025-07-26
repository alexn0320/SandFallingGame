#include "renderer.h"

#include <stdio.h>

GLuint init_renderer()
{
    /* Fullscreen texture */
    GLfloat data[] = {
        -1.f, -1.f, 1.f,
        1.f, -1.f, 1.f,
        1.f, 1.f, 1.f,
        1.f, 1.f, 1.f,
        -1.f, -1.f, 1.f,
        -1.f, 1.f, 1.f
    };

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

void init_tex_buffer(tex_buffer *buffer)
{
    /* Framebuffers are used to get the output texture data to the CPU */
    glGenTextures(1, &buffer->tex_input);
    glGenTextures(1, &buffer->tex_output);

    glBindTexture(GL_TEXTURE_2D, buffer->tex_input);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, buffer->tex_width, buffer->tex_heigh, 0, GL_RED, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBindTexture(GL_TEXTURE_2D, buffer->tex_output);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, buffer->tex_width, buffer->tex_heigh, 0, GL_RED, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glGenFramebuffers(1, &buffer->FBO_input);
    glGenFramebuffers(1, &buffer->FBO_output);

    glBindFramebuffer(GL_FRAMEBUFFER, buffer->FBO_input);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, buffer->tex_input, 0);

    glBindFramebuffer(GL_FRAMEBUFFER, buffer->FBO_output);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, buffer->tex_output, 0);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void init_uniforms(GLuint program, uniforms *unif)
{
    unif->tex_input = glGetUniformLocation(program, "tex_input");
    unif->tex_output = glGetUniformLocation(program, "tex_output");
}