#version 330 core
layout (location = 0) in vec3 vertex;
layout (location = 1) in vec2 texCoords;
out vec2 TexCoords;

uniform mat4 projection = mat4(1);

void main()
{
    gl_Position = projection * vec4(vertex, 1.0);
    TexCoords = texCoords;
}