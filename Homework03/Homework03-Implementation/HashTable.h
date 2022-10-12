#pragma once
#include <iostream>
#include <vector>
#include <forward_list>

template <typename T, typename Y>
struct Node
{
private:
	T key;
	Y value;

public:

	Node(const T& key, const Y& value) : key(key), value(value) {}

	const T first() const
	{
		return key;
	}

	Y& second()
	{
		return value;
	}

	const Y second() const
	{
		return value;
	}
};

template <typename T, typename Y>
class HashBucket
{
private:
	typedef Node<T, Y> Item;
	std::forward_list<Item> nodes;

	typename std::forward_list<Item>::iterator getItemIterator(const T& key)
	{
		for (typename std::forward_list<Item>::iterator it = nodes.begin(); it != nodes.end(); ++it)
		{
			if ((*it).first() == key)
			{
				return it;
			}
		}
	}

	const typename std::forward_list<Item>::const_iterator getItemIterator(const T& key) const
	{
		for (typename std::forward_list<Item>::const_iterator it = nodes.cbegin(); it != nodes.cend(); ++it)
		{
			if ((*it).first() == key)
			{
				return it;
			}
		}
	}

public:
	HashBucket() {}

	void addNode(const T& key, const Y& value)
	{
		Item newNode(key, value);
		nodes.push_front(newNode);
	}

	bool existNode(const T& key) const
	{
		for (auto it = nodes.cbegin(); it != nodes.cend(); ++it)
		{
			if ((*it).first() == key)
			{
				return true;
			}
		}

		return false;
	}

	void removeNode(const T& key)
	{
		typename std::forward_list<Item>::iterator it = nodes.before_begin();

		for (; it != nodes.end();)
		{
			typename std::forward_list<Item>::iterator previous = it++;

			if (it != nodes.end() && it->first() == key)
			{
				nodes.erase_after(previous);
				return;
			}
		}

		throw std::invalid_argument("Node with such key does not exist!");
	}

	class Iterator
	{
		friend class HashBucket;

	private:
		typename std::forward_list<Item>::iterator it;

		Iterator(typename std::forward_list<Item>::iterator it) : it(it) {}

	public:
		Iterator& operator++()
		{
			it++;
			return *this;
		}

		Node<const T, Y>& operator*()
		{
			return reinterpret_cast<Node<const T, Y> &>(*it);
		}

		bool operator==(const Iterator& other)
		{
			return it == other.it;
		}

		bool operator!=(const Iterator& other)
		{
			return !(*this == other);
		}
	};

	Iterator begin()
	{
		return Iterator(nodes.begin());
	}

	Iterator end()
	{
		return Iterator(nodes.end());
	}

	class constIterator
	{
		friend class HashBucket;

	private:
		typename std::forward_list<Item>::const_iterator it;

		constIterator(typename std::forward_list<Item>::const_iterator const it) : it(it) {}

	public:
		constIterator& operator++()
		{
			it++;
			return *this;
		}

		const Node<T, Y>& operator*() const
		{
			return reinterpret_cast<const Node<T, Y> &>(*it);
		}

		bool operator==(const constIterator& other) const
		{
			return it == other.it;
		}

		bool operator!=(const constIterator& other) const
		{
			return !(*this == other);
		}
	};

	constIterator cbegin() const
	{
		return constIterator(nodes.cbegin());
	}

	constIterator cend() const
	{
		return constIterator(nodes.cend());
	}

	Y& getValueByKey(const T& key)
	{
		if (existNode(key))
		{
			return (*getItemIterator(key)).second();
		}

		throw std::invalid_argument("Such value does not exist!");
	}

	Y getValueByKey(const T& key) const
	{
		if (existNode(key))
		{
			return (*getItemIterator(key)).second();
		}

		throw std::invalid_argument("Such value does not exist!");
	}
};

template <typename T, typename Y>
class HashTable
{
private:
	std::vector<HashBucket<T, Y>> hashList;

	size_t getHashValue(const T& key) const
	{
		return std::hash<T>{}(key) % hashList.size();
	}

	typename std::vector<HashBucket<T, Y>>::const_iterator getNodeIterator(const T& key) const
	{
		return hashList.begin() + getHashValue(key);
	}

public:
	HashTable()
	{
		hashList.resize(16);
	}

	class Iterator
	{
		friend class HashTable;

	private:
		typename std::vector<HashBucket<T, Y>>::iterator tableIterator;
		typename HashBucket<T, Y>::Iterator bucketIterator;
		typename std::vector<HashBucket<T, Y>>::iterator end;

		Iterator(typename std::vector<HashBucket<T, Y>>::iterator tableIterator,
			typename HashBucket<T, Y>::Iterator bucketIterator,
			typename std::vector<HashBucket<T, Y>>::iterator end)
			: tableIterator(tableIterator), bucketIterator(bucketIterator), end(end)
		{
			findNext();
		}

		void findNext()
		{
			while (tableIterator != end && bucketIterator == (*tableIterator).end())
			{
				tableIterator++;

				if (tableIterator != end)
				{
					bucketIterator = tableIterator->begin();
				}
			}
		}

	public:
		Iterator& operator++()
		{
			++bucketIterator;
			findNext();
			return *this;
		}

		Node<const T, Y>& operator*()
		{
			return *bucketIterator;
		}

		bool operator==(const Iterator& other)
		{
			return tableIterator == other.tableIterator && bucketIterator == other.bucketIterator;
		}

		bool operator!=(const Iterator& other)
		{
			return !(*this == other);
		}
	};

	Iterator begin()
	{
		return Iterator(hashList.begin(), hashList.front().begin(), hashList.end());
	}

	Iterator end()
	{
		return Iterator(hashList.end(), hashList.back().end(), hashList.end());
	}

	class constIterator
	{
		friend class HashTable;

	private:
		typename std::vector<HashBucket<T, Y>>::const_iterator tableIterator;
		typename HashBucket<T, Y>::constIterator bucketIterator;
		typename std::vector<HashBucket<T, Y>>::const_iterator cend;

		constIterator(typename std::vector<HashBucket<T, Y>>::const_iterator tableIterator,
			typename HashBucket<T, Y>::constIterator bucketIterator,
			typename std::vector<HashBucket<T, Y>>::const_iterator cend)
			: tableIterator(tableIterator), bucketIterator(bucketIterator), cend(cend)
		{
			findNext();
		}

		void findNext()
		{
			while (tableIterator != cend && bucketIterator == (*tableIterator).cend())
			{
				tableIterator++;

				if (tableIterator != cend)
				{
					bucketIterator = (*tableIterator).cbegin();
				}
			}
		}

	public:

		constIterator& operator++()
		{
			++bucketIterator;
			findNext();
			return *this;
		}

		const Node<T, Y>& operator*() const
		{
			return *bucketIterator;
		}

		bool operator==(const constIterator& other) const
		{
			return tableIterator == other.tableIterator && bucketIterator == other.bucketIterator;
		}

		bool operator!=(const constIterator& other) const
		{
			return !(*this == other);
		}
	};

	constIterator cbegin() const
	{
		return constIterator(hashList.cbegin(), hashList.front().cbegin(), hashList.cend());
	}

	constIterator cend() const
	{
		return constIterator(hashList.cend(), hashList.back().cend(), hashList.cend());
	}

	constIterator find(const T& key) const
	{
		size_t hash = getHashValue(key);
		typename std::vector<HashBucket<T, Y>>::const_iterator tableIterator = getNodeIterator(key);
		typename HashBucket<T, Y>::constIterator bucketIterator = (*tableIterator).cbegin(); //hashList[hash].begin();

		for (; bucketIterator != (*tableIterator).cend(); ++bucketIterator)
		{
			if ((*bucketIterator).first() == key)
			{
				break;
			}
		}

		return (*tableIterator).existNode(key) ? constIterator(tableIterator, bucketIterator, hashList.cend()) : cend();
	}

	void insert(const T& key, const Y& value)
	{
		size_t hash = getHashValue(key);
		hashList[hash].addNode(key, value);
	}

	void erase(const T& key)
	{
		size_t hash = getHashValue(key);
		hashList[hash].removeNode(key);
	}

	Y& operator[](const T& key)
	{
		size_t hash = getHashValue(key);

		if (hashList[hash].existNode(key))
		{
			return hashList[hash].getValueByKey(key);
		}

		hashList[hash].addNode(key, Y());
		return hashList[hash].getValueByKey(key);
	}
};
