#include "shader.hh"

#include "../util/util.hh"

Shader::Shader(std::string const &vertShader, std::string const &fragShader)
{
	uint32_t vertHandle = glCreateShader(GL_VERTEX_SHADER), fragHandle = glCreateShader(GL_FRAGMENT_SHADER);
	this->shaderHandle = glCreateProgram();
	char const *vertSource = vertShader.data(), *fragSource = fragShader.data();
	glShaderSource(vertHandle, 1, &vertSource, nullptr);
	glShaderSource(fragHandle, 1, &fragSource, nullptr);
	glCompileShader(vertHandle);
	int32_t success = 0;
	glGetShaderiv(vertHandle, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		int32_t maxLen = 0;
		glGetShaderiv(vertHandle, GL_INFO_LOG_LENGTH, &maxLen);
		std::vector<char> error;
		error.resize(maxLen * sizeof(GLchar));
		glGetShaderInfoLog(vertHandle, maxLen, &maxLen, error.data());
		std::string errorStr{error.begin(), error.end()};
		printf("Shader failed to compile: %s\n", errorStr.data());
		return;
	}
	glCompileShader(fragHandle);
	success = 0;
	glGetShaderiv(fragHandle, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		int32_t maxLen = 0;
		glGetShaderiv(fragHandle, GL_INFO_LOG_LENGTH, &maxLen);
		std::vector<char> error;
		error.resize(maxLen * sizeof(GLchar));
		glGetShaderInfoLog(fragHandle, maxLen, &maxLen, error.data());
		std::string errorStr{error.begin(), error.end()};
		printf("Shader failed to compile: %s\n", errorStr.data());
		return;
	}
	glAttachShader(this->shaderHandle, vertHandle);
	glAttachShader(this->shaderHandle, fragHandle);
	glLinkProgram(this->shaderHandle);
	success = 0;
	glGetProgramiv(this->shaderHandle, GL_LINK_STATUS, &success);
	if(!success)
	{
		int32_t maxLen = 0;
		glGetShaderiv(this->shaderHandle, GL_INFO_LOG_LENGTH, &maxLen);
		std::vector<char> error;
		error.resize(maxLen * sizeof(GLchar));
		glGetShaderInfoLog(this->shaderHandle, maxLen, &maxLen, error.data());
		std::string errorStr{error.begin(), error.end()};
		printf("Shader program %u failed to link\n", this->shaderHandle);
		return;
	}
	glDetachShader(this->shaderHandle, vertHandle);
	glDetachShader(this->shaderHandle, fragHandle);
	glDeleteShader(vertHandle);
	glDeleteShader(fragHandle);
}

Shader::Shader(std::string const &compShader)
{
	uint32_t compHandle = glCreateShader(GL_COMPUTE_SHADER);
	this->shaderHandle = glCreateProgram();
	char const *compSource = compShader.data();
	glShaderSource(compHandle, 1, &compSource, nullptr);
	glCompileShader(compHandle);
	int32_t success = 0;
	glGetShaderiv(compHandle, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		int32_t maxLen = 0;
		glGetShaderiv(compHandle, GL_INFO_LOG_LENGTH, &maxLen);
		std::vector<char> error;
		error.resize(maxLen * sizeof(GLchar));
		glGetShaderInfoLog(compHandle, maxLen, &maxLen, error.data());
		std::string errorStr{error.begin(), error.end()};
		printf("Shader failed to compile: %s\n", errorStr.data());
		return;
	}
	
	glAttachShader(this->shaderHandle, compHandle);
	glLinkProgram(this->shaderHandle);
	success = 0;
	glGetProgramiv(this->shaderHandle, GL_LINK_STATUS, &success);
	if(!success)
	{
		int32_t maxLen = 0;
		glGetShaderiv(this->shaderHandle, GL_INFO_LOG_LENGTH, &maxLen);
		std::vector<char> error;
		error.resize(maxLen * sizeof(GLchar));
		glGetShaderInfoLog(this->shaderHandle, maxLen, &maxLen, error.data());
		std::string errorStr{error.begin(), error.end()};
		printf("Shader program %u failed to link\n", this->shaderHandle);
		return;
	}
	glDetachShader(this->shaderHandle, compHandle);
	glDeleteShader(compHandle);
}

Shader::~Shader()
{
	glDeleteProgram(this->shaderHandle);
}

void Shader::use()
{
	glUseProgram(this->shaderHandle);
}

void Shader::sendFloat(std::string const &location, float val)
{
	glUniform1f(glGetUniformLocation(this->shaderHandle, location.data()), val);
}

void Shader::sendInt(std::string const &location, int32_t val)
{
	glUniform1i(glGetUniformLocation(this->shaderHandle, location.data()), val);
}

void Shader::sendUInt(std::string const &location, uint32_t val)
{
	glUniform1ui(glGetUniformLocation(this->shaderHandle, location.data()), val);
}

void Shader::sendVec2f(std::string const &location, IR::vec2<float> const &val)
{
	glUniform2fv(glGetUniformLocation(this->shaderHandle, location.data()), 1, val.data);
}

void Shader::sendVec3f(std::string const &location, IR::vec3<float> const &val)
{
	glUniform3fv(glGetUniformLocation(this->shaderHandle, location.data()), 1, val.data);
}

void Shader::sendVec4f(std::string const &location, IR::vec4<float> const &val)
{
	glUniform4fv(glGetUniformLocation(this->shaderHandle, location.data()), 1, val.data);
}

void Shader::sendMat3f(std::string const &location, IR::mat3x3<float> const &val)
{
	glUniformMatrix3fv(glGetUniformLocation(this->shaderHandle, location.data()), 1, GL_FALSE, &val[0][0]);
}

void Shader::sendMat4f(std::string const &location, IR::mat4x4<float> const &val)
{
	glUniformMatrix4fv(glGetUniformLocation(this->shaderHandle, location.data()), 1, GL_FALSE, &val[0][0]);
}
