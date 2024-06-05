#include <iostream>
#include <functional>
#include <compare>

//https://cppinsights.io/
struct ValueClass {
	int _val{};
	//double _d_val;
	//ValueClass(int val, double dval) : _val(val), _d_val(dval){}
	ValueClass(int val) : _val(val) {}
	auto operator<=>(const ValueClass& rhs) const = default;
	//bool operator<(const ValueClass& other) { return _val<other._val;}
	int calc(int b, int c) const {
		return _val + b + c;
	}
};

int compose(int a, int b, int c) {
	return 100 * a + 10 * b + c;
}

int main()
{
	//  ValueClass a{4, 1.}, b{7, 2.3};
	ValueClass a{ 4 }, b{ 7 };

	bool result;
	result = a < b;
	result = a < 23;
	result = 23 < a;
	result = b >= a;
	result = a <= b;

	auto fun = std::bind(compose, std::placeholders::_2, std::placeholders::_1, 7);
	std::cout << fun(1, 2) << std::endl;

	auto fun2 = std::bind_front(compose, 2);
	std::cout << fun2(1, 7) << std::endl;

	ValueClass vc{ 7 };
	auto fun3 = std::bind_front(&ValueClass::calc, vc, 1); //vc is captured by copy
	std::cout << fun3(2) << std::endl;

	vc._val = 10;
	std::cout << fun3(2) << std::endl; //still uses 7

	vc._val = 7;
	auto fun4 = std::bind_front(&ValueClass::calc, std::ref(vc), 1);
	vc._val = 10;
	std::cout << fun4(2) << std::endl;

	vc._val = 7;
	auto lam = [vc](int i) { return vc.calc(1, 2); }; //vc is captured by copy
	std::cout << lam(2) << std::endl;

	vc._val = 10;
	std::cout << lam(2) << std::endl;
}
