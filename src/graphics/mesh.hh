#pragma once

#include "../util/def.hh"

#include <iris/vec3.hh>
#include <vector>
#include <array>
#include <iris/quaternion.hh>
#include <QtGui/QOpenGLFunctions_4_5_Core>

struct Mesh : private QOpenGLFunctions_4_5_Core
{
	Mesh() = default;
	~Mesh();
	
	Mesh(float const *verts, size_t vertsSize, float const *uvs, size_t uvsSize);
	
	void use();
	
	uint32_t vao = 0, vboV = 0, vboU = 0, vboN = 0, numVerts = 0;
	std::vector<IR::vec3<float>> verticies;
};
