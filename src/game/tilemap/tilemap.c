#include "tilemap.h"
#include <gvec.h>
#include <stdlib.h>
#include <stdio.h>

TileMap tilemap;

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
};

static u32 vertex_idxs[] = {
    0, 1, 2, 0, 2, 3
};

static void insert_vertex_data(f32* data, Tile* tile, i32 x, i32 z, i32* count)
{
    /* c = count, s = side, v = vertex */
    int c = *count;
    for (i32 s = 0; s < 5; s++) {
        for (i32 v = 0; v < 6; v++) {
            data[5*6*6*c+6*6*s+6*v]   = s_vertices[3*side_idxs[4*s+vertex_idxs[v]]]   + x;
            data[5*6*6*c+6*6*s+6*v+1] = s_vertices[3*side_idxs[4*s+vertex_idxs[v]]+1];
            data[5*6*6*c+6*6*s+6*v+2] = s_vertices[3*side_idxs[4*s+vertex_idxs[v]]+2] + z;
            data[5*6*6*c+6*6*s+6*v+3] = tile->r;
            data[5*6*6*c+6*6*s+6*v+4] = tile->g;
            data[5*6*6*c+6*6*s+6*v+5] = tile->b;
        }
    }
    (*count)++;
}

void tilemap_init(void) 
{
    tilemap.tile_count = 0;
    for (i32 i = 0; i < TILEMAP_WIDTH * TILEMAP_WIDTH; i++) {
        if (i % 7 == 0)
            tilemap.map[i/TILEMAP_WIDTH][i%TILEMAP_WIDTH] = tile_create(0.5f, 0.5f, 0.5f), tilemap.tile_count++;
        else
            tilemap.map[i/TILEMAP_WIDTH][i%TILEMAP_WIDTH] = NULL;
    }
}

void tilemap_clear(void)
{
    for (i32 i = 0; i < TILEMAP_WIDTH * TILEMAP_WIDTH; i++)
        if (tilemap.map[i/TILEMAP_WIDTH][i%TILEMAP_WIDTH] != NULL)
            free(tilemap.map[i/TILEMAP_WIDTH][i%TILEMAP_WIDTH]);
}

f32* tilemap_vertex_data(void) 
{
    f32* data = malloc(5 * 6 * 6 * tilemap.tile_count * sizeof(f32));
    i32 count = 0;
    for (i32 i = 0; i < TILEMAP_WIDTH; i++)
        for (i32 j = 0; j < TILEMAP_WIDTH; j++)
            if (tilemap.map[i][j] != NULL)
                insert_vertex_data(data, tilemap.map[i][j], i, j, &count);
    return data;
}