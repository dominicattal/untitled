#include "tile.h"
#include <stdlib.h>

static f32 s_vertices[] = {
    0, 0, 0,
    1, 0, 0,
    1, 1, 0,
    0, 1, 0,
    0, 0, 1,
    1, 0, 1,
    1, 1, 1,
    0, 1, 1
};

static u32 side_idxs[] = {
    2, 1, 0, 3, //-z
    7, 4, 5, 6, //+z
    6, 5, 1, 2, //+x
    3, 0, 4, 7, //-x
    2, 3, 7, 6, //+y
    0, 4, 5, 1  //-y
};

static u32 vertex_idxs[] = {
    0, 1, 2, 0, 2, 3
};

Tile* tile_create(tiletype type)
{
    Tile* tile = malloc(sizeof(Tile));
    tile->type = type;
    return tile;
}

void tile_destroy(Tile* tile)
{
    free(tile);
}

void tile_vertex_data(vec3f pos, vec3f color, f32* buffer, Tile* tile, i32 offset)
{
    i32 start, end;
    start = tile->type == WALL ? 0 : NUM_WALL_SIDES;
    end   = tile->type == WALL ? NUM_WALL_SIDES : NUM_WALL_SIDES + NUM_FLOOR_SIDES;
    for (i32 s = start; s < end; s++) {
        for (i32 v = 0; v < VERTEX_COUNT; v++) {
            buffer[offset++] = s_vertices[3*side_idxs[4*s+vertex_idxs[v]]]   + pos.x;
            buffer[offset++] = s_vertices[3*side_idxs[4*s+vertex_idxs[v]]+1] * pos.y;
            buffer[offset++] = s_vertices[3*side_idxs[4*s+vertex_idxs[v]]+2] + pos.z;
            buffer[offset++] = color.x + s * 0.1;
            buffer[offset++] = color.y + s * 0.1;
            buffer[offset++] = color.z + s * 0.1;
        }
    }
}