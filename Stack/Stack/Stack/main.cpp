#include <iostream>
#include "Stack.h"

int main()
{
	Stack<int> s1;

	s1.push(1);
	s1.push(2);
	s1.push(3);

	int x = s1.pop();

	std::cout << x << std::endl;

	s1.pop();
	s1.pop();

	std::cout << s1.isEmpty() << std::endl;

	Stack<int> s2;
	s2.push(11);
	s2.push(12);
	s2.push(13);

	s1 = s2;

	std::cout << s1.pop();

	return 0;
}