#include "crossair.hpp"

#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>
#include <common/glutils.h>

Crossair::Crossair(const Scene* parent) 
    : Renderable(parent) {
    setRenderType(GL_LINES);
}

void Crossair::render() const {
	glLineWidth(4.0f);
    Renderable::render();
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
