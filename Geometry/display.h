#pragma once
#include <algorithm>
#include <iostream>

/**
* T: type of values to display
* InputIt: iterator on values of type T
*/
template<class T, class InputIt>
void display(InputIt first, InputIt last) {
	std::copy(first, last, std::ostream_iterator<T>(std::cout, ", "));
	std::cout << std::endl;
}

template<class InputIt, class F>
void display(InputIt first, InputIt last, F adapter) {
	// for (; first != last; ++first)
	while (first != last) {
		auto iteratedValue = *first;
		auto printValue = adapter(iteratedValue);
		std::cout << printValue << ", ";
		++first;
	}
	std::cout << std::endl;
}
