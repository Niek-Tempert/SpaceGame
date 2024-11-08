#version 330

uniform mat4 MVP;
uniform mat4 M;
uniform mat4 V;

in vec3 vPos;
in vec3 vNorm;

out vec3 cam_pos;
out vec3 w_pos;
out vec3 w_norm;

out vec4 col;

void main()
{
    gl_Position = MVP * vec4(vPos, 1.0);
    w_norm = vec3(M * vec4(vNorm, 0.0));
    w_pos = vec3(M * vec4(vPos, 1.0));
    cam_pos = vec3(inverse(V)[3]);
};
