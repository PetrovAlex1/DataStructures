#pragma once

template <class T>
struct Node
{
	T data;
	Node<T>* next;

	Node(const T& data, Node<T>* next = nullptr) : data(data), next(next) {}
};

template <class T>
class LinkedList
{
private:
	Node<T>* first;
public:

	LinkedList() : first(nullptr) {}

	LinkedList(const LinkedList<T>& other)
	{
		Node<T>* current = other.first;

		while (current)
		{
			push(current->data);
			current = current->next;
		}
	}

	~LinkedList()
	{
		clear();
	}

	LinkedList& operator=(const LinkedList<T> other)
	{
		if (this != &other)
		{
			clear();

			Node<T>* current = other.first;

			while (current)
			{
				push(current->data);
				current = current->next;
			}
		}

		return *this;
	}

	void push(const T& element)
	{
		first = new Node<T>(element, first);
	}

	bool pop()
	{
		if (first == nullptr)
		{
			return false;
		}

		Node<T>* toRemove = first;
		first = first->next;
		delete toRemove;

		return true;
	}

	void clear()
	{
		Node<T>* current = first;

		while (current)
		{
			Node<T>* toRemove = current;
			current = current->next;
			delete toRemove;
		}
	}

	void print()
	{
		Node<T>* current = first;

		while (current)
		{
			std::cout << current->data << " ";
			current = current->next;
		}

		std::cout << std::endl;
	}

	class Iterator
	{
		friend class LinkedList;

	private:
		Node<T>* pointer;

		Iterator(Node<T>* pointer) : pointer(pointer) {}
	public:
		const T& operator*() const
		{
			return pointer->data;;
		}

		T& operator*()
		{
			return pointer->data;
		}

		Iterator& operator++()
		{
			pointer = pointer->next;
			return *this;
		}

		Iterator operator++(int)
		{
			Iterator res(*this);
			++(*this);
			return res;
		}

		bool operator==(const Iterator& other)
		{
			return (pointer == other.pointer);
		}

		bool operator!=(const Iterator& other)
		{
			return !(*this == other);
		}
	};

	Iterator begin()
	{
		return Iterator(first);
	}

	Iterator end()
	{
		return Iterator(nullptr);
	}
};