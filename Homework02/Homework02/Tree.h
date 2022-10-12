#pragma once
#include <iostream>
#include <vector>
#include <queue>

template <typename T>
class Tree
{
private:
	struct	Node
	{
		T data;
		int level;
		Node* child;
		Node* brother;

		Node(const T& data, const int level, Node* child = nullptr, Node* brother = nullptr)
			: data(data), level(level), child(child), brother(brother) {}
	} *root;

	int size;

	void clear(Node* root)
	{
		if (root)
		{
			clear(root->child);
			clear(root->brother);
			delete root;
		}
	}

	Node* copy(Node* root)
	{
		if (root)
		{
			return new Node(root->data, root->level, copy(root->child), copy(root->brother));
		}

		return root;
	}

	bool find(const Node* root, const T& key) const
	{
		if (!root)
		{
			return false;
		}
		else if (root->data == key)
		{
			return true;
		}
		else
		{
			return find(root->child, key) || find(root->brother, key);
		}
	}

	bool remove(Node*& root, const T& key)
	{
		if (!root)
		{
			return false;
		}

		if (root->data == key)
		{
			Node* toDelete = root;

			if (!root->child)
			{
				root = root->brother;
			}
			else if (root->brother)
			{
				Node* current = root->child;

				while (current->brother)
				{
					current = current->brother;
				}

				current->brother = root->brother;
				root = root->child;
			}
			else
			{
				root = root->child;
			}

			size--;
			delete toDelete;
			return true;
		}
		else
		{
			return remove(root->brother, key) || remove(root->child, key);
		}
	}

	bool insert(Node*& root, const T& keyToDetach, const T& data)
	{
		if (!root)
		{
			return false;
		}
		else if (root->data == keyToDetach)
		{
			root->child = new Node(data, root->level + 1, nullptr, root->child);
			return true;
		}
		else
		{
			return insert(root->brother, keyToDetach, data) || insert(root->child, keyToDetach, data);
		}
	}

	int height(const Node* root) const
	{
		if (!root)
		{
			return 0;
		}

		return std::max(1 + height(root->child), height(root->brother));
	}

	void getListOfAllElements(std::vector<T>& list, const Node* root) const
	{
		if (root)
		{
			list.push_back(root->data);
			getListOfAllElements(list, root->brother);
			getListOfAllElements(list, root->child);
		}
	}

	void modernize(Node*& root)
	{
		if (root != nullptr)
		{
			if (root->child)
			{
				modernize(root->child);
			}
			if (root->level % 2 != 0 && root->child)
			{
				remove(root->data);
				modernize(root);
			}
			if (root)
			{
				modernize(root->brother);
			}
		}
	}

	void correctLevel(Node* root, const int level)
	{
		if (root)
		{
			root->level = level;
			correctLevel(root->brother, level);
			correctLevel(root->child, level + 1);
		}
	}

	T* getParent(Node* root, const T& key) const
	{
		if (!root)
		{
			return nullptr;
		}
		else if (isChild(root->child, key))
		{
			return &root->data;
		}
		else
		{
			T* fromBrother = getParent(root->brother, key);
			T* fromChild = getParent(root->child, key);

			if (!fromBrother && !fromChild)
			{
				return nullptr;
			}

			return fromChild ? fromChild : fromBrother;
		}
	}

	bool isChild(Node* root, const T& key) const
	{
		while (root)
		{
			if (root->data == key)
			{
				return true;
			}

			root = root->brother;
		}

		return false;
	}

	void getChildren(const Node* root, const T& key, std::vector<T>& list) const
	{
		if (root)
		{
			if (root->data == key)
			{
				Node* current = root->child;

				while (current)
				{
					list.push_back(current->data);
					current = current->brother;
				}

				return;
			}

			getChildren(root->brother, key, list);
			getChildren(root->child, key, list);
		}
	}

	void getAllBrotherhoods(Node* root, std::vector<std::vector<T>>& brotherhoods)
	{
		if (root)
		{
			getAllBrotherhoods(root->child, brotherhoods);

			std::vector<T> children;
			getChildren(root, root->data, children);

			if (children.size() >= 2)
			{
				brotherhoods.push_back(children);
			}

			getAllBrotherhoods(root->brother, brotherhoods);
		}
	}

	Node* getParentNode(Node* root, const T& key)
	{
		if (!root)
		{
			return nullptr;
		}
		else if (isChild(root->child, key))
		{
			return root;
		}
		else
		{
			Node* fromBrother = getParentNode(root->brother, key);
			Node* fromChild = getParentNode(root->child, key);

			if (!fromBrother && !fromChild)
			{
				return nullptr;
			}

			return fromChild ? fromChild : fromBrother;
		}
	}

	void incorporate(Node*& root, const T& key)
	{
		if (root)
		{
			if (root->data == key)
			{
				Node* newBoss = root;
				Node* bossParent = getParentNode(this->root, root->data);
				Node* current = bossParent->child;

				if (current->data == key)
				{
					bossParent->child = newBoss;
				}
				else
				{
					while (current->brother->data != root->data)
					{
						current = current->brother;
					}

					current->brother = newBoss->child;
				}
				if (newBoss->child)
				{
					Node* currentBossChild = newBoss->child;

					while (currentBossChild->brother)
					{
						currentBossChild = currentBossChild->brother;
					}

					currentBossChild->brother = newBoss->brother;
				}
				else
				{
					current->brother = newBoss->brother;
				}

				newBoss->child = current->data == key ? root->child : bossParent->child;
				newBoss->brother = nullptr;
				bossParent->child = newBoss;
				return;
			}

			incorporate(root->child, key);
			incorporate(root->brother, key);
		}
	}

	int getLevel(const Node* root, const T& key) const
	{
		if (!root)
		{
			return -1;
		}
		else if (root->data == key)
		{
			return root->level;
		}
		else
		{
			int fromChild = getLevel(root->child, key);
			int fromBrother = getLevel(root->brother, key);

			if (fromChild == -1 && fromBrother == -1)
			{
				return -1;
			}

			return fromBrother >= 0 ? fromBrother : fromChild;
		}
	}

	bool existInSubtree(Node* root, const T& first, const T& second) const
	{
		if (!root)
		{
			return false;
		}
		else if (root->data == first)
		{
			return find(root->child, second);
		}
		else
		{
			return existInSubtree(root->child, first, second) || existInSubtree(root->brother, first, second);
		}
	}

	Node* get(Node* root, const T& key)
	{
		if (!root)
		{
			return nullptr;
		}
		else if (root->data == key)
		{
			return root;
		}
		else
		{
			Node* fromChild = get(root->child, key);
			Node* fromBrother = get(root->brother, key);

			if (!fromChild && !fromBrother)
			{
				return nullptr;
			}

			return fromChild ? fromChild : fromBrother;
		}
	}

	void move(Node*& root, const T& nodeToMove, const T& newNode)
	{
		if (root)
		{
			if (root->data == nodeToMove)
			{
				Node* temp = root;
				Node* nodeToDetach = get(this->root, newNode);
				Node* parent = getParentNode(this->root, root->data);

				//remove the node from brotherhood
				if (parent->child == root)
				{
					parent->child = root->brother;
				}
				else
				{
					Node* current = parent->child;

					while (current->brother != root)
					{
						current = current->brother;
					}

					current->brother = root->brother;
				}

				//detach the node to it's new place
				if (nodeToDetach->child)
				{
					Node* current = nodeToDetach->child;

					while (current->brother)
					{
						current = current->brother;
					}

					current->brother = temp;
				}
				else
				{
					nodeToDetach->child = temp;
				}

				temp->brother = nullptr;
				return;
			}

			move(root->brother, nodeToMove, newNode);
			move(root->child, nodeToMove, newNode);
		}
	}

public:

	Tree() : root(nullptr), size(0) {}

	Tree(Tree& other) : root(copy(other.root)), size(other.size) {}

	Tree(Tree&& other)
		: Tree()
	{
		std::swap(root, other.root);
		std::swap(size, other.size);
	}

	Tree& operator=(const Tree& other)
	{
		if (this != &other)
		{
			clear(root);
			root = copy(other.root);
			this->size = other.size;
		}

		return *this;
	}

	~Tree()
	{
		clear(root);
	}

	bool find(const T& key) const
	{
		return find(root, key);
	}

	void insert(const T& keyToDetach, const T& data)
	{
		if (root == nullptr)
		{
			root = new Node(data, 0, nullptr, root);
			size++;
		}
		else
		{
			if (insert(root, keyToDetach, data))
			{
				size++;
			}
			else
			{
				throw std::invalid_argument("No such key to detach in current tree!");
			}
		}
	}

	void remove(const T& key)
	{
		remove(root, key);
	}

	int getSize() const
	{
		return size;
	}

	const T* getParent(const T& key) const
	{
		if (find(key))
		{
			if (key != root->data)
			{
				return getParent(root, key);
			}

			throw std::invalid_argument("The root has no parent!");
		}

		throw std::invalid_argument("Node with such key does not exist!");
	}

	std::vector<T> getChildren(const T& key) const
	{
		if (find(key))
		{
			std::vector<T> children;
			getChildren(root, key, children);
			return children;
		}

		throw std::invalid_argument("Node with such key does not exist!");
	}

	std::vector<std::vector<T>> getAllBrotherhoods()
	{
		std::vector<std::vector<T>> brotherhoods;
		getAllBrotherhoods(root, brotherhoods);
		return brotherhoods;
	}

	void modernizeTree()
	{
		modernize(root);
		correctLevel(root, 0);
	}

	void incorporateTree(const T& key)
	{
		if (find(key))
		{
			incorporate(root, key);
			correctLevel(root, 0);
		}
		else
		{
			throw std::invalid_argument("Node with such key does not exist!");
		}
	}

	void moveSubtree(const T& nodeToMove, const T& newNode)
	{
		if (find(nodeToMove) && find(newNode))
		{
			move(root, nodeToMove, newNode);
		}
		else
		{
			throw std::invalid_argument("Node(s) with such key does not exist!");
		}
	}

	int getHeight() const
	{
		return height(root);
	}

	int getLevel(const T& key) const
	{
		if (find(key))
		{
			return getLevel(root, key);
		}

		throw std::invalid_argument("Node with such key does not exist!");
	}

	//return whether in the tree with root node {first} exist node {second}
	bool existInSubtree(const T& first, const T& second) const
	{
		if (find(first) && find(second))
		{
			return existInSubtree(root, first, second);
		}

		throw std::invalid_argument("Node with such key does not exist!");
	}

	std::vector<T> getListOfAllElements() const
	{
		std::vector<T> list;
		getListOfAllElements(list, root);
		return list;
	}
};