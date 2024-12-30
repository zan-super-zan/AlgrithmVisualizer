#include "IndexBuffer.h"
#include "GLCheck.h"
#include "glad/glad.h"

IndexBuffer::IndexBuffer(const void* data, uint32_t count, uint32_t usage)
	:m_Count(count)
{
	GLCheck(glGenBuffers(1, &m_BufferId));
	GLCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferId));
	GLCheck(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), data, usage));
	GLCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

IndexBuffer::~IndexBuffer()
{
	GLCheck(glDeleteBuffers(1, &m_BufferId));
}

void IndexBuffer::Bind() const
{
	GLCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferId));
}

void IndexBuffer::Unbind() const
{
	GLCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

void IndexBuffer::UpdateData(uint32_t offset, uint32_t size, const void* data)
{
	GLCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferId));
	GLCheck(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data));
	GLCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
