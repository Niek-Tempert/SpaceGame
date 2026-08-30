#pragma once

#include "helpers.h"
#include "types.h"
#include "log.h"

typedef i32 code;

const char* codeToStr(code err);
code logErr(code err, const char* filename, i32 line, const char* func);

#ifdef CODE_LOG
#define ERR(err) logErr(err, __FILENAME__, __LINE__, __func__)
#else
#define ERR(err) err
#endif

#define CODE_OK              0
#define CODE_ERR        ERR(-1)
#define CODE_MEM_ERR    ERR(-2)
#define CODE_SHADER_ERR ERR(-3)
#define CODE_FILE_ERR   ERR(-4)
#define CODE_GLFW_ERR   ERR(-5)
