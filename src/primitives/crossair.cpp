#include "crossair.hpp"

#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>
#include <common/glutils.h>
#include <engine/scene.hpp>

Crossair::Crossair(const Scene* parent) 
    : Renderable(parent) {
    setRenderType(GL_LINES);
}

void Crossair::setState() const {
    glLineWidth(4.0f);
}

std::vector<glm::vec3> Crossair::getVertices() const {
    return {
        { -16.0f, 0.0f, 0.0f },
        { 16.0f, 0.0f, 0.0f },
        { 0.0f, -16.0f, 0.0f },
        { 0.0f, 16.0f, 0.0f }
    };
}

GLuint Crossair::getShader() const {
    GLuint shader = 0;
    if (shaderLoadVF(&shader, SHADER_PATH "cursor.vert", SHADER_PATH "cursor.frag")) throw;
    return shader;
}
