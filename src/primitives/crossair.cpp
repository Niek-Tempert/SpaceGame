#include "crossair.hpp"

#include <glad/glad.h>
#include <common/glutils.h>

#include <glm/gtc/matrix_transform.hpp>
#include <engine/scene.hpp>

Crossair::Crossair(const Scene* parent) 
    : Renderable(parent, (u32)RenderConfig::Lines)
    , CanvasProvider(parent) {
    Renderable::init();
}

void Crossair::setGLState() const {
    Renderable::setGLState();
    glLineWidth(4.0f);
}

glm::mat4 Crossair::getTransform() const {
    glm::ivec2 size = getSize();
    return glm::translate(glm::mat4(1.0f), glm::vec3((f32)size.x / 2.0f, (f32)size.y / 2.0f, 0.0f));
}

glm::mat4 Crossair::getView() const {
    return glm::mat4(1.f);
}

glm::mat4 Crossair::getProj() const {
    glm::ivec2 size = getSize();
    return glm::ortho(0.0f, (f32)size.x, 0.0f, (f32)size.y, 1.0f, -1.0f);
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
