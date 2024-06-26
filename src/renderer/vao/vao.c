#include "vao.h"

VAO vao_create(GLenum usage, GLenum mode, u32 length)
{
    VAO vao;
    glGenVertexArrays(1, &vao.id);
    glBindVertexArray(vao.id);
    vao.vbo = vbo_create();
    vao.length = length;
    vao.usage = usage;
    vao.mode = mode;
    return vao;
}

void vao_attr(VAO vao, u32 index, u32 length, u32 offset)
{
    glBindVertexArray(vao.id);
    vbo_bind(vao.vbo);
    glVertexAttribPointer(index, length, GL_FLOAT, GL_FALSE, vao.length * sizeof(f32), (void*)(offset * sizeof(f32)));
    glEnableVertexAttribArray(index);
}

void vao_update(VAO vao, u32 offset, u32 length, f32* buffer)
{
    glBindVertexArray(vao.id);
    vbo_update(vao.vbo, offset, length, buffer);
}

void vao_malloc(VAO vao, u32 length)
{
    glBindVertexArray(vao.id);
    vbo_malloc(vao.vbo, length, vao.usage);
}

void vao_draw(VAO vao)
{
    glBindVertexArray(vao.id);
    glDrawArrays(vao.mode, 0, vao.vbo->length / vao.length);
}

void vao_destroy(VAO vao)
{
    vbo_destroy(vao.vbo);
    glDeleteVertexArrays(1, &vao.id);
}
