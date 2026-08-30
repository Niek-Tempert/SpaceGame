#pragma once

#include "glad.h"
#include "error.h"

code shaderLoadCompute(GLuint* shader, const char* filepath);
code shaderLoadVF(GLuint* shader, const char* vertPath, const char* fragPath);
