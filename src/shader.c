#include "shader.h"
#include "debug.h"

char* readEntireFile(const char* filename)
{
	FILE* file = fopen(filename, "rb");
	if (!file)
	{
		gm_setError(ERR_CODE, ERR_NOFIL);
		return NULL;
	}

	fseek(file, 0, SEEK_END);
	size_t fileLength = ftell(file);
	rewind(file);

	char * fileContents = malloc(fileLength + 1);
	if (!fileContents)
	{
		gm_setError(ERR_CODE, ERR_NOMEM);
		fclose(file);
		return NULL;
	}

	fread(fileContents, 1, fileLength, file);
	fileContents[fileLength] = '\0';
	fclose(file);

	return fileContents;
}

GLuint gm_createShader(const char* shaderFilename, GLenum shaderType)
{
	const char* shaderSource = readEntireFile(shaderFilename);
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
	for (int i = 0; i < shaderCount; i++)
	{
		GLuint currentShader = va_arg(args, GLuint);
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
