#include "mesh.hh"
#include "../util/util.hh"

#include <glad/glad.h>
#include <iris/mat4.hh>

Mesh::~Mesh()
{
	glDeleteBuffers(1, &this->vboV);
	glDeleteBuffers(1, &this->vboU);
	glDeleteBuffers(1, &this->vboN);
	glDeleteVertexArrays(1, &this->vao);
}

Mesh::Mesh(float const *verts, size_t vertsSize, float const *uvs, size_t uvsSize)
{
	size_t constexpr vertexStride = 3 * sizeof(float);
	size_t constexpr uvStride = 2 * sizeof(float);
	
	this->numVerts = static_cast<uint32_t>(vertsSize);
	
	glCreateVertexArrays(1, &this->vao);
	glCreateBuffers(1, &this->vboV);
	glCreateBuffers(1, &this->vboU);
	
	glNamedBufferData(this->vboV, vertsSize * sizeof(float), verts, GL_STATIC_DRAW);
	glVertexArrayAttribBinding(this->vao, 0, 0);
	glVertexArrayVertexBuffer(this->vao, 0, this->vboV, 0, vertexStride);
	glEnableVertexArrayAttrib(this->vao, 0);
	glVertexArrayAttribFormat(this->vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
	
	glNamedBufferData(this->vboU, uvsSize * sizeof(float), uvs, GL_STATIC_DRAW);
	glVertexArrayAttribBinding(this->vao, 1, 1);
	glVertexArrayVertexBuffer(this->vao, 1, this->vboU, 0, uvStride);
	glEnableVertexArrayAttrib(this->vao, 1);
	glVertexArrayAttribFormat(this->vao, 1, 2, GL_FLOAT, GL_FALSE, 0);
}

void Mesh::use()
{
	glBindVertexArray(this->vao);
}
