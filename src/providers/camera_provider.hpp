#pragma once

#include <glm/glm.hpp>

class CameraProvider {
public:
    CameraProvider(glm::mat4* view, glm::mat4* proj);
	CameraProvider(const CameraProvider* provider);

protected:
    virtual glm::mat4 getView() const;
    virtual glm::mat4 getProj() const;

private:
    const glm::mat4* m_view;
    const glm::mat4* m_proj;
};
