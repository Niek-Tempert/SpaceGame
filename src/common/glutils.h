#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <glad/glad.h>
#include "error.h"

NODISCARD code shaderLoadCompute(GLuint* shader, const char* filepath);
NODISCARD code shaderLoadVF(GLuint* shader, const char* vertPath, const char* fragPath);

#ifdef __cplusplus
}
#endif
