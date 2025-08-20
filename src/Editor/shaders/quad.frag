#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform vec4 _color = vec4(1);

void main()
{
    color = _color;
}