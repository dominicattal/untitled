#include "wall.h"
#include <stdlib.h>

Wall* wall_create(walltype type, f32 x, f32 z, f32 height)
{
    Wall* wall = malloc(sizeof(Wall));
    wall->type = type;
    wall->position.x = x;
    wall->position.z = z;
    wall->height = height;
    return wall;
}

void wall_destroy(Wall* wall)
{
    free(wall);
}