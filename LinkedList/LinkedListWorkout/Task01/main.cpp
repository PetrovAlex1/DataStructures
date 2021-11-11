#include <iostream>
#include "SortedLinkedList.h"

template <class T>
SortedLinkedList<T> merge(SortedLinkedList<T>& firstList, SortedLinkedList<T>& secondList)
{
	SortedLinkedList<T> result{ firstList };

	for (SortedLinkedList<int>::Iterator i = secondList.begin(); i != secondList.end(); ++i)
	{
		result.push(*i);
	}

	return result;
}

int main()
{
	SortedLinkedList<int> s1;
	s1.push(1);
	s1.push(5);
	s1.push(2);
	s1.push(8);

	SortedLinkedList<int> s2;
	s2.push(12);
	s2.push(4);
	s2.push(6);
	s2.push(20);

	SortedLinkedList<int> result = merge(s1, s2);

	for (SortedLinkedList<int>::Iterator i = result.begin(); i != result.end(); ++i)
	{
		std::cout << *i << " ";
	}

	return 0;
}