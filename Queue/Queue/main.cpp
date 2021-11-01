#include <iostream>
#include "Queue.h"

int main()
{
	Queue<int> q;
	q.enqueue(1);
	q.enqueue(2);
	q.enqueue(3);
	q.enqueue(4);

	std::cout << std::boolalpha << (q.back() == 4) << std::endl;
	std::cout << std::boolalpha << (q.front() == 1) << std::endl;

	q.dequeue();
	q.dequeue();
	q.dequeue();
	q.dequeue();

	std::cout << std::boolalpha << q.isEmpty();

	return 0;
}