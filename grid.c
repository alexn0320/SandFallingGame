#include "grid.h"

cell *grid_init()
{
    cell *grid = malloc(sizeof(cell) * GRID_WIDTH * GRID_HEIGHT);

    for(uint32_t i = 0; i < GRID_HEIGHT; i++)
    {
        for(uint32_t j = 0; j < GRID_WIDTH; j++)
        {
            cell c = {
                .x = j * CELL_SIZE,
                .y = i * CELL_SIZE,
                .type = EMPTY
            };

            grid[GRID_HEIGHT * i + j] = c;
        }
    }

    return grid;
}

void move_cell(GLuint grid_width, GLuint grid_height, GLuint old_x, GLuint old_y, GLuint new_x, GLuint new_y)
{
    uint8_t aux = texture_grid[old_y * grid_height + old_x];
    texture_grid[old_y * grid_height + old_x] = 0;
    texture_grid[new_y * grid_height + new_x] = aux;
}