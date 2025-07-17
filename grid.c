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