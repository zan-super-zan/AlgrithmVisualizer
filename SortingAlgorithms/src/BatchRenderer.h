#pragma once
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "Vertex.h"
#include "Rectangle.h"

#include <memory>

class BatchRenderer
{
public:
	BatchRenderer(uint32_t maxQuads);
	~BatchRenderer();

	void Init();
	void Shutdown();
	
	void BeginBatch();
	void SubmitRect(const FRectangle& rect, const glm::vec3& color);

	void EndBatch();
	void Flush();

private:
	std::shared_ptr<VertexBuffer> m_VertexBuffer = nullptr;
	std::shared_ptr<IndexBuffer>  m_IndexBuffer  = nullptr;
	std::unique_ptr<VertexArray>  m_VertexArray  = nullptr;
	BufferLayout m_BufferLayout;

	uint32_t m_MaxQuads = 0;
	uint32_t m_QuadCount = 0;

	Vertex* m_Buffer = nullptr;
	Vertex* m_BufferPtr = nullptr;
};

