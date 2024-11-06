#version 330

uniform mat4 MVP;
uniform mat4 M;
uniform mat4 V;

in vec3 vPos;
in vec3 vNorm;

out vec3 camera_pos;
out vec3 world_pos;

out vec3 color;
out vec3 normal;
out vec3 w_normal;

void main()
{
    gl_Position = MVP * vec4(vPos, 1.0);
    camera_pos = vec3(inverse(V)[3]);
    world_pos = vec3(M * vec4(vPos, 1.0));
    
    color = vec3(0.0, 1.0, 1.0);
    normal = vNorm;
    w_normal = vec3(M * vec4(vNorm, 0.0));
};
