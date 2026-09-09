#version 330

in vec3 vPos;

uniform mat4 View;

void main()
{
   gl_Position = View * vec4(vPos, 1.0);
}
