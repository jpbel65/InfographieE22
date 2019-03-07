#include "Shader.h"
#include "ofMain.h"
#include <iostream>
#include <string>

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type); // (position in the pipeline)
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char *message = (char*) alloca(length * sizeof(char)); // malloc sur stack
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Shader compilation failed: " << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}
	return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader, const std::string& geometryShader)
{
	unsigned int programID = glCreateProgram();
	unsigned int vertexShaderID = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fragmentShaderID = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
	unsigned int geometryShaderID = geometryShader.compare("") == 0 ? 0 : CompileShader(GL_GEOMETRY_SHADER, geometryShader);


	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	if(geometryShaderID) glAttachShader(programID, geometryShaderID);
	glLinkProgram(programID);
	glValidateProgram(programID);

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
	if (geometryShaderID) glDeleteShader(geometryShaderID);
	return programID;
}

std::string* Shader::importShader(const std::string& filePath) {
	std::ifstream fileStream{ filePath };
	return new string{ istreambuf_iterator<char>(fileStream), istreambuf_iterator<char>() };
}

Shader::Shader()
{
	
}

Shader::Shader(const std::string& vertexSource, const std::string& fragmentSource, const std::string& geometrySource) {
	std::string *vertexShader = importShader(vertexSource);
	std::string *fragmentShader = importShader(fragmentSource);
	std::string *geometryShader = geometrySource.compare("") == 0 ? &string("") : importShader(geometrySource);

	programID = CreateShader(*vertexShader, *fragmentShader,  *geometryShader);

	delete vertexShader;
	delete fragmentShader;
	delete geometryShader;
}


Shader::~Shader()
{
}
