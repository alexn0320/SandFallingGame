#include <stdio.h>
#include "shader.h"
#include "grid.h"
#include "renderer.h"

#include <GLFW/glfw3.h>

#define WIDTH   (800U)
#define HEIGHT  (800U)
#define FPS     (60U)

const char *title = "Sand Falling";
uint8_t texture_grid[GRID_WIDTH * GRID_HEIGHT];

GLuint shader_handler()
{
    /* Vertex shader */
    char *vert_source = get_shader_source("shaders/vertex_shader.vert");

    if(!vert_source)
        return 0;

    GLint vert = get_shader(vert_source, GL_VERTEX_SHADER);
    free(vert_source);

    if(vert < 0)
        return 0;

    /* Fragment shader */
    char *frag_source = get_shader_source("shaders/fragment_shader.frag");

    if(!frag_source)
        return 0;

    GLint frag = get_shader(frag_source, GL_FRAGMENT_SHADER);
    free(frag_source);

    if(frag < 0)
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

    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        printf("Failed to load GLAD window\n");
        glfwTerminate();
        return 0;
    }

    /* Shader loading */
    GLuint program = shader_handler();
    renderer r = init_renderer();

    cell *grid = grid_init();
    memset(texture_grid, 0, GRID_WIDTH * GRID_HEIGHT);

    int x = 1, y = 1;
    texture_grid[y * GRID_HEIGHT + x] = 1;

    /* Game loop */
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(program);
        glUniform1i(glGetUniformLocation(program, "tex"), 0);
        glActiveTexture(GL_TEXTURE0);
        render(texture_grid, r.texture, GRID_WIDTH, GRID_HEIGHT);
        glBindTexture(GL_TEXTURE_2D, r.texture);
        glBindVertexArray(r.VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        move_cell(GRID_WIDTH, GRID_HEIGHT, x, y, x, y + 1);

        if(y >= 390)
            y = 390;
        else
            y++;

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    free(grid);

    return 0;
}