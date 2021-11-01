#pragma once

template <class Type>
class DynamicArray
{
private:
	Type* data;
	size_t size;
	size_t capacity;

	void resize()
	{
		Type* newData = new Type[capacity * 2];

		for (int i = 0; i < size; ++i)
		{
			newData[i] = data[i];
		}

		delete[] data;
		data = newData;
		capacity = capacity * 2;
	}
public:

	DynamicArray() : data(new Type[8]), size(0), capacity(8)
	{
	}

	DynamicArray(const DynamicArray<Type>& other)
	{
		data = new Type[other.capacity];

		for (int i = 0; i < other.size; ++i)
		{
			data[i] = other.data[i];
		}

		capacity = other.capacity;
		size = other.size;
	}

	~DynamicArray()
	{
		clear();
	}

	DynamicArray<Type>& operator=(const DynamicArray<Type>& other)
	{
		if (this != &other)
		{
			DynamicArray<Type> copy{ other };
			std::swap(data, copy.data);
			std::swap(size, copy.size);
			std::swap(capacity, copy.capacity);
		}

		return *this;
	}

	void append(const Type& element)
	{
		if (size + 1 == capacity)
		{
			resize();
		}

		data[size++] = element;
	}

	void remove(const size_t& index)
	{
		if (index >= size)
		{
			throw std::invalid_argument("Index out of range!");
		}

		for (int i = index; i < size - 1; ++i)
		{
			data[i] = data[i + 1];
		}

		size--;
	}

	bool contains(const Type& element) const
	{
		for (int i = 0; i < size; ++i)
		{
			if (element == data[i])
			{
				return true;
			}
		}

		return false;
	}

	Type getElement(const size_t& index) const
	{
		if (index >= size)
		{
			throw std::invalid_argument("Index out of range!");
		}

		return data[index];
	}

	size_t getSize() const
	{
		return size;
	}

	bool isEmpty() const
	{
		return size == 0;
	}

	void clear()
	{
		delete[] data;
		data = nullptr;
		size = capacity = 0;
	}

	const Type& operator[](const size_t& index) const
	{
		if (index >= size)
		{
			throw std::invalid_argument("Index out of range!");
		}

		return data[index];
	}

	Type& operator[](const size_t& index)
	{
		if (index >= size)
		{
			throw std::invalid_argument("Index out of range!");
		}

		return data[index];
	}

	void print()
	{
		for (int i = 0; i < size; i++)
		{
			std::cout << data[i] << " ";
		}

		std::cout << std::endl;
	}

	class DAIterator
	{
	private:
		Type* pointer;

		DAIterator(Type* pointer) : pointer(pointer) {}
	public:

		const Type& operator*() const
		{
			return *pointer;
		}

		Type& operator*()
		{
			return *pointer;
		}

		DAIterator& operator++()
		{
			++pointer;
			return *this;
		}

		DAIterator& operator++(int)
		{
			DAIterator result(*this);
			++(*this);
			return result;
		}

		const Type* operator->() const
		{
			return pointer;
		}

		Type* operator->()
		{
			return pointer;
		}

		bool operator!=(const DAIterator& other) const
		{
			return !(this == &other)
		}

		const Type& operator[](const int& offset) const
		{
			return *(pointer + offset);
		}

		Type& operator[](const int& offset)
		{
			return *(pointer + offset);
		}
	};

	DAIterator begin()
	{
		return DAIterator(data);
	}

	DAIterator end()
	{
		return DAIterator(data + size);
	}
};