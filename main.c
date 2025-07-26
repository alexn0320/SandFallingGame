#include <stdio.h>
#include "shader.h"
#include "grid.h"
#include "renderer.h"

#include <GLFW/glfw3.h>

#define WIDTH (800U)
#define HEIGHT (800U)
#define FPS (60U)

const char *title = "Sand Falling";

GLuint shader_handler()
{
    /* Vertex shader */
    char *vert_source = get_shader_source("shaders/vertex_shader.vert");

    if (!vert_source)
        return 0;

    GLint vert = get_shader(vert_source, GL_VERTEX_SHADER);
    free(vert_source);

    if (vert < 0)
        return 0;

    /* Fragment shader */
    char *frag_source = get_shader_source("shaders/fragment_shader.frag");

    if (!frag_source)
        return 0;

    GLint frag = get_shader(frag_source, GL_FRAGMENT_SHADER);
    free(frag_source);

    if (frag < 0)
        return 0;

    GLint shaders[2] = {vert, frag};

    return get_program(shaders, 2);
}

int main()
{
    if (!glfwInit())
    {
        printf("Failed to init GLFW\n");
        return 0;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow *window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, title, NULL, NULL);

    if (!window)
    {
        printf("Failed to load GLFW window\n");
        glfwTerminate();
        return 0;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Failed to load GLAD window\n");
        glfwTerminate();
        return 0;
    }

    /* OpenGL related initialisations */
    GLuint program = shader_handler();
    GLuint VAO = init_renderer();

    tex_buffer buf = {
        .tex_width = SCREEN_WIDTH,
        .tex_heigh = SCREEN_HEIGHT
    };
    init_tex_buffer(&buf);

    uniforms unif;
    init_uniforms(program, &unif);

    /* Application related initialisations */
    cell *grid = grid_init();

    uint8_t aux = 1;

    glBindTexture(GL_TEXTURE_2D, buf.tex_input);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 2, 2, 1, 1, GL_RED, GL_UNSIGNED_BYTE, &aux);

    /* Game loop */
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(program);
        glUniform1i(unif.tex_input, 0);
        glBindTexture(GL_TEXTURE_2D, buf.tex_input);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    free(grid);

    return 0;
}