#version 330

layout (location = 0) in vec3 vPos;

uniform mat4 trans;

void main()
{
   gl_Position = trans * vec4(vPos, 1.0);
}
