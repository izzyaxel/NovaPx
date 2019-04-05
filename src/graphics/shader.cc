#include "shader.hh"

#include "../util/util.hh"

Shader::Shader(std::string const &vertShader, std::string const &fragShader)
{
	this->initializeOpenGLFunctions();
	uint32_t vertHandle = this->glCreateShader(GL_VERTEX_SHADER), fragHandle = this->glCreateShader(GL_FRAGMENT_SHADER);
	this->shaderHandle = this->glCreateProgram();
	char const *vertSource = vertShader.data(), *fragSource = fragShader.data();
	this->glShaderSource(vertHandle, 1, &vertSource, nullptr);
	this->glShaderSource(fragHandle, 1, &fragSource, nullptr);
	this->glCompileShader(vertHandle);
	int32_t success = 0;
	this->glGetShaderiv(vertHandle, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		int32_t maxLen = 0;
		this->glGetShaderiv(vertHandle, GL_INFO_LOG_LENGTH, &maxLen);
		std::vector<char> error;
		error.resize(maxLen * sizeof(GLchar));
		this->glGetShaderInfoLog(vertHandle, maxLen, &maxLen, error.data());
		std::string errorStr{error.begin(), error.end()};
		printf("Shader failed to compile: %s\n", errorStr.data());
		return;
	}
	this->glCompileShader(fragHandle);
	success = 0;
	this->glGetShaderiv(fragHandle, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		int32_t maxLen = 0;
		this->glGetShaderiv(fragHandle, GL_INFO_LOG_LENGTH, &maxLen);
		std::vector<char> error;
		error.resize(maxLen * sizeof(GLchar));
		this->glGetShaderInfoLog(fragHandle, maxLen, &maxLen, error.data());
		std::string errorStr{error.begin(), error.end()};
		printf("Shader failed to compile: %s\n", errorStr.data());
		return;
	}
	this->glAttachShader(this->shaderHandle, vertHandle);
	this->glAttachShader(this->shaderHandle, fragHandle);
	this->glLinkProgram(this->shaderHandle);
	success = 0;
	this->glGetProgramiv(this->shaderHandle, GL_LINK_STATUS, &success);
	if(!success)
	{
		int32_t maxLen = 0;
		this->glGetShaderiv(this->shaderHandle, GL_INFO_LOG_LENGTH, &maxLen);
		std::vector<char> error;
		error.resize(maxLen * sizeof(GLchar));
		this->glGetShaderInfoLog(this->shaderHandle, maxLen, &maxLen, error.data());
		std::string errorStr{error.begin(), error.end()};
		printf("Shader program %u failed to link\n", this->shaderHandle);
		return;
	}
	this->glDetachShader(this->shaderHandle, vertHandle);
	this->glDetachShader(this->shaderHandle, fragHandle);
	this->glDeleteShader(vertHandle);
	this->glDeleteShader(fragHandle);
}

Shader::Shader(std::string const &compShader)
{
	this->initializeOpenGLFunctions();
	uint32_t compHandle = this->glCreateShader(GL_COMPUTE_SHADER);
	this->shaderHandle = this->glCreateProgram();
	char const *compSource = compShader.data();
	this->glShaderSource(compHandle, 1, &compSource, nullptr);
	this->glCompileShader(compHandle);
	int32_t success = 0;
	this->glGetShaderiv(compHandle, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		int32_t maxLen = 0;
		this->glGetShaderiv(compHandle, GL_INFO_LOG_LENGTH, &maxLen);
		std::vector<char> error;
		error.resize(maxLen * sizeof(GLchar));
		this->glGetShaderInfoLog(compHandle, maxLen, &maxLen, error.data());
		std::string errorStr{error.begin(), error.end()};
		printf("Shader failed to compile: %s\n", errorStr.data());
		return;
	}
	
	this->glAttachShader(this->shaderHandle, compHandle);
	this->glLinkProgram(this->shaderHandle);
	success = 0;
	this->glGetProgramiv(this->shaderHandle, GL_LINK_STATUS, &success);
	if(!success)
	{
		int32_t maxLen = 0;
		this->glGetShaderiv(this->shaderHandle, GL_INFO_LOG_LENGTH, &maxLen);
		std::vector<char> error;
		error.resize(maxLen * sizeof(GLchar));
		this->glGetShaderInfoLog(this->shaderHandle, maxLen, &maxLen, error.data());
		std::string errorStr{error.begin(), error.end()};
		printf("Shader program %u failed to link\n", this->shaderHandle);
		return;
	}
	this->glDetachShader(this->shaderHandle, compHandle);
	this->glDeleteShader(compHandle);
}

Shader::~Shader()
{
	this->glDeleteProgram(this->shaderHandle);
}

void Shader::use()
{
	this->glUseProgram(this->shaderHandle);
}

void Shader::sendFloat(std::string const &location, float val)
{
	this->glUniform1f(this->glGetUniformLocation(this->shaderHandle, location.data()), val);
}

void Shader::sendInt(std::string const &location, int32_t val)
{
	this->glUniform1i(this->glGetUniformLocation(this->shaderHandle, location.data()), val);
}

void Shader::sendUInt(std::string const &location, uint32_t val)
{
	this->glUniform1ui(this->glGetUniformLocation(this->shaderHandle, location.data()), val);
}

void Shader::sendVec2f(std::string const &location, IR::vec2<float> const &val)
{
	this->glUniform2fv(this->glGetUniformLocation(this->shaderHandle, location.data()), 1, val.data);
}

void Shader::sendVec3f(std::string const &location, IR::vec3<float> const &val)
{
	this->glUniform3fv(this->glGetUniformLocation(this->shaderHandle, location.data()), 1, val.data);
}

void Shader::sendVec4f(std::string const &location, IR::vec4<float> const &val)
{
	this->glUniform4fv(this->glGetUniformLocation(this->shaderHandle, location.data()), 1, val.data);
}

void Shader::sendMat3f(std::string const &location, IR::mat3x3<float> const &val)
{
	this->glUniformMatrix3fv(this->glGetUniformLocation(this->shaderHandle, location.data()), 1, GL_FALSE, &val[0][0]);
}

void Shader::sendMat4f(std::string const &location, IR::mat4x4<float> const &val)
{
	this->glUniformMatrix4fv(this->glGetUniformLocation(this->shaderHandle, location.data()), 1, GL_FALSE, &val[0][0]);
}
