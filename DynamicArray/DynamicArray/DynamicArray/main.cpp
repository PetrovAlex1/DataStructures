#include <iostream>
#include "Dynamicarray.h"

int main()
{
	DynamicArray<int> d1;
	d1.append(1);
	d1.append(2);
	d1.append(3);
	d1.append(4);

	for (DynamicArray<int>::DAIterator i = d1.begin(); i != d1.end(); ++i)
	{
		std::cout << *i << " ";
	}

	std::cout << std::endl;

	std::cout << std::boolalpha << d1.contains(3) << std::endl;
	int x = d1.getElement(0);
	std::cout << x << std::endl;
	std::cout << "Size: " << d1.getSize() << std::endl;
	std::cout << d1[3] << std::endl;
	d1.clear();
	std::cout << std::boolalpha << d1.isEmpty();

	return 0;
}