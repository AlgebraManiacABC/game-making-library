#ifndef SHADERS_H
#define SHADERS_H

#include <GL/glew.h>

GLuint gm_createShader(const char* shaderFilename, GLenum shaderType);

GLuint gm_createShaderProgram(size_t shaderCount, ...);

void gm_setActiveShaderProgram(GLuint shaderProgram);

#endif