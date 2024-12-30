#pragma once
#include "SortAlgorithm.h"

#include <memory>
#include <chrono>
#include <mutex>


enum class Sorters
{
	Bubble = 0, Quick, Merge
};

class SortContext
{
public:
	SortContext() : m_Sorter(std::make_unique<BubbleSort>()) {}

	SortContext(std::unique_ptr<Sorter> sorter)
		: m_Sorter(std::move(sorter))
	{
	}

	void SetSorter(Sorters sort)
	{
		switch (sort)
		{
		case Sorters::Bubble: m_Sorter = std::make_unique<BubbleSort>(); break;
		case Sorters::Quick:  m_Sorter = std::make_unique<QuickSort>();  break;
		case Sorters::Merge:  m_Sorter = std::make_unique<MergeSort>();  break;
		}
	}

	void Sort(std::vector<FRectangle>& data, bool stopSort = false)
	{
		m_Sorter->Sort(data, stopSort);
	}
private:
	std::unique_ptr<Sorter> m_Sorter;
	std::mutex m_SoterMutex;
};