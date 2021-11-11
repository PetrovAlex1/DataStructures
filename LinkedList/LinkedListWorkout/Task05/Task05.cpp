#include <iostream>
#include <functional>
#include "LinkedList.h"

bool predicate(const int element)
{
	return element % 2 == 0;
}

LinkedList<int> filter(LinkedList<int>& list, std::function<bool(int)> predicate)
{
	LinkedList<int> result;

	for (LinkedList<int>::Iterator i = list.begin(); i != list.end(); ++i)
	{
		if (predicate(*i))
		{
			result.push(*i);
		}
	}

	return result;
}

int main()
{
	LinkedList<int> list;
	list.push(1);
	list.push(2);
	list.push(3);
	list.push(4);
	list.push(5);
	list.push(6);

	std::function<bool(int)> func = predicate;

	LinkedList<int> result = filter(list, func);

	for (LinkedList<int>::Iterator i = result.begin(); i != result.end(); ++i)
	{
		std::cout << *i << " ";
	}

	std::cout << std::endl;

	return 0;
}