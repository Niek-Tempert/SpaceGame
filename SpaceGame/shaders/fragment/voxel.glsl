#version 330

in vec3 color;
in vec2 uv;
out vec4 fragment;

void main()
{
    fragment = vec4(uv, 0.0, 1.0);
};
