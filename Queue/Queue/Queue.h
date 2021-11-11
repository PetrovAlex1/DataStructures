#pragma once

template <class T>
class Queue
{
private:
	T* s_data{ new T[8] };
	size_t s_first{};
	size_t s_last{};
	size_t s_size{};
	size_t s_capacity{ 8 };

	void resize()
	{
		T* newData = new T[s_capacity * 2];

		int j = 0;

		for (int i = s_first; i < s_last; i = (i + 1) % s_capacity)
		{
			newData[j] = s_data[i];
			j++;
		}

		delete[] s_data;
		s_data = newData;
		s_first = 0;
		s_last = j;
		s_capacity *= 2;
	}
public:

	Queue() = default;

	~Queue()
	{
		delete[] s_data;
	}

	Queue(const Queue<T>& other)
	{
		s_data = new T[other.s_capacity];

		for (int i = 0; i < other.s_last; ++i)
		{
			s_data[i] = other.s_data[i];
		}

		s_capacity = other.s_capacity;
		s_first = other.s_first;
		s_last = other.s_last;
	}

	T& front()
	{
		if (isEmpty())
		{
			throw std::out_of_range("Queue is empty!");
		}

		return s_data[s_first];
	}

	const T& front() const
	{
		if (isEmpty())
		{
			throw std::out_of_range("Queue is empty!");
		}

		return s_data[s_first];
	}

	T& back()
	{
		if (isEmpty())
		{
			throw std::out_of_range("Queue is empty!");
		}

		return s_data[s_last - 1];
	}

	const T& back() const
	{
		if (isEmpty())
		{
			throw std::out_of_range("Queue is empty!");
		}

		return s_data[s_last - 1];
	}

	void enqueue(const T& element)
	{
		if (isFull())
		{
			resize();
		}

		s_data[s_last] = element;
		s_last = (s_last + 1) % s_capacity;
	}

	T dequeue()
	{
		if (isEmpty())
		{
			throw std::out_of_range("Queue is empty!");
		}

		T toRemove = s_data[s_first];
		s_first = (s_first + 1) % s_capacity;
		return toRemove;
	}

	size_t size() const
	{
		return (s_last + s_capacity - s_first) % s_capacity;
	}

	bool isEmpty() const
	{
		return size() == 0;
	}

	bool isFull() const
	{
		return s_last % s_capacity == s_first;
	}
};