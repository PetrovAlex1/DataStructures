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

	dq1.pop_front();
	dq1.pop_front();
	dq1.pop_front();
	dq1.push_back(12);
	dq1.push_back(15);
	dq1.push_back(25);
	dq1.push_back(17);
	dq1.push_back(8);
	dq1.push_back(22);
	dq1.push_back(267);

	for (Deque<int>::DQIterator i = dq1.begin(); i != dq1.end(); ++i)
	{
		std::cout << *i << " ";
	}

	std::cout << std::endl;

	return  0;
}