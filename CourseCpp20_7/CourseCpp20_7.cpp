#include <iostream>
#include <vector>
//#include <algorithm>
#include <numeric>

enum class Number { One = 1, Two, Three };

using enum Number;

struct SomeNumber {
	//using enum Number; 
};

struct A {
	/*constexpr*/ A() = default;
	constexpr virtual int values() const { return 42; }
};

struct B : A {
	/*constexpr*/ //B() {}
	constexpr int values() const override { return 18; }
};

constexpr int add(const A& x, const A& y) {
	return x.values() + y.values();
}

//constexpr const std::vector<int> v //it should compile?

constexpr int sum_vec(const std::vector<int>& data) {
	int result{};
	for (const auto& n : data)
		result += n;
	return result;
}

constexpr int sum_vec2(const std::vector<int>& data) {

	return std::reduce(data.cbegin(), data.cend(), 0,
		[](auto a, auto b) { return a + b; });
}

static constinit const int fact = 10;
static constinit int fact2 = fact*2;

int main()
{
	//SomeNumber sn;
	//std::cout << static_cast<int>(sn.Three) << std::endl;
	//std::cout << static_cast<int>(SomeNumber::One) << std::endl;

	Number num(Number::Two);

	switch (num) {
	case Number::One:
		std::cout << "One...\n";
		break;

	case Number::Two:
		std::cout << "Two...\n";
		break;

	case Number::Three:
		std::cout << "Three...\n";
		break;
	}

	switch (num) {
		//using enum Number;
	case One:
		std::cout << "One...\n";
		break;

	case Two:
		std::cout << "Two...\n";
		break;

	case Three:
		std::cout << "Three...\n";
		break;
	}

	constexpr A a1, a2;
	constexpr int sum = add(A{}, B{});
	constexpr int sum2 = add(a1, a2);

	//constexpr int a = sum_vec(std::vector{1, 2, 3}); //???
	//constexpr int b = sum_vec2(std::vector{1, 2, 3});
}