#ifndef GRID_H
#define GRID_H

#include "glad/glad.h"
#include <stdlib.h>

/* Grid rendering functionality */

#define SCREEN_WIDTH    (800U)
#define SCREEN_HEIGHT   (800U)

#define CELL_SIZE       (2U)
#define GRID_WIDTH      (SCREEN_WIDTH / CELL_SIZE)
#define GRID_HEIGHT     (SCREEN_HEIGHT / CELL_SIZE)

/* Existing cell types */
typedef enum 
{
    EMPTY
} CELL_TYPE;

/* Defines the information for movable cells */
typedef struct 
{

} movable;

/* Defines the information for immovable cells */
typedef struct
{

} immovable;

/* Cell data */
typedef struct
{
    GLuint x, y;
    CELL_TYPE type;

    /* Stores the cell type */
    union
    {
        movable mov;
        immovable im;
    };
} cell;

/* byte grid for the shader */
extern uint8_t texture_grid[GRID_WIDTH * GRID_HEIGHT];

cell *grid_init();
/* moves a cell from one position to another, through air */
void move_cell(GLuint grid_width, GLuint grid_height, GLuint old_x, GLuint old_y, GLuint new_x, GLuint new_y);

#endif