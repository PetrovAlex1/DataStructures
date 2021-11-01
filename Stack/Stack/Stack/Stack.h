#pragma once
#include <stdexcept>

template <class T>
class Stack
{
private:
	T* s_data{ new T[8] };
	size_t s_size{};
	size_t s_capacity{ 8 };

	void resize()
	{
		T* newData = new T[s_capacity * 2];

		for (int i = 0; i < s_size; i++)
		{
			newData[i] = s_data[i];
		}

		delete[] s_data;
		s_data = newData;
		s_capacity *= 2;
	}
public:

	Stack() = default;

	~Stack()
	{
		delete[] s_data;
	}

	Stack(const Stack<T>& other)
	{
		s_data = new T[other.s_capacity];

		for (int i = 0; i < other.s_size; i++)
		{
			s_data[i] = other.s_data[i];
		}

		s_size = other.s_size;
		s_capacity = other.s_capacity;
	}

	Stack<T>& operator=(const Stack<T>& other)
	{
		Stack<T> copy(other);

		std::swap(s_data, copy.s_data);
		std::swap(s_size, copy.s_size);
		std::swap(s_capacity, copy.s_capacity);

		return *this;
	}

	T& top()
	{
		if (s_size == 0)
		{
			throw std::out_of_range("Stack is empty!");
		}

		return s_data[s_size - 1];
	}

	const T& top() const
	{
		if (s_size == 0)
		{
			throw std::out_of_range("Stack is empty!");
		}

		return s_data[s_size - 1];
	}

	void push(const T& element)
	{
		if (s_size == s_capacity)
		{
			resize();
		}

		s_data[s_size++] = element;
	}

	T pop()
	{
		if (s_size == 0)
		{
			throw std::out_of_range("Stack is empty!");
		}

		return s_data[--s_size];
	}

	bool isEmpty() const
	{
		return s_size == 0;
	}
};