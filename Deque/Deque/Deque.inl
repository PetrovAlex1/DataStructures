#pragma once

template<class T, class AllocatorType>
inline void Deque<T, AllocatorType>::resize()
{
	T* newData = alloc.allocate(capacity * 2 - 1);

	size_t j = 0;

	for (size_t i = first; i != last; i = (i + 1) % (capacity - 1))
	{
		newData[j] = data[i];
		j++;
	}

	first = 0;
	last = j;
	alloc.free(data);
	data = newData;
	capacity = capacity * 2 - 1;
}

template<class T, class AllocatorType>
inline Deque<T, AllocatorType>::Deque()
{
	data = alloc.allocate(9);
	first = 0;
	last = 0;
	capacity = 9;
}

template<class T, class AllocatorType>
inline Deque<T, AllocatorType>::Deque(const Deque<T, AllocatorType>& other)
{
	data = alloc.allocate(other.capacity);
	first = other.capacity - 2;
	last = 0;
	capacity = other.capacity;

	for (size_t i = other.first; i != other.last - 1; i = (i + 1) % (capacity - 1))
	{
		push_back(other.data[i]);
	}
}

template<class T, class AllocatorType>
inline Deque<T>& Deque<T, AllocatorType>::operator=(const Deque<T, AllocatorType>& other)
{
	Deque<T, AllocatorType> copy(other);

	std::swap(data, copy.data);
	std::swap(first, copy.first);
	std::swap(last, copy.last);
	std::swap(capacity, copy.capacity);
	std::swap(alloc, copy.alloc);

	return *this;
}

template<class T, class AllocatorType>
inline Deque<T, AllocatorType>::~Deque()
{
	alloc.free(data);
	data = nullptr;
	first = 0;
	last = 0;
	capacity = 0;
}

template<class T, class AllocatorType>
inline void Deque<T, AllocatorType>::push_front(const T& element)
{
	if (first == last)//Deque is empty
	{
		first = 0;
		last = 0;
		data[first] = element;
	}
	else if ((first == 0 && last == capacity - 1) || (first == last + 1))//Deque is full
	{
		resize();
		first = capacity - 1;
		data[first] = element;
	}
	else if (first == 0)
	{
		first = capacity - 1;
		data[first] = element;
	}
	else
	{
		data[--first] = element;
	}
}

template<class T, class AllocatorType>
inline void Deque<T, AllocatorType>::push_back(const T& element)
{
	if (first == last)//Deque is empty
	{
		first = 0;
		last = 0;
	}
	else if ((first == 0 && last == capacity - 1) || (first == last + 1))//Deque is full
	{
		resize();
	}

	data[last] = element;
	last = last + 1 == capacity ? 0 : ++last;
}

template<class T, class AllocatorType>
inline void Deque<T, AllocatorType>::pop_front()
{
	if (first == capacity - 1)
	{
		first = 0;
	}
	else if (!isEmpty())
	{
		first++;
	}
	else
	{
		throw std::logic_error("Deque is empty!");
	}
}

template<class T, class AllocatorType>
inline void Deque<T, AllocatorType>::pop_back()
{
	if (last == 0 && first != 0)
	{
		last = capacity - 1;
	}
	else if (!isEmpty())
	{
		last--;
	}
	else
	{
		throw std::logic_error("Deque is empty!");
	}
}

template<class T, class AllocatorType>
inline T& Deque<T, AllocatorType>::front()
{
	return data[first];
}

template<class T, class AllocatorType>
inline const T& Deque<T, AllocatorType>::front() const
{
	return data[first];
}

template<class T, class AllocatorType>
inline T& Deque<T, AllocatorType>::back()
{
	return data[last - 1];
}

template<class T, class AllocatorType>
inline const T& Deque<T, AllocatorType>::back() const
{
	return data[last - 1];
}

template<class T, class AllocatorType>
inline bool Deque<T, AllocatorType>::isEmpty() const
{
	return (first == last);
}

template<class T, class AllocatorType>
inline int Deque<T, AllocatorType>::size() const
{
	return (last + capacity - first) % capacity;
}

template<class T, class AllocatorType>
inline const T& Deque<T, AllocatorType>::operator[](const int& index) const
{
	if (index < 0 || index > capacity - 2)
	{
		throw std::out_of_range("Invalid index!");
	}
	else if (first == last)
	{
		throw std::logic_error("Deque is empty!");
	}
	if (first == 0)
	{
		if (index > last - 1)
		{
			throw std::out_of_range("Index out of range");
		}

		return data[index];
	}
	else
	{
		if (first < last - 1)
		{
			if (first + index > last - 1)
			{
				throw std::out_of_range("Index out of range");
			}

			return data[first + index];
		}
		else
		{
			int newIndex = (first + index) % (capacity - 1);

			if (newIndex > last - 1 && newIndex < first)
			{
				throw std::out_of_range("Index out of range");
			}

			return data[newIndex];
		}
	}
}

template<class T, class AllocatorType>
inline T& Deque<T, AllocatorType>::operator[](const int& index)
{
	if (index < 0 || index > capacity - 2)
	{
		throw std::out_of_range("Invalid index!");
	}
	else if (first == last)
	{
		throw std::logic_error("Deque is empty!");
	}
	if (first == 0)
	{
		if (index > last - 1)
		{
			throw std::out_of_range("Index out of range");
		}

		return data[index];
	}
	else
	{
		if (first < last - 1)
		{
			if (first + index > last - 1)
			{
				throw std::out_of_range("Index out of range");
			}

			return data[first + index];
		}
		else
		{
			int newIndex = (first + index) % (capacity - 1);

			if (newIndex > last - 1 && newIndex < first)
			{
				throw std::out_of_range("Index out of range");
			}

			return data[newIndex];
		}
	}
}

template<class T, class AllocatorType>
inline AllocatorType Deque<T, AllocatorType>::getAllocator() const
{
	return alloc;
}

template<class T, class AllocatorType>
inline void Deque<T, AllocatorType>::print()
{
	for (size_t i = first; i != last; i = (i + 1) % (capacity))
	{
		std::cout << data[i] << " ";
	}

	std::cout << std::endl;
}