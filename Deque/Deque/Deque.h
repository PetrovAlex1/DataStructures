#pragma once
#include <stdexcept>
#include "DebugAllocator.h"

template <class T, class AllocatorType = DebugAllocator<T>>
class Deque
{
protected:
	T* data;
	int first;
	int last;
	size_t capacity;
	AllocatorType alloc;

	void resize();

public:

	Deque();

	Deque(const Deque<T, AllocatorType>& other);

	Deque<T>& operator=(const Deque<T, AllocatorType>& other);

	~Deque();

	void push_front(const T& element);

	void push_back(const T& element);

	void pop_front();

	void pop_back();

	T& front();

	const T& front() const;

	T& back();

	const T& back() const;

	bool isEmpty() const;

	int size() const;

	const T& operator[](const int& index) const;

	T& operator[](const int& index);

	AllocatorType getAllocator() const;

	void print();

	//Implementation of DQIterator class
#include "DQIterator.inl"

	DQIterator begin()
	{
		return DQIterator(this, first);
	}

	DQIterator end()
	{
		return DQIterator(this, last);
	}
};

#include "Deque.inl"