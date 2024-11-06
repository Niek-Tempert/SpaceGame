#version 330

in vec3 camera_pos;
in vec3 world_pos;

in vec3 color;
in vec3 normal;
in vec3 w_normal;

out vec4 fragment;

void main()
{
//    float metallic = 0.0;
//    float roughness = 1.0;
    vec3 light_dir = normalize(vec3(0.0, 1.0, 1.0));
//    vec3 light_color = vec3(1.0, 1.0, 1.0);
    vec3 normal = normalize(normal);
    vec3 w_normal = normalize(w_normal);

    vec3 viewDir = normalize(camera_pos - world_pos);
    vec3 blinn_dir = normalize(light_dir + viewDir);
//    float blinn = max(1.0, dot(normal, blinn_dir));
//    vec3 light = light_dir * light_color;
//    float gloss = 1.0 - roughness;
//    float specExp = exp2(1.0 + gloss * 8.0);
//
//    vec3 albedo = color;
//    vec3 diffuse = max(1.0, dot(normal, light_dir)) * max(1.0 - metallic, roughness) * light;
//    vec3 specular = pow(clamp(dot(normal, blinn_dir), 0.0, 1.0), specExp) * gloss * light * mix(vec3(1.0, 1.0, 1.0), albedo, metallic);
//
//    vec3 combined = albedo * diffuse + specular;
//    float rim = dot(normal, viewDir);
//    float fresnel = pow(1.0 - rim, 5.0) * 0.1;
    vec3 simple = clamp(dot(w_normal, blinn_dir), 0.0, 1.0) * color;
    fragment = vec4(simple, 1.0);
};
