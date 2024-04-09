#version 330 core
layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

uniform mat4 view;
uniform mat4 proj;

void build_house(vec4 position)
{   
    gl_Position = (position + vec4(-1.0, 0.0, 0.0, 0.0)); // 1:bottom-left   
    EmitVertex();
    gl_Position = (position + vec4(-1.0, 1.0, 0.0, 0.0)); // 3:top-left
    EmitVertex();
    gl_Position = (position + vec4(1.0, 1.0, 0.0, 0.0)); // 2:bottom-right
    EmitVertex();
    gl_Position = (position + vec4(0.0, 1.0, 0.0, 0.0)); // 4:top-right
    EmitVertex();
    EndPrimitive();
}

void main() {    
    build_house(gl_in[0].gl_Position);
}