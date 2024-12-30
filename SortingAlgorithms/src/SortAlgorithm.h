#pragma once

#include "Rectangle.h"

#include <functional>
#include <algorithm>
#include <chrono>
#include <vector>
#include <iostream>

class Sorter
{
public:
	virtual ~Sorter() = default;

	void Sort(std::vector<FRectangle>& data)
	{
		sortImpl(data);
	}

protected:
	virtual void sortImpl(std::vector<FRectangle>& data) = 0;

protected:
	std::chrono::milliseconds m_Delay{ 16 };
};

class BubbleSort : public Sorter
{
protected:
	void sortImpl(std::vector<FRectangle>& data) override;
};


class QuickSort : public Sorter
{
protected:
	void sortImpl(std::vector<FRectangle>& data) override;

private:
	void quickSortRecursive(std::vector<FRectangle>& arr, int32_t low, int32_t high);
	int32_t partition(std::vector<FRectangle>& arr, int32_t low, int32_t high);
};

class MergeSort : public Sorter
{
protected:
	void sortImpl(std::vector<FRectangle>& data) override;

private:
	void MergeSortRecursive(std::vector<FRectangle>& data, int32_t left, int32_t right);
	void Merge(std::vector<FRectangle>& data, int32_t left, int32_t mid, int32_t right);
};


