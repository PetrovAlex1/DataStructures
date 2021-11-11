#include <iostream>
#include "LinkedList.h"

bool compare(const char* firstString, const char* secondString)
{
	int i = 0;

	while (firstString[i] != '\0' && secondString[i] != '\0')
	{
		if (firstString[i] != secondString[i])
		{
			return false;
		}

		i++;
	}

	return true;
}

int getCountEqualStrings(LinkedList<char*>& list, const char* string)
{
	int counter = 0;

	for (LinkedList<char*>::Iterator i = list.begin(); i != list.end(); ++i)
	{
		if (compare(*i, string))
		{
			counter++;
		}
	}

	return counter;
}

int main()
{
	LinkedList<char*> list;

	for (int i = 0; i < 5; i++)
	{
		char* buffer = new char[16];
		std::cin.getline(buffer, 16);
		list.push(buffer);
	}

	std::cout << getCountEqualStrings(list, "AliBaba");

	return 0;
}