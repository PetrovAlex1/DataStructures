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

		for (int i = 0; i < s_size; i++)
		{
			newData[i] = s_data[i];
		}

		delete[] s_data;
		s_data = newData;
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
		if (s_size == 0)
		{
			throw std::out_of_range("Queue is empty!");
		}

		return s_data[s_first];
	}

	const T& front() const
	{
		if (s_size == 0)
		{
			throw std::out_of_range("Queue is empty!");
		}

		return s_data[s_first];
	}

	T& back()
	{
		if (s_size == 0)
		{
			throw std::out_of_range("Queue is empty!");
		}

		return s_data[s_last - 1];
	}

	const T& back() const
	{
		if (s_size == 0)
		{
			throw std::out_of_range("Queue is empty!");
		}

		return s_data[s_last - 1];
	}

	void enqueue(const T& element)
	{
		if (s_size == s_capacity)
		{
			resize();
		}

		s_size++;
		s_data[s_last++] = element;
	}

	void dequeue()
	{
		if (s_size == 0)
		{
			throw std::out_of_range("Queue is empty!");
		}

		s_size--;
		s_first++;
	}

	size_t size() const
	{
		return s_last - s_first;
	}

	bool isEmpty() const
	{
		return size() == 0;
	}
};