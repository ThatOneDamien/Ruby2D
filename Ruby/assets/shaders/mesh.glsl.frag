#version 450 core

layout(location = 0) out vec4 o_Color;

layout(location = 1) in vec4 v_Color;

void main()
{
    o_Color = vec4(0.0, 0.0, 0.0, 1.0);
}