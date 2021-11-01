#pragma once

template<typename Type>
struct Node
{
	Type data;
	Node* next;

	Node(const int data, Node* next = nullptr) : data(data), next(next) {}
};

template<typename Type>
class LinkedStack
{
private:
	Node<Type>* tos;

	void clear()
	{
		while (!isEmpty())
		{
			pop();
		}
	}

	void copy(const Node<Type>* other)
	{
		if (other)
		{
			tos = new Node<Type>(other->data);
			other = other->next;

			Node<Type>* current = tos;

			while (other)
			{
				current->next = new Node<Type>(other->data);
				current = current->next;
				other = other->next;
			}
		}
	}

public:

	LinkedStack() : tos(nullptr) {}

	LinkedStack(const LinkedStack& other)
	{
		copy(other);
	}

	LinkedStack& operator=(const LinkedStack& other)
	{
		if (this != &other)
		{
			clear();
			copy(other.tos);
		}

		return *this;
	}

	~LinkedStack()
	{
		clear();
	}

	void push(int newNode)
	{
		tos = new Node<Type>(newNode, tos);
	}

	Type pop()
	{
		if (!isEmpty())
		{
			Node<Type>* toRemove = tos;
			tos = tos->next;
			Type element = toRemove->data;
			delete toRemove;

			return element;
		}

		throw std::underflow_error("Stack is empty!");
	}

	const Type& top() const
	{
		if (!isEmpty())
		{
			return tos->data();
		}

		throw std::underflow_error("Stack is empty!");
	}

	Type& top()
	{
		if (!isEmpty())
		{
			return tos->data();
		}

		throw std::underflow_error("Stack is empty!");
	}

	bool isEmpty()
	{
		return tos == nullptr;
	}
};
