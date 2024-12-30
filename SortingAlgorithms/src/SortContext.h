#pragma once
#include "SortAlgorithm.h"

#include <memory>
#include <chrono>
#include <mutex>


namespace Sort
{
	enum Sorters
	{
		Bubble = 0, Quick, Merge
	};
}

class SortContext
{
public:
	SortContext() : m_Sorter(std::make_unique<BubbleSort>()){ }

	SortContext(std::unique_ptr<Sorter> sorter)
		: m_Sorter(std::move(sorter))
	{
	}

	void SetSorter(Sort::Sorters sort)
	{
		//std::lock_guard<std::mutex> lock(m_SoterMutex);
		switch (sort)
		{
		case Sort::Bubble: m_Sorter = std::make_unique<BubbleSort>(); break;
		case Sort::Quick:  m_Sorter = std::make_unique<QuickSort>();  break;
		case Sort::Merge:  m_Sorter = std::make_unique<MergeSort>();  break;
		}
	}

	void Sort(std::vector<FRectangle>& data)
	{
		m_Sorter->Sort(data);
	}
private:
	std::unique_ptr<Sorter> m_Sorter;
	std::mutex m_SoterMutex;
};