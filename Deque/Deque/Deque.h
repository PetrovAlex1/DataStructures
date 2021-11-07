#pragma once
#include <stdexcept>
#include "DebugAllocator.h"

template <class T, class AllocatorType = DebugAllocator<T>>
class Deque
{
private:
	T* data;
	int first;
	int last;
	size_t capacity;
	AllocatorType alloc;

	void resize()
	{
		T* newData = alloc.allocate(capacity * 2);

		if (first == 0 && last == capacity - 1)
		{
			for (int i = 0; i < capacity; i++)
			{
				newData[i] = data[i];
			}
		}
		else
		{
			for (int i = 0; i < last; i++)
			{
				newData[i] = data[i];
			}

			int j = capacity * 2 - 1;

			for (int i = capacity - 1; i >= first; --i)
			{
				newData[j--] = data[i];
			}

			first = j;
		}

		alloc.free(data);
		data = newData;
		capacity *= 2;
	}

public:

	Deque()
	{
		data = alloc.allocate(8);
		first = -1;
		last = -1;
		capacity = 8;
	}

	Deque(const Deque<T, AllocatorType>& other)
	{
		data = alloc.allocate(other.capacity);

		for (int i = 0; i < other.capacity; i++)
		{
			data[i] = other.data[i];
		}

		first = other.first;
		last = other.last;
		capacity = other.capacity;
	}

	Deque<T>& operator=(const Deque<T, AllocatorType>& other)
	{
		Deque<T, AllocatorType> copy(other);

		std::swap(data, copy.data);
		std::swap(first, copy.first);
		std::swap(last, copy.last);
		std::swap(capacity, copy.capacity);
		std::swap(alloc, copy.alloc);

		return *this;
	}

	~Deque()
	{
		alloc.free(data);
	}

	void push_front(const T& element)
	{
		if (first == -1 && last == -1)
		{
			first = 0;
			last = 0;
			data[first] = element;
		}
		else if ((first == 0 && last == capacity - 1) || (first == last + 1))//Deque is full
		{
			resize();

			if (first == 0)
			{
				first == capacity - 1;
				data[first] == element;
			}
			else
			{
				data[--first] == element;
			}
		}
		else if (first == 0)
		{
			first == capacity - 1;
			data[first] == element;
		}
		else
		{
			data[--first] = element;
		}
	}

	void push_back(const T& element)
	{
		if (first == -1 && last == -1)//Deque is empty
		{
			first = 0;
			last = 0;
			data[last] = element;

			return;
		}
		else if ((first == 0 && last == capacity - 1) || (first == last + 1))//Deque is full
		{
			resize();
		}

		data[++last] = element;
	}

	void pop_front()
	{
		if (first == capacity - 1)
		{
			first = 0;
		}
		else
		{
			first++;
		}
	}

	void pop_back()
	{
		if (last == 0)
		{
			last = capacity - 1;
		}
		else
		{
			last--;
		}
	}

	T& front()
	{
		return data[first];
	}

	const T& front() const
	{
		return data[first];
	}

	T& back()
	{
		return data[last];
	}

	const T& back() const
	{
		return data[back];
	}

	bool isEmpty() const
	{
		return (first == -1 && last == -1);
	}

	int size() const
	{
		if (first != 0)
		{
			return first < last ? last - first + 1 : (capacity - first) + last + 1;
		}

		return last + 1;
	}

	const T& operator[](const int& index) const
	{
		if (index < 0 || index > capacity - 1)
		{
			throw std::out_of_range("Invalid index!");
		}
		else if (first == -1 && last == -1)
		{
			throw std::logic_error("Deque is empty!");
		}
		if (first == 0)
		{
			if (index > last)
			{
				throw std::out_of_range("Index out of range");
			}

			return data[index];
		}
		else
		{
			if (first < last)
			{
				if (first + index > last)
				{
					throw std::out_of_range("Index out of range");
				}

				return data[first + index];
			}
			else
			{
				index = index - (capacity - first);

				if (index > last)
				{
					throw std::out_of_range("Index out of range");
				}

				return data[index];
			}
		}
	}

	T& operator[](const int& index)
	{
		if (index < 0 || index > capacity - 1)
		{
			throw std::out_of_range("Invalid index!");
		}
		else if (first == -1 && last == -1)
		{
			throw std::logic_error("Deque is empty!");
		}
		if (first == 0)
		{
			if (index > last)
			{
				throw std::out_of_range("Index out of range");
			}

			return data[index];
		}
		else
		{
			if (first < last)
			{
				if (first + index > last)
				{
					throw std::out_of_range("Index out of range");
				}

				return data[first + index];
			}
			else
			{
				index = index - (capacity - first);

				if (index > last)
				{
					throw std::out_of_range("Index out of range");
				}

				return data[index];
			}
		}
	}

	AllocatorType getAllocator() const
	{
		return alloc;
	}

	void print()
	{
		if (first < last)
		{
			for (int i = first; i <= last; ++i)
			{
				std::cout << data[i] << " ";
			}

			std::cout << std::endl;
		}
		else
		{
			for (int i = first; i < capacity; ++i)
			{
				std::cout << data[i] << " ";
			}
			for (int i = 0; i <= last; ++i)
			{
				std::cout << data[i] << " ";
			}
		}
	}

	class DQIterator
	{
		friend class Deque;

	private:
		T* pointer;

		DQIterator(T* pointer) : pointer(pointer) {}
	public:

		const T& operator*() const
		{
			return *pointer;
		}

		T& operator*()
		{
			return *pointer;
		}

		const T* operator->() const
		{
			return pointer;
		}

		T* operator->()
		{
			return pointer;
		}

		DQIterator operator++()
		{
			pointer++;
			return *this;
		}

		DQIterator operator++(int)
		{
			DQIterator res(*this);
			++(*this);
			return res;
		}

		bool operator==(const DQIterator& other) const
		{
			return (pointer == other.pointer);
		}

		bool operator!=(const DQIterator& other) const
		{
			return !(*this == other);
		}

		const T& operator[](const size_t& offset)
		{
			return *(pointer + offset);
		}

		T& operator[](const size_t offset)
		{
			return *(pointer + offset);
		}
	};

	DQIterator begin()
	{
		return DQIterator(&data[first]);
	}

	DQIterator end()
	{
		return DQIterator(&data[last + 1]);
	}
};
