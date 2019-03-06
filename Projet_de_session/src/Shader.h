#pragma once
#include <string>

class Shader
{
public:
	static unsigned int CompileShader(unsigned int type, const std::string& source);
	static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

	Shader();
	~Shader();
};

