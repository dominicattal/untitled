#ifndef RENDERER_H
#define RENDERER_H

#include <glad.h>
#include <glfw.h>
#include "vao.h"
#include "vbo.h"
#include "shader.h"
#include "texture.h"

typedef struct Renderer {
    VAO vaos[2];
    Shader shaders[2];
    Texture spritesheet;
} Renderer;

extern Renderer renderer;

void renderer_init(void);
void renderer_update(u32 offset, size_t subdata_size, f32* subdata, u32 buffer_length, buffertype type);
void renderer_render(void);
void renderer_destroy(void);

u32 renderer_uniform_location(char* identifier, buffertype type);

#endif