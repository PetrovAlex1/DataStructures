#pragma once
#include <unordered_set>
#include <stdexcept>

template <typename T>
class DebugAllocator
{
private:
	std::unordered_set<T*> allocations;
public:

	T* allocate(const size_t& size)
	{
		T* newArr = new T[size];
		allocations.insert(newArr);
		return newArr;
	}

	void free(T* arr)
	{
		if (allocations.count(arr) != 1)
		{
			throw std::invalid_argument("Arr is not allocated.");
		}

		allocations.erase(arr);
		delete[] arr;
	}

	size_t getAllocationsCount() const
	{
		return allocations.size();
	}
};