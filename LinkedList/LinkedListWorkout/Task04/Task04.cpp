#include <iostream>
#include <functional>
#include "LinkedList.h"

bool orFunc(bool firstNum, bool secondNum)
{
	return firstNum || secondNum;
}

template <typename T, typename Y>
T foldr(std::function<T(Y, T)> func, T item, LinkedList<Y>& list)
{
	Y currentElement = list.getFirst();
	list.pop();

	if (!list.isEmpty())
	{
		return func(currentElement, foldr(func, item, list));
	}

	return func(currentElement, item);
}

int main()
{
	LinkedList<bool> list;
	list.push(false);
	list.push(true);
	list.push(false);

	std::function<bool(bool, bool)> func = orFunc;

	std::cout << foldr(func, false, list);

	return 0;
}