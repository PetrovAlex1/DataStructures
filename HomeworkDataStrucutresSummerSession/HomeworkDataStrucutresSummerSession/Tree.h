#pragma once

#include <iostream>
#include <fstream>
#include <queue>
#include <optional>

template <typename T>
class Tree
{
private:
	struct Node
	{
		T data;
		Node* parent;
		Node* child;
		Node* brother;

		Node(const T& data, Node* parent, Node* child = nullptr, Node* brother = nullptr)
			: data(data), parent(parent), child(child), brother(brother)
		{}
	};

	Node* root;
	size_t size;

public:

	Tree()
	{
		this->root = nullptr;
		this->size = 0;
	}

	~Tree()
	{
		clear(root);
	}

	void insert(const T& keyToDetach, const T& data, const int level = 0, int position = 0)
	{
		if (root == nullptr)
		{
			root = new Node(data, nullptr);
		}
		else if (!recursiveInsert(root, keyToDetach, data, level - 1, position))
		{
			throw std::invalid_argument("No such key to detach in current tree!");
		}

		size++;
	}

	void remove(const Tree<T>& other)
	{
		recursiveRemove(root, other.root, 0);
	}

	bool contains(const Tree<T>& other)
	{
		return recursiveContains(root, other.root);
	}

	void saveToFile(std::ofstream& file) const
	{
		file << "| " << root->data << " |\n";

		std::queue<Node*> front;
		front.push(root->child);
		int frontCount = getCountOfChildren(root);
		int nextFrontCount = 0;

		while (!front.empty())
		{
			if (frontCount == 0)
			{
				file << "|\n";
				frontCount = nextFrontCount;
				nextFrontCount = 0;
			}

			bool hasToPrint = false;
			Node* currentNode = front.front();
			file << "| ";

			while (currentNode)
			{
				hasToPrint = true;
				file << currentNode->data << ' ';
				front.push(currentNode->child);
				int currentChildren = getCountOfChildren(currentNode);
				nextFrontCount += currentChildren == 0 ? 1 : currentChildren;
				currentNode = currentNode->brother;
				frontCount--;
			}

			front.pop();

			if (!hasToPrint)
			{
				frontCount--;
			}
		}

		file << "|";
	}

private:

	bool recursiveInsert(Node*& root, const T& keyToDetach, const T& data, const int level, int& position)
	{
		if (level < 0 || position < 0 || !root)
		{
			return false;
		}
		if (level == 0)
		{
			if (position == 0 && root->data == keyToDetach)
			{
				if (!root->child)
				{
					root->child = new Node(data, root);
				}
				else
				{
					Node* temp = root->child;

					while (temp && temp->brother)
					{
						if (temp->data == data)
						{
							throw std::invalid_argument("There cannot be two children nodes with same value!");
						}

						temp = temp->brother;
					}

					temp->brother = new Node(data, root);
				}

				return true;
			}

			position--;
		}

		return recursiveInsert(root->child, keyToDetach, data, level - 1, position) || recursiveInsert(root->brother, keyToDetach, data, level, position);
	}

	void recursiveRemove(Node*& root, const Node* other, const int level)
	{
		if (!root)
		{
			return;
		}

		recursiveRemove(root->child, other, level + 1);

		if (root->data == other->data && existSubtree(root->child, other->child))
		{
			std::optional<int> result = removeSubtree(root->child, other->child);
			Node* toDelete = root;
			Node* curParent = root->parent;
			root = root->brother;
			delete toDelete;

			if (result.has_value() && !checkForDublicateValues(curParent, level, *std::move(result)))
			{
				int value = *std::move(result);
				Node* newNode = new Node(value, curParent, nullptr, root);
				root = newNode;
			}
		}

		if (root)
		{
			recursiveRemove(root->brother, other, level);
		}
	}

	bool checkForDublicateValues(Node* root, const int level, const int value)
	{
		Node* temp = root->child;

		while (temp)
		{
			if (temp->data == value)
			{
				return true;
			}

			temp = temp->brother;
		}

		return false;
	}

	std::optional<int> removeSubtree(Node* root, Node* other)
	{
		bool hasToAddFromChildren = false;
		int sum = 0;
		Node* prev = nullptr;
		Node* tempThisNode = root;
		Node* tempOtherNode = other;

		while (tempOtherNode)
		{
			while (tempThisNode)
			{
				if (tempThisNode->data == tempOtherNode->data)
				{
					std::optional<int> currentSum = removeSubtree(tempThisNode->child, tempOtherNode->child);

					if (currentSum.has_value())
					{
						hasToAddFromChildren = true;
						sum += *std::move(currentSum);
					}
					if (tempThisNode->data == root->data)
					{
						root = root->brother;
					}
					else
					{
						prev->brother = tempThisNode->brother;
					}

					Node* toDelete = tempThisNode;
					tempThisNode = tempThisNode->brother;
					delete toDelete;
				}
				else
				{
					prev = tempThisNode;
					tempThisNode = tempThisNode->brother;
				}
			}

			tempOtherNode = tempOtherNode->brother;
			tempThisNode = root;
		}

		tempThisNode = root;
		bool hasToAddFromCurrent = false;

		while (tempThisNode)
		{
			hasToAddFromCurrent = true;
			sum += tempThisNode->data;
			Node* toDelete = tempThisNode;
			tempThisNode = tempThisNode->brother;
			delete toDelete;
		}

		if (hasToAddFromCurrent || hasToAddFromChildren)
		{
			return sum;
		}

		return {};
	}

	bool recursiveContains(Node* root, const Node* other)
	{
		if (!root)
		{
			return false;
		}
		else if (root->data == other->data)
		{
			return existSubtree(root->child, other->child);
		}

		return recursiveContains(root->brother, other) || recursiveContains(root->child, other);
	}

	bool existSubtree(Node* root, Node* otherRoot)
	{
		if (!root && otherRoot)
		{
			return false;
		}
		else if (!root && !otherRoot || root && !otherRoot)
		{
			return true;
		}

		Node* tempThisNode = root;
		Node* tempOtherNode = otherRoot;
		int otherBrotherhoodCount = 0;
		int countSameNodes = 0;
		bool result = false;

		while (tempOtherNode)
		{
			while (tempThisNode)
			{
				if (tempThisNode->data == tempOtherNode->data)
				{
					countSameNodes++;
					result = existSubtree(tempThisNode->child, tempOtherNode->child);
				}

				tempThisNode = tempThisNode->brother;
			}

			tempOtherNode = tempOtherNode->brother;
			otherBrotherhoodCount++;
			tempThisNode = root;
		}

		return (otherBrotherhoodCount == countSameNodes ? true : false) && result;
	}

	void clear(Node* root)
	{
		if (root)
		{
			clear(root->child);
			clear(root->brother);
			delete root;
		}
	}

	int getCountOfChildren(Node* root) const
	{
		int count = 0;
		Node* current = root->child;

		while (current)
		{
			count++;
			current = current->brother;
		}

		return count;
	}
};