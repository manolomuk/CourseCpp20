#include <iostream>
#include <source_location>
#include <vector>
#include <format>
//#include <print>

void logit(const std::string& msg, std::source_location sl = std::source_location::current()) {
	std::cout << msg << " " << sl.function_name() << " " << sl.line() << '\n';
}

void do_work() {
	logit("Some info...");
}

auto get_data() { //c++14?
	return std::vector{ 4,5,6,7,8 };
}

struct A {
	~A() {
		//std::cout << "Destroying an A...\n";
	}
};

int main()
{
	do_work();
	logit("Just a test...");

	for (int cnt{}; const auto & n : get_data()) {
		std::cout << cnt++ << " " << n << std::endl;
	}

	for (auto data = get_data(); const auto & n : data) {
		std::cout << n << std::endl;
	}

	auto ptr = std::make_shared<A[]>(7);
	std::shared_ptr<int[7]> sp; //<--how to assign an array?

	std::vector data{ 1, 2, 3, 4, 5, 6, 7, 8, 5, 4, 3 };
	std::ranges::copy(data, std::ostream_iterator<int>(std::cout, ", "));
	std::cout << std::endl;

	std::erase(data, 5);
	std::ranges::copy(data, std::ostream_iterator<int>(std::cout, ", "));
	std::cout << std::endl;

	std::vector data2{ 1, 2, 3, 4, 5, 6, 7, 8, 5, 4, 3 };
	[[maybe_unused]] auto it = std::remove(data2.begin(), data2.end(), 5);
	std::ranges::copy(data2, std::ostream_iterator<int>(std::cout, ", "));
	std::cout << std::endl;

	std::string msg = std::format("int: {}, double: {}, float: {}", 10, 25.0, 15.0f);
	std::cout << msg << std::endl;

	std::string msg2;
	std::format_to(std::back_inserter(msg2), "int: {}, double: {}, float: {}", 10, 25.0, 15.0f);
	std::cout << msg2 << std::endl;

	auto args = std::make_format_args(10, 25.0, 15.0f);
	std::string msg3;
	std::vformat_to(std::back_inserter(msg3), "int: {}, double: {}, float: {}", args);
	std::cout << msg3 << std::endl;

	bool b{ true };
	char ch{ 'w' };
	std::string str{ "Greetings" };
	std::cout << std::format("b{:s}, ch{:c}, str{:s}\n", b, ch, str);

	std::cout << std::format("double: {1}, float: {2}, int: |{0:<+7}|, int: |{0:^+7}|, int: |{0:>+7}|, "
		"double: {1}\n", 10, 25.0, 15.0f);

	std::cout << std::format("double: |{1}|, double: |{1:<6.2}|, double: |{1:>8.4}|, float: {2}, int: |{0:<+7}|, "
		"int: |{0:>+7}|\n", 10, 25.0, 15.0f);

	std::cout << std::format("default:{0}, b:{0:b}, B:{0:B}, d:{0:d}, o:{0:o}, x:{0:x}, X:{0:X}\n", 267);
	std::cout << std::format("default:{0}, b:{0:#b}, B:{0:#B}, d:{0:#d}, o:{0:#o}, x:{0:#x}, X:{0:#X}\n", 267);

	std::cout << std::format("default:{0}, a:{0:a}, A:{0:A}, e:{0:e}, E:{0:E}, f:{0:f}, F:{0:F}\n", 2.5);
	std::cout << std::format("|{0:^+15.7f}|", 345.35);

	//std::println(std::cout, "double: {1}, float: {2}, int: |{0:<+7}|, int: |{0:^+7}|, int: |{0:>+7}|, double: {1}\n", 10, 25.0, 15.0f);
	//https://godbolt.org/z/q8rM9KqTY
	//https://godbolt.org/z/1746v46G1 
}