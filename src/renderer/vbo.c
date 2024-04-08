#include "vbo.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

VBO vbo_create(buffertype type)
{
    VBO vbo;
    glGenBuffers(1, &vbo.ID);
    glBindBuffer(GL_ARRAY_BUFFER, vbo.ID);
    vbo.buffer_length = 0;
    if (type == DRAWABLE)
        glBufferData(GL_ARRAY_BUFFER, MAX_BUFFER_LENGTH * sizeof(f32), NULL, GL_DYNAMIC_DRAW);
    else
        glBufferData(GL_ARRAY_BUFFER, MAX_BUFFER_LENGTH * sizeof(f32), NULL, GL_STATIC_DRAW);
    return vbo;
}

void vbo_update(VBO* vbo, u32 offset, size_t subdata_size, f32* subdata, u32 buffer_length)
{
    assert(buffer_length < MAX_BUFFER_LENGTH);
    glBindBuffer(GL_ARRAY_BUFFER, vbo->ID);
    vbo->buffer_length = buffer_length;
    if (buffer_length == 15)
        for (int i = 0; i < 15; i++)
            printf(i % 5 == 4 ? "%f\n" : "%f ", subdata[i]);
    glBufferSubData(GL_ARRAY_BUFFER, offset, subdata_size, subdata);
}

void vbo_destroy(VBO vbo)
{
    glDeleteBuffers(1, &vbo.ID);
}