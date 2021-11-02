#include <iostream>
#include "Deque.h"
#include "DebugAllocator.h"

int main()
{
	Deque<int, DebugAllocator<int>> dq1;
	dq1.push_back(1);
	dq1.push_back(2);
	dq1.push_back(3);
	dq1.push_back(4);
	dq1.push_back(5);
	dq1.push_back(53);

	std::cout << dq1.getAllocator().getAllocationsCount() << std::endl;

	Deque<int, DebugAllocator<int>> dq2;
	dq2 = dq1;

	std::cout << dq2.getAllocator().getAllocationsCount() << std::endl;

	for (Deque<int>::DQIterator i = dq1.begin(); i != dq1.end(); ++i)
	{
		std::cout << *i << " ";
	}

	return  0;
}