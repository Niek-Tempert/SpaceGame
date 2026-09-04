#include "camera_provider.hpp"

#include <common/types.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

CameraProvider::CameraProvider(glm::mat4* view, glm::mat4* proj) {
    m_view = view;
    m_proj = proj;
}

CameraProvider::CameraProvider(const CameraProvider *provider) {
    m_view = provider->m_view;
    m_proj = provider->m_proj;
}

glm::mat4 CameraProvider::getView() const {
	return *m_view;
}

glm::mat4 CameraProvider::getProj() const {
    return *m_proj;
}
