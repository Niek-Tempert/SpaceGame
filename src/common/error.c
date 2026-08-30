#undef CODE_LOG
#include "error.h"

#include <stdio.h>

const char* codeToStr(code err) {
    switch (err) {
        case CODE_OK:           return "Ok";
        case CODE_ERR:          return "Error";
        case CODE_MEM_ERR:      return "Memory error";
        case CODE_SHADER_ERR:   return "Shader error";
        case CODE_FILE_ERR:     return "File error";
        default:                return "Unknown error";
    }
}

code logErr(code err, const char* filename, i32 line, const char* func) {
    fprintf(stderr, "%s at line %d: %s in %s\n", filename, line, codeToStr(err), func);
    return err;
}
