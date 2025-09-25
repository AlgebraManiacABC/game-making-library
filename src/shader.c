#include "shader.h"
#include "debug.h"
#include "files.h"

GLuint gm_createShader(const char* shaderFilename, GLenum shaderType)
{
	const char* shaderSource = _gm_readEntireTextFile(shaderFilename);
	if (!shaderSource) return 0;
	GLuint shaderID = glCreateShader(shaderType);
	glShaderSource(shaderID, 1, &shaderSource, NULL);
	glCompileShader(shaderID);
	GLint success;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char info_log[512] = { 0 };
		glGetShaderInfoLog(shaderID, 512, NULL, info_log);
		gm_setError(ERR_MESG, "Shader did not compile: %s", info_log);
		return 0;
	}
	return shaderID;
}

GLuint gm_createShaderProgram(size_t shaderCount, ...)
{
	GLuint shaderProgram = glCreateProgram();
	va_list args;
	va_start(args, shaderCount);
	for (GLuint i = 0; i < shaderCount; i++)
	{
		GLuint currentShader = va_arg(args, GLuint);
		if (!currentShader || !glIsShader(currentShader))
		{
			gm_setError(ERR_MESG, "Failure creating shader (ID %d)! OpenGL says: %s", currentShader, glGetError());
			return 0;
		}
		glAttachShader(shaderProgram, currentShader);
	}
	glLinkProgram(shaderProgram);
	GLint success;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		char info_log[512] = { 0 };
		glGetProgramInfoLog(shaderProgram, 512, NULL, info_log);
		gm_setError(ERR_MESG, "Shader linking failure: %s", info_log);
		return 0;
	}
	return shaderProgram;
}

void gm_setActiveShaderProgram(GLuint shaderProgram)
{
	glUseProgram(shaderProgram);
}
