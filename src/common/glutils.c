#include "glutils.h"

#include <stdio.h>
#include <stdlib.h>

static code loadFile(char** data, const char* filepath) {
    code err = CODE_OK;

    FILE* file = fopen(filepath, "rb");
    if (!file) return CODE_FILE_ERR;
    
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    char* buffer = (char*)malloc(length + 1);
    if(!buffer) { err = CODE_MEM_ERR; goto cleanup; }
    
    fread(buffer, 1, length, file);
    buffer[length] = '\0';

    *data = buffer;

cleanup:
    fclose(file);
    
    return err;
}

static code shaderCompile(GLuint* shader, GLenum type, const char* source) {
    code err = CODE_OK;

    GLuint id = glCreateShader(type);
    glShaderSource(id, 1, &source, NULL);
    glCompileShader(id);
    
    GLint success;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success) {
        char info_log[512];
        glGetShaderInfoLog(id, 512, NULL, info_log);
        logError("Shader compilation failed:\n%s", info_log);
        glDeleteShader(id);
        err = CODE_SHADER_ERR;
        goto cleanup;
    }

    *shader = id;

cleanup:
    return err;
}

static code shaderFromSource(GLuint* shader, GLenum type, const char* source) {
    code err = CODE_OK;

    GLuint id = 0;
    if (err = shaderCompile(&id, type, source)) return err;
    
    GLuint program = glCreateProgram();
    glAttachShader(program, id);
    glLinkProgram(program);
    
    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char info_log[512];
        glGetProgramInfoLog(program, 512, NULL, info_log);
        logError("Program linking failed:\n%s", info_log);
        glDeleteProgram(program);
        err = CODE_SHADER_ERR;
        goto cleanup;
    }

    *shader = program;

cleanup:    
    glDeleteShader(id);
    return err;
}

static code shaderFromSourceVF(GLuint* shader, const char* vertex, const char* fragment) {
    code err = CODE_OK;

    GLuint vshader = 0, fshader = 0;
    if (err = shaderCompile(&vshader, GL_VERTEX_SHADER, vertex)) return err;
    if (err = shaderCompile(&fshader, GL_FRAGMENT_SHADER, fragment)) goto cleanup;
    
    GLuint program = glCreateProgram();
    glAttachShader(program, vshader);
    glAttachShader(program, fshader);
    glLinkProgram(program);

    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char info_log[512];
        glGetProgramInfoLog(program, 512, NULL, info_log);
        logError("Program linking failed:\n%s", info_log);
        glDeleteProgram(program);
        err = CODE_SHADER_ERR;
        goto cleanup;
    }

    *shader = program;
    
cleanup:
    glDeleteShader(vshader);
    glDeleteShader(fshader);
    return err;
}

code shaderLoadCompute(GLuint* shader, const char* filepath) {
    code err = CODE_OK;

    char* source = NULL;
    if (err = loadFile(&source, filepath)) return err;
    
    err = shaderFromSource(shader, GL_COMPUTE_SHADER, source);
    
    free(source);
    return err;
}

code shaderLoadVF(GLuint* shader, const char* vertPath, const char* fragPath) {
    code err = CODE_OK;
    
    char *vertSrc = NULL, *fragSrc = NULL; 
    if (err = loadFile(&vertSrc, vertPath)) return err;
    if (err = loadFile(&fragSrc, fragPath)) goto cleanup;
    
    err = shaderFromSourceVF(shader, vertSrc, fragSrc);
    
cleanup:
    free(vertSrc);
    free(fragSrc);

    return err;
}
