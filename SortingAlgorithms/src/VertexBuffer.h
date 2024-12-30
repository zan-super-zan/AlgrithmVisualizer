#pragma once
#include <cstdint>

class VertexBuffer
{
public:
	VertexBuffer(const void* data, uint32_t size, uint32_t usage);
	~VertexBuffer();

	void Bind()const;
	void Unind()const;

	void UpdateData(uint32_t offset, uint32_t size, const void* data);

	uint32_t GetID()const { return m_BufferId; }
private:
	uint32_t m_BufferId = 0;

};

