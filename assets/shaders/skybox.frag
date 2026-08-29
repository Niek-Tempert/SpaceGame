#version 330

in vec3 cam_pos;
in vec3 w_pos;

out vec4 fragment;

const vec3 top = vec3(0.12, 0.12, 0.34);
const vec3 bottom = vec3(0.04, 0.06, 0.12);

void main()
{
    vec3 view_dir = normalize(w_pos - cam_pos);
    float t = view_dir.y * 0.5 + 0.5;
    vec3 grad = mix(bottom, top, t);
    fragment = vec4(grad, 1.0);
};
