#include <iostream>
#include <ranges>
#include <vector>
#include <algorithm>

int main()
{
	int data[]{ 3, 4, 5, 6, 7, 8, 9 };
	auto results = data | std::views::filter([](auto n) { return n % 2 == 0; });

	std::copy(results.begin(), results.end(), std::ostream_iterator<int>(std::cout, ", "));

	return EXIT_SUCCESS;
}