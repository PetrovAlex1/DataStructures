#include <iostream>
#include "Linkedlist.h"

template <typename T>
T sumElements(LinkedList<T>& list)
{
	T sum = 0;

	for (LinkedList<double>::Iterator i = list.begin(); i != list.end(); ++i)
	{
		sum += *i;
	}

	return sum;
}

int main()
{
	LinkedList<double> list;
	list.push(3.14);
	list.push(3);
	list.push(2.02);
	list.push(10.11);
	list.push(150.89);

	std::cout << sumElements(list);

	return 0;
}