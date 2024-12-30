#pragma once
#include <cstdint>

class IndexBuffer
{
public:

	IndexBuffer(const void* data, uint32_t count, uint32_t usage);
	~IndexBuffer();


	void Bind()const;
	void Unbind()const;

	void UpdateData(uint32_t offset, uint32_t size, const void* data);

	uint32_t GetCount()const { return m_Count; }

private:
	uint32_t m_BufferId = 0;
	uint32_t m_Count; // indices

};

