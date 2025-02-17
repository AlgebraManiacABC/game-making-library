#ifndef SHADERS_H
#define SHADERS_H

#define GLEW_STATIC
#include <stdio.h>
#include <GL/glew.h>
#include <stdarg.h>

GLuint gm_createShader(const char* shaderFilename, GLenum shaderType);

GLuint gm_createShaderProgram(size_t shaderCount, ...);

void gm_setActiveShaderProgram(GLuint shaderProgram);

#endif