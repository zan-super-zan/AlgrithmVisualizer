#include "BatchRenderer.h"
#include "glad/glad.h"
#include "GLCheck.h"

BatchRenderer::BatchRenderer(uint32_t maxQuads)
	: m_MaxQuads(maxQuads)
{
	m_Buffer = new Vertex[4 * m_MaxQuads];

	m_BufferLayout.PushFloat(3);   // Position 
	m_BufferLayout.PushFloat(3);   // Color
	m_BufferLayout.PushFloat(2);   // TexCoord
}

BatchRenderer::~BatchRenderer()
{
	Shutdown();
	delete[] m_Buffer;
}

void BatchRenderer::Init()
{
	m_VertexArray = std::make_unique<VertexArray>();
	m_VertexArray->Bind();

	m_VertexBuffer = std::make_shared<VertexBuffer>(nullptr, m_MaxQuads * 4 * sizeof(Vertex), GL_DYNAMIC_DRAW);
	m_VertexBuffer->Bind();
	
	m_VertexArray->AddVertexBuffer(m_VertexBuffer, m_BufferLayout);

	std::vector<uint32_t> indices;
	indices.reserve(m_MaxQuads * 6);


	for (uint32_t i = 0; i < m_MaxQuads; i++)
	{
		uint32_t offset = i * 4;
		indices.push_back(offset + 0);
		indices.push_back(offset + 1);
		indices.push_back(offset + 2);
		indices.push_back(offset + 2);
		indices.push_back(offset + 3);
		indices.push_back(offset + 0);
	}
	m_IndexBuffer = std::make_shared<IndexBuffer>(indices.data(), indices.size(), GL_STATIC_DRAW);
	m_IndexBuffer->Bind();
	m_VertexArray->SetIndexBuffer(m_IndexBuffer);
	m_VertexArray->Unbind();
}

void BatchRenderer::Shutdown()
{
}

void BatchRenderer::BeginBatch()
{
	m_BufferPtr = m_Buffer;
	m_QuadCount = 0;
}

void BatchRenderer::SubmitRect(const FRectangle& rect, const glm::vec3& color)
{
	if (m_QuadCount >= m_MaxQuads)
		return; 

	// 1. Bottom-left
	m_BufferPtr->Position = { rect.X, rect.Y, 0.0f };
	m_BufferPtr->Color = color;
	m_BufferPtr++;

	// 2. Top-left
	m_BufferPtr->Position = { rect.X, rect.Y + rect.Height, 0.0f};
	m_BufferPtr->Color = color;
	m_BufferPtr++;

	// 3. Top-right
	m_BufferPtr->Position = { rect.X + rect.Width, rect.Y + rect.Height, 0.0f };
	m_BufferPtr->Color = color;
	m_BufferPtr++;

	// 4. Bottom-right
	m_BufferPtr->Position = { rect.X + rect.Width, rect.Y, 0.0f };
	m_BufferPtr->Color = color;
	m_BufferPtr++;

	m_QuadCount++;
}

void BatchRenderer::EndBatch()
{
	std::size_t dataSize = (reinterpret_cast<uint8_t*>(m_BufferPtr) - reinterpret_cast<uint8_t*>(m_Buffer));
	m_VertexBuffer->Bind();
	GLCheck(glBufferSubData(GL_ARRAY_BUFFER, 0, dataSize, m_Buffer));
}

void BatchRenderer::Flush()
{
	if (m_QuadCount == 0)
		return;

	m_VertexArray->Bind();
	GLCheck(glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr));
	m_VertexArray->Unbind();
}
