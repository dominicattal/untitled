#version 330 core
layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

layout (std140) uniform AspectRatio
{
    float ar;
};

layout (std140) uniform Zoom
{
    float zoom;
};

layout (std140) uniform Constants
{
    float pi;
    float sqrt2;
};

layout (std140) uniform Rotation
{
    float rotation;
};

layout (std140) uniform Tilt
{
    float tilt;
};

out vec2 texCoord;

in float proj_rotation[];

void build_projectile(vec4 position) 
{
    float a = proj_rotation[0] - rotation;
    a = atan(tan(a) / cos(pi / 2 + tilt)) + (cos(a) > 0 ? 0 : pi);
    vec2 offset;
    offset = zoom * (1 / sqrt2) * vec2(ar * cos(a - 3 * pi / 4), sin(a - 3 * pi / 4));
    gl_Position = position + vec4(offset, 0.0 , 0.0);    // 1:bottom-left
    texCoord = vec2(0.0f, 0.25f);
    EmitVertex();
    offset = zoom * (1 / sqrt2) * vec2(ar * cos(a + 3 * pi / 4), sin(a + 3 * pi / 4));
    gl_Position = position + vec4(offset, 0.0, 0.0);    // 3:top-left
    texCoord = vec2(0.0f, 0.0f);
    EmitVertex();
    offset = zoom * (1 / sqrt2) * vec2(ar * cos(a - pi / 4), sin(a - pi / 4));
    gl_Position = position + vec4(offset, 0.0, 0.0);    // 2:bottom-right
    texCoord = vec2(0.25f, 0.25f);
    EmitVertex();
    offset = zoom * (1 / sqrt2) * vec2(ar * cos(a + pi / 4), sin(a + pi / 4));
    gl_Position = position + vec4(offset, 0.0, 0.0);    // 4:top-right
    texCoord = vec2(0.25f, 0.0f);
    EmitVertex();
    EndPrimitive();
}

void main() {
    build_projectile(gl_in[0].gl_Position);
}