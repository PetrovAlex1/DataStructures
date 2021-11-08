#pragma once

class DQIterator
{
	friend class Deque;

private:
	size_t index;
	Deque<T>* deque;

	DQIterator(Deque<T>* deque, size_t index) : deque(deque), index(index) {}
public:

	const T& operator*() const
	{
		int actualIndex = (index - deque->first) % deque->capacity;
		return (*deque)[actualIndex];
	}

	T& operator*()
	{
		int actualIndex = (index - deque->first) % deque->capacity;
		return (*deque)[actualIndex];
	}

	const T* operator->() const
	{
		int actualIndex = (index - deque->first) % deque->capacity;
		return &(*deque[actualIndex]);
	}

	T* operator->()
	{
		int actualIndex = (index - deque->first) % deque->capacity;
		return  &(*deque[actualIndex]);
	}

	DQIterator operator++()
	{
		index++;
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
		return ((index % deque->capacity) == other.index);
	}

	bool operator!=(const DQIterator& other) const
	{
		return !(*this == other);
	}
};