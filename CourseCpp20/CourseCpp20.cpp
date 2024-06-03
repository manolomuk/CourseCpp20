//03/Jun/2024

#include <iostream>
#include <vector>

using std::cout;
using std::endl;

auto amax(auto&& x, auto&& y) {
	return x < y ? y : x;
}

auto get_name = []<typename T>(T t) {
	return typeid(T::value_type).name();
};

struct DataClass {
	int a;
	constexpr DataClass(int n) : a{ n } {}
	/*implicitly constexpr*/ int calc(int b) const {
		return a * b;
	}
};

template<DataClass dc> int dc_calc(int b) {
	return dc.calc(b);
}

using FunPtr = double(double);
template<FunPtr F> class Command {
public:
	/*constexpr*/ double execute(double d) {
		return F(d);
	}
};

template<typename... Args> auto lambda_variadic = [](Args&&... args) {
	return (args + ...);
};

template<typename... Args> auto lambda_variadic2 = [](Args&&... args) {
	return ([... args = std::forward<Args>(args)]() { return (args + ...); })();
};

template<typename T> requires (std::is_integral_v<T> || std::is_floating_point_v<T>) 
inline T a_max(T x, T y) {
	return x < y ? y : x;
}

template<typename Fun, typename T> requires std::invocable<Fun, T, T> T operate(Fun f, T a, T b) {
	return f(a, b);
}

template<typename T> concept Integral = std::is_integral_v<T>;
template<typename T> concept Floating = std::is_floating_point_v<T>;

template<Integral T> void do_output(T t) {
	cout << "Integral: " << t << endl;
}
template<Floating T> void do_output(T t) {
	cout << "Floating: " << t << endl;
}

template<typename T> void do_output2(T t) requires Integral<T> {
	cout << "Integral: " << t << endl;
}
template<typename T> void do_output2(T t) requires Floating<T> {
	cout << "Floating: " << t << endl;
}

//template<typename T> concept Numeric = Integral<T> || Floating<T>;
template<typename T> concept Numeric = Integral<T> || std::is_floating_point_v<T>;
template<typename T> void do_output3(T t) requires Numeric<T> {
	cout << "Numeric: " << t << endl;
}

template<typename It> concept MyIncrementor = requires(It it) {
	{++it} -> std::same_as<It&>;
	{it++} -> std::same_as<It>;
};

template<typename It> concept MyDerefer = requires(It it) {
	{*it} -> std::convertible_to<typename It::reference>;
};

template<MyIncrementor I> void display(I begin, I end) {
	for (auto it{ begin }; it != end; ++it) {
		cout << *it << ", ";
	}
	cout << '\n';
}

//template<typename I> concept Not_Equal = requires(I it1, I it2) {
//	{it1 != it2} -> std::convertible_to<bool>;
//};

struct Something {
	Something& operator++() {
		return *this;
	}
	Something operator++(int) {
		return *this;
	}
	int operator*() const {
		return 42;
	}
	using reference = int;
};

//try cref;
//or const T (for const member functions)
template<typename T> concept Stringable = requires(T t) { 
	{t.to_string() } -> std::same_as<std::string>;
	{std::as_const(t).to_string() } -> std::same_as<std::string>;

} && noexcept(std::declval<const T>().to_string());

template<Stringable T> void do_output(T&& t) {
	cout << t.to_string() << endl;
}

struct SomeData {
	std::string to_string() const noexcept {
		return "testing Stringable (const)...\n";
	}
	std::string to_string()  {
		return "testing Stringable (non const)...\n";
	}
};

struct Number {
	int _val;
	Number(int val) : _val(val) {}
	Number& operator+=(const Number& n) {
		_val += n._val;
		return *this;
	}
	int get_val() const {
		return _val;
	}
};

inline Number operator+(const Number lhs, const Number rhs) {
	Number temp(lhs);
	return temp += rhs;
}

template<typename T> concept Addable = requires(T n1, T n2) {
	{n1 += n2} -> std::convertible_to<T&>;
	{n1 + n2} -> std::convertible_to<T>;
};

template<Addable A> void do_add(A a1, A a2) {
	cout << (a1 + a2).get_val() << endl;
}

int main()
{
	int a{ 23 }, b{ 43 }, c;
	c = amax(a, b);
	cout << "Max: " << c << endl;

	cout << get_name(std::vector{ 3.3, 6.2 }) << endl;

	cout << dc_calc<DataClass{4}>(6) << endl;

	Command < [](double d) /*constexpr*/ -> double { return d * d; } > cmd;
	cout << cmd.execute(7) << endl;

	cout << lambda_variadic<int, int>(1, 2) << endl;
	//cout << lambda_variadic(1, 2) << endl; //use of a variable template requires template argument list
	cout << lambda_variadic2<int, int>(1, 2) << endl;

	cout << a_max(2, 3) << endl;

	auto add = [](double x, double y) { return x + y; };
	cout << operate(add, 23.3, 65.2) << endl;

	do_output(23.2);
	do_output(654);

	do_output2(23.2);
	do_output2(654);

	do_output3(3.1415);

	std::vector data{ 1, 2, 3, 4 };
	display(data.cbegin(), data.cend());
	//display(Something{}, Something{}); //no matching overloaded function found; the associated constraints are not satisfied

	do_output(SomeData{}); //it calls the non-const if available

	do_add(Number{ 5 }, Number{ 81 });

	return EXIT_SUCCESS;
}