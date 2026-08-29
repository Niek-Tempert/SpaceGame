#version 330

uniform mat4 MVP;
uniform mat4 Model;
uniform mat4 View;

in vec3 vPos;
in vec3 vNorm;
in vec3 vCol;
in vec2 vUV;

out vec3 cam_pos;
out vec3 w_pos;
out vec3 w_norm;
out vec2 uv0;

out vec3 col;

#include "hash.glsl"

void main()
{
    gl_Position = MVP * vec4(vPos, 1.0);
    cam_pos = vec3(inverse(View)[3]);
    w_pos = vec3(Model * vec4(vPos, 1.0));
    w_norm = vec3(Model * vec4(vNorm, 0.0));
    
    col = hash_vec3_to_vec3(vCol);
    uv0 = vUV;
};
