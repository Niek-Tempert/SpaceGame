#version 330

uniform mat4 MVP;
uniform mat4 View;
uniform mat4 Model;

in vec3 vPos;

out vec3 cam_pos;
out vec3 w_pos;

void main()
{
    gl_Position = MVP * vec4(vPos, 1.0);
    cam_pos = vec3(inverse(View)[3]);
    w_pos = vec3(Model * vec4(vPos, 1.0));
};
