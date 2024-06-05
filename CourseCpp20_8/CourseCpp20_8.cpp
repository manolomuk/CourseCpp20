#include <iostream>

struct some_data {
	int a{ 1 }, b{ 2 };
};

template<typename T> class Num {
	T _val;
public:
	Num(T val) : _val(val) {}
	explicit(not std::is_integral_v<T>) operator T() const {
		return _val;
	}
};

int main()
{
	some_data sd{ .b = 32 }; //designated initializer
	std::cout << sd.a << " " << sd.b << "\n";

	Num num{ 23.3 };
	double val = static_cast<double>(num);
	std::cout << val << "\n";

	Num num2{ 2 };
	int val2 = num2;
	std::cout << val2 << "\n";

	int n;
	std::cin >> n;

	if (n > 0) [[likely]]
		std::cout << "Greater than zero...\n";
	else [[unlikely]]
		std::cout << "Not greater than zero...\n";
}