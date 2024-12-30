#include "SortAlgorithm.h"
#include <thread>

void BubbleSort::sortImpl(std::vector<FRectangle>& data)
{
	bool swapped = true;
	for (std::size_t i = 0; i < data.size() - 1 && swapped; ++i)
	{
		swapped = false;
		for (std::size_t j = 0; j < data.size() - 1 - i; ++j)
		{
			if (data[j].Height > data[j + 1].Height)
			{
				std::swap(data[j].Height, data[j + 1].Height);
				swapped = true;
			}
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
	}
}

void QuickSort::sortImpl(std::vector<FRectangle>& data)
{
	quickSortRecursive(data, 0, data.size() - 1);
}

void QuickSort::quickSortRecursive(std::vector<FRectangle>& arr, int32_t low, int32_t high)
{
	if (low < high)
	{
		int pivotIndex = partition(arr, low, high);
		// Recur on left part
		quickSortRecursive(arr, low, pivotIndex - 1);
		// Recur on right part
		quickSortRecursive(arr, pivotIndex + 1, high);
	}
}

int32_t QuickSort::partition(std::vector<FRectangle>& arr, int32_t low, int32_t high)
{
	int pivot = arr[high].Height;
	int i = (low - 1);

	for (int j = low; j < high; j++)
	{
		if (arr[j].Height < pivot)
		{
			i++;
			std::swap(arr[i].Height, arr[j].Height);
		}
	}
	std::swap(arr[i + 1].Height, arr[high].Height);
	std::this_thread::sleep_for(std::chrono::milliseconds(16));

	return (i + 1);
}

void MergeSort::sortImpl(std::vector<FRectangle>& data)
{
	MergeSortRecursive(data, 0, data.size() - 1);
}

void MergeSort::MergeSortRecursive(std::vector<FRectangle>& data, int32_t left, int32_t right)
{
	if (left < right) {
		int mid = left + (right - left) / 2;
		MergeSortRecursive(data, left, mid);
		MergeSortRecursive(data, mid + 1, right);
		Merge(data, left, mid, right);
	}
}

void MergeSort::Merge(std::vector<FRectangle>& data, int32_t left, int32_t mid, int32_t right)
{
	int32_t n1 = mid - left + 1;
	int32_t n2 = right - mid;

	// Create temporary vectors
	std::vector<float> L(n1);
	std::vector<float> R(n2);

	// Copy data to temporary vectors
	for (int32_t i = 0; i < n1; ++i)
		L[i] = data[left + i].Height;
	for (int32_t j = 0; j < n2; ++j)
		R[j] = data[mid + 1 + j].Height;

	
	int32_t i = 0;    // Initial index of first subvector
	int32_t j = 0;    // Initial index of second subvector
	int32_t k = left; // Initial index of merged subvector

	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			data[k].Height = L[i];
			++i;
		}
		else
		{
			data[k].Height = R[j];
			++j;
		}
		++k;
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
	}

	while (i < n1) 
	{
		data[k].Height = L[i];
		++i;
		++k;
	}

	while (j < n2)
	{
		data[k].Height = R[j];
		++j;
		++k;
	}
}

