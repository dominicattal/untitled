#include "shader.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char* read_file(char *path)
{
    FILE *ptr;
    char *content;
    ptr = fopen(path, "rb");
    fseek(ptr, 0, SEEK_END);
    i32 len = ftell(ptr);
    assert(len > 0);
    fseek(ptr, 0, SEEK_SET);
    content = calloc(1, len);
    assert(content != NULL);
    fread(content, 1, len, ptr);
    assert(strlen(content) > 0);
    fclose(ptr);
    return content;
}

static unsigned int compile(char *s_path, GLenum type)
{
    u32 shader;
    const char* shader_code;
    shader = glCreateShader(type);
    shader_code = read_file(s_path);
    glShaderSource(shader, 1, &shader_code, NULL);
    glCompileShader(shader);

    char info_log[512];
    i32 success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, info_log);
        printf(info_log);
        exit(1);
    }

    return shader;
}

Shader shader_create(char* vs_path, char* fs_path)
{
    Shader shader;
    u32 vertex, fragment;
    shader.ID = glCreateProgram();
    vertex   = compile(vs_path, GL_VERTEX_SHADER);
    fragment = compile(fs_path, GL_FRAGMENT_SHADER);
    glAttachShader(shader.ID, vertex);
    glAttachShader(shader.ID, fragment);
    glLinkProgram(shader.ID);
    glDeleteShader(vertex);
    glDeleteShader(fragment);

    char info_log[512];
    i32 success;
    glGetProgramiv(shader.ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shader.ID, 512, NULL, info_log);
        printf(info_log);
        exit(1);
    }

    return shader;
}

void shader_use(Shader shader)
{
    glUseProgram(shader.ID);
}