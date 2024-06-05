#include <iostream>
#include <ranges>
#include <vector>
//#include <algorithm>
//#include <string>
#include <map>
//#include <iterator>
#include <tuple>

template<typename T> inline auto myodd(T&& t) requires std::ranges::range<T> {
	return std::views::filter(std::forward<T>(t), [](auto n) { return n % 2 != 0; });
}

template<typename T> inline auto myodd2(T&& t) requires std::ranges::range<T> {
	return std::forward<T>(t) | std::views::filter([](auto n) { return n % 2 != 0; });
}

//template<typename T> constexpr auto myodd3() {
//	return std::views::filter([](auto n) { return n % 2 != 0; });
//}
constexpr auto myodd3() {
	return std::views::filter([](auto n) { return n % 2 != 0; });
}

int main()
{
	const int data[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	auto results = data | std::views::filter([](auto n) { return n % 2 == 0; });
	//std::copy(results.begin(), results.end(), std::ostream_iterator<int>(std::cout, ", "));
	//std::cout << '\n';

	auto results2 = data | std::views::drop(0) |
		std::views::filter([](auto n) { return n % 2 == 0; }) |
		std::views::transform([](auto n) {return n * n; }) |
		std::views::take(2);

	auto results3 = data | std::views::take_while([](auto n) { return n < 4; });
	//std::copy(results3.begin(), results3.end(), std::ostream_iterator<int>(std::cout, ", ")); //error

	auto results4 = data | std::views::take_while([](auto n) { return n < 4; }) | std::views::common;
	std::copy(results4.begin(), results4.end(), std::ostream_iterator<int>(std::cout, ", ")); std::cout << '\n';

	std::map<int, std::string> m{ {1, "one"}, {2, "two"}, {3, "three"} };
	auto results5 = m | std::views::values;
	//std::ranges::copy(results5, std::ostream_iterator<std::string>{std::cout, ", "}); std::cout << '\n';

	std::vector<std::tuple<int, std::string, std::string>> tup{ {1, "one", "I"}, {2, "two", "II"}, {3, "three", "III"} };
	auto results6 = tup | std::views::elements<2>;
	std::ranges::copy(results6, std::ostream_iterator<std::string>{std::cout, ", "}); std::cout << '\n';

	//key, value can be applied to tuples too

	std::ranges::copy(myodd(std::views::iota(1, 20)), std::ostream_iterator<int>{std::cout, ", "}); std::cout << '\n';
	std::ranges::copy(myodd2(std::views::iota(1, 20)), std::ostream_iterator<int>{std::cout, ", "}); std::cout << '\n';

	auto results7 = std::views::iota(1, 20) | myodd3();
	std::copy(results7.begin(), results7.end(), std::ostream_iterator<int>(std::cout, ", ")); std::cout << '\n';

	return EXIT_SUCCESS;
}