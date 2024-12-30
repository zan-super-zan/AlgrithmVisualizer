#include "VertexArray.h"
#include "GLCheck.h"
#include "glad/glad.h"
#include <cassert>

VertexArray::VertexArray()
{
	GLCheck(glGenVertexArrays(1, &m_Id));
}

VertexArray::~VertexArray()
{
	GLCheck(glDeleteVertexArrays(1, &m_Id));
}

void VertexArray::Bind() const
{
	GLCheck(glBindVertexArray(m_Id));
}

void VertexArray::Unbind() const
{
	GLCheck(glBindVertexArray(0));
}

void VertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vb, const BufferLayout& layout)
{
	assert(layout.GetElements().size() && "Vertex buffer has no layouts");

	Bind();
	vb->Bind();

	const auto& elements = layout.GetElements();
	uint32_t offset = 0;
	for (uint32_t i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];

		GLCheck(glEnableVertexAttribArray(i));
		GLCheck(glVertexAttribPointer(i, element.Count, element.Type, false, layout.GetStride(), (const void*)offset));

		offset += element.Count * BufferElement::GetSizeOfType(element.Type);
	}
	m_VertexBuffers.push_back(vb);
}

void VertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& ib)
{
	Bind();
	ib->Bind();

	m_IndexBuffer = ib;
}
