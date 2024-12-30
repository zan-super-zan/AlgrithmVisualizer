#pragma once
#include "glad/glad.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include <vector>
#include <memory>

struct BufferElement
{
	uint32_t Type;
	uint32_t Count;
	bool Normalized;

	static uint32_t GetSizeOfType(uint32_t type)
	{
		switch(type)
		{
		case GL_FLOAT: return sizeof(float);
		case GL_UNSIGNED_INT: return sizeof(uint32_t);
		}
		return 0;
	}
};

class BufferLayout
{
public:
	BufferLayout()
		: m_Stride(0) { }

	void PushFloat(uint32_t count)
	{
		m_Elements.push_back({ GL_FLOAT, count, false });
		m_Stride += count * BufferElement::GetSizeOfType(GL_FLOAT);
	}

	void PushUInt(uint32_t count)
	{
		m_Elements.push_back({ GL_UNSIGNED_INT, count, false });
		m_Stride += count * BufferElement::GetSizeOfType(GL_UNSIGNED_INT);
	}

	const std::vector<BufferElement>& GetElements()const { return m_Elements; }
	const uint32_t GetStride()const { return m_Stride; }
private:
	std::vector<BufferElement> m_Elements;
	uint32_t m_Stride;
};

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void Bind()const;
	void Unbind()const;

	void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vb, const BufferLayout& layout);
	void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& ib);
	
	const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }

private:
	uint32_t m_Id = 0;

	std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
	std::shared_ptr<IndexBuffer> m_IndexBuffer;
};

