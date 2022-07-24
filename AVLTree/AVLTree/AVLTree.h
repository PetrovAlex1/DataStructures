#pragma once
#include <iostream>
#include<cassert>
#include <vector>

template <typename T>

class AVLTree
{
private:

	struct Node
	{
		T data;
		int height;
		Node* left;
		Node* right;

		Node(const T& data, Node* left = nullptr, Node* right = nullptr, const int height = 1) : data(data), left(left), right(right), height(height) {}
	};

	size_t nodesCount;
	Node* root;

	void recursiveInsert(Node*& current, const T& value)
	{
		if (!current)
		{
			current = new Node(value);
			nodesCount++;
		}
		else if (current->data < value)
		{
			recursiveInsert(current->right, value);
		}
		else if (current->data > value)
		{
			recursiveInsert(current->left, value);
		}

		current->height = max(getHeight(current->left), getHeight(current->right)) + 1;
		Balance(current);
	}

	void Balance(Node*& current)
	{
		int balance = getBalanceFactor(current);

		if (balance > 1)
		{
			int leftBalance = getBalanceFactor(current->left);

			if (leftBalance < 0)
			{
				rotateLeft(current->left);
			}

			rotateRight(current);
		}
		else if (balance < -1)
		{
			int rightBalance = getBalanceFactor(current->right);

			if (rightBalance > 0)
			{
				rotateRight(current->right);
			}

			rotateLeft(current);
		}
	}

	const T* recursiveFind(const Node* current, const T& value)
	{
		if (!current)
		{
			return nullptr;
		}
		else if (current->data > value)
		{
			return recursiveFind(current->left, value);
		}
		else if (current->data < value)
		{
			return recursiveFind(current->right, value);
		}

		return current->data;
	}

	bool recursiveRemove(Node*& current, const T& value)
	{
		bool result = true;

		if (!current)
		{
			return false;
		}
		else if (current->data > value)
		{
			result = recursiveRemove(current->left, value);
		}
		else if (current->data < value)
		{
			result = recursiveRemove(current->right, value);
		}
		else
		{
			if (!current->left && !current->right)
			{
				delete current;
				current = nullptr;
				return true;
			}
			else if (!current->left)
			{
				Node* toDelete = current;
				current = current->right;
				delete toDelete;
			}
			else if (!current->right)
			{
				Node* toDelete = current;
				current = current->left;
				delete toDelete;
			}
			else
			{
				Node* minElement = extractMin(current->right);
				minElement->left = current->left;
				minElement->right = current->right;
				delete current;
				current = nullptr;
				current = minElement;
			}
		}

		if (result)
		{
			current->height = max(getHeight(current->left), getHeight(current->right)) + 1;
			Balance(current);
			return true;
		}

		return false;
	}

	Node* findMin(Node* current)
	{
		Node* temp = current;

		while (current && current->left)
		{
			current = current->left;
		}

		return current;
	}

	Node* extractMin(Node*& current)
	{
		Node* minElement = nullptr;

		if (current->left)
		{
			minElement = extractMin(current->left);
		}
		else
		{
			minElement = current;
			current = current->right ? current->right : nullptr;
		}

		if (current)
		{
			current->height = max(getHeight(current->left), getHeight(current->right)) + 1;
		}

		Balance(current);
		return minElement;
	}

	void rotateRight(Node*& current)
	{
		Node* leftSide = current->left;
		Node* temp = current;
		temp->left = leftSide->right;
		leftSide->right = temp;
		current = leftSide;

		temp->height = max(getHeight(temp->left), getHeight(temp->right)) + 1;
		leftSide->height = max(getHeight(leftSide->left), getHeight(leftSide->right)) + 1;
	}

	void rotateLeft(Node*& current)
	{
		Node* rightSide = current->right;
		Node* temp = current;
		temp->right = rightSide->left;
		rightSide->left = temp;
		current = rightSide;

		temp->height = max(getHeight(temp->left), getHeight(temp->right)) + 1;
		rightSide->height = max(getHeight(rightSide->left), getHeight(rightSide->right)) + 1;
	}

	int getBalanceFactor(Node* current)
	{
		return current ? getHeight(current->left) - getHeight(current->right) : 0;
	}

	int getHeight(Node* current) const
	{
		return current ? current->height : 0;
	}

	void deleteTree(Node* root)
	{
		if (!root)
		{
			return;
		}

		deleteTree(root->left);
		deleteTree(root->right);

		delete root;
	}

	void recursiveInorder(Node* root, std::vector<T>& result) const // to be removed
	{
		if (root)
		{
			recursiveInorder(root->left, result);
			result.push_back(root->data);
			recursiveInorder(root->right, result);
		}
	}

	int max(int first, int second)
	{
		return first > second ? first : second;
	}
public:

	AVLTree()
	{
		this->root = nullptr;
	}

	~AVLTree()
	{
		deleteTree(this->root);
	}

	void insert(const T& value)
	{
		recursiveInsert(root, value);
	}

	void remove(const T& value)
	{
		if (!recursiveRemove(root, value))
		{
			throw std::invalid_argument("Node is not part of the tree!");
		}

		nodesCount--;
	}

	const T* find(const T& value) const
	{
		T* result = recursiveFind(root, value);

		if (!result)
		{
			return result;
		}

		throw std::invalid_argument("No such key exist");
	}

	std::vector<T> inorder() const
	{
		std::vector<T> result;
		recursiveInorder(root, result);
		return result;
	}

	int getNodesCount() const {
		return nodesCount;
	}

	int getHeightT() const {
		return root ? root->height : 0;
	}
};