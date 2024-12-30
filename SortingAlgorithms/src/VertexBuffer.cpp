#include "VertexBuffer.h"
#include "GLCheck.h"
#include "glad/glad.h"

VertexBuffer::VertexBuffer(const void* data, uint32_t size, uint32_t usage)
{
	GLCheck(glGenBuffers(1, &m_BufferId));
	GLCheck(glBindBuffer(GL_ARRAY_BUFFER, m_BufferId));
	GLCheck(glBufferData(GL_ARRAY_BUFFER, size, data, usage));
	GLCheck(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

VertexBuffer::~VertexBuffer()
{
	GLCheck(glDeleteBuffers(1, &m_BufferId));
}

void VertexBuffer::Bind() const
{
	GLCheck(glBindBuffer(GL_ARRAY_BUFFER, m_BufferId));
}

void VertexBuffer::Unind() const
{
	GLCheck(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void VertexBuffer::UpdateData(uint32_t offset, uint32_t size, const void* data)
{
	GLCheck(glBindBuffer(GL_ARRAY_BUFFER, m_BufferId));
	GLCheck(glBufferSubData(GL_ARRAY_BUFFER, offset, size, data));
	GLCheck(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
