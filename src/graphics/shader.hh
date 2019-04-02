#pragma once

#include "../util/def.hh"

#include <string>
#include <iris/vec2.hh>
#include <iris/vec3.hh>
#include <iris/vec4.hh>
#include <iris/mat3.hh>
#include <iris/mat4.hh>
#include <QtGui/QOpenGLFunctions_4_5_Core>

struct Shader : private QOpenGLFunctions_4_5_Core
{
	Shader(std::string const &vertShader, std::string const &fragShader);
	Shader(std::string const &compShader);
	~Shader();
	void use();
	void sendFloat(std::string const &location, float val);
	void sendInt(std::string const &location, int32_t val);
	void sendUInt(std::string const &location, uint32_t val);
	void sendVec2f(std::string const &location, IR::vec2<float> const &val);
	void sendVec3f(std::string const &location, IR::vec3<float> const &val);
	void sendVec4f(std::string const &location, IR::vec4<float> const &val);
	void sendMat3f(std::string const &location, IR::mat3x3<float> const &val);
	void sendMat4f(std::string const &location, IR::mat4x4<float> const &val);

private:
	uint32_t shaderHandle = 0;
};
