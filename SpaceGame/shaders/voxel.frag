#version 330

in vec3 cam_pos;
in vec3 w_pos;
in vec3 w_norm;

in vec3 col;

out vec4 fragment;

const vec3 light_dir = vec3(0.0, 1.0, 0.0);


void main()
{
    vec3 light_dir = normalize(light_dir);
    vec3 normal = normalize(w_norm);

    vec3 view_dir = normalize(cam_pos - w_pos);
    vec3 blinn_dir = normalize(light_dir + view_dir);
    vec3 result = clamp(dot(normal, blinn_dir), 0.0, 1.0) * col;
    fragment = vec4(result, 1.0);
};
