#include "mesh.hh"
#include "../util/util.hh"

#include <iris/mat4.hh>

Mesh::~Mesh()
{
	this->glDeleteBuffers(1, &this->vboV);
	this->glDeleteBuffers(1, &this->vboU);
	this->glDeleteBuffers(1, &this->vboN);
	this->glDeleteVertexArrays(1, &this->vao);
}

Mesh::Mesh(float const *verts, size_t vertsSize, float const *uvs, size_t uvsSize)
{
	this->initializeOpenGLFunctions();
	size_t constexpr vertexStride = 3 * sizeof(float);
	size_t constexpr uvStride = 2 * sizeof(float);
	
	this->numVerts = static_cast<uint32_t>(vertsSize);
	
	this->glCreateVertexArrays(1, &this->vao);
	this->glCreateBuffers(1, &this->vboV);
	this->glCreateBuffers(1, &this->vboU);
	
	this->glNamedBufferData(this->vboV, vertsSize * sizeof(float), verts, GL_STATIC_DRAW);
	this->glVertexArrayAttribBinding(this->vao, 0, 0);
	this->glVertexArrayVertexBuffer(this->vao, 0, this->vboV, 0, vertexStride);
	this->glEnableVertexArrayAttrib(this->vao, 0);
	this->glVertexArrayAttribFormat(this->vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
	
	this->glNamedBufferData(this->vboU, uvsSize * sizeof(float), uvs, GL_STATIC_DRAW);
	this->glVertexArrayAttribBinding(this->vao, 1, 1);
	this->glVertexArrayVertexBuffer(this->vao, 1, this->vboU, 0, uvStride);
	this->glEnableVertexArrayAttrib(this->vao, 1);
	this->glVertexArrayAttribFormat(this->vao, 1, 2, GL_FLOAT, GL_FALSE, 0);
}

void Mesh::use()
{
	this->glBindVertexArray(this->vao);
}
