#version 330

in vec3 w_norm;

out vec4 fragment;

const vec3 light_pos = vec3(-0.9, 1, 0.8);
const vec3 light_col = vec3(1.0, 1.0, 1.0);

void main()
{
    vec3 w_normal = normalize(w_norm);
    vec3 light_dir = normalize(light_pos);
    
    float d = dot(w_normal, light_pos);
    float lambert = max(d, 0.0);
    
    vec3 result = lambert * light_col;
    
    fragment = vec4(result, 1.0);
};
