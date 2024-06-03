#include <iostream>
#include <span>
#include <numeric>
#include <algorithm>
#include <vector>
#include <array>
#include <ranges>
#include <sstream>

#define LINE {std::cout << '\n';}

inline int my_sum(std::span<int> data) {

    int result = std::accumulate(data.begin(), data.end(), 0,
        std::plus<int>());
    return result;
}

struct Data {
    int val;
    Data(int v) : val(v) {}
    int get_val() const {
        return val;
    }
};

struct MySentinel {};

template<typename T> constexpr bool operator==(T ptr, MySentinel) noexcept{ 
    return *ptr == -1;
};

std::vector<int> get_data() {
    return std::vector<int>{ 1, 2, 3 };
}

std::string get_msg() {
    return "Greetings";
}

int main()
{
    std::vector data{ 1, 2, 3 };
    std::cout << my_sum(data) << std::endl;

    int arr[] = { 1, 2, 3 };
    std::cout << my_sum(arr) << std::endl;
    std::cout << std::accumulate(std::begin(arr), std::end(arr), 0,
        [](int a, int b) {return a + b; }) << std::endl;

    std::cout << sizeof(int) << std::endl;
    std::cout << sizeof(int*) << std::endl;
    std::cout << sizeof(std::vector<int>(10)) << std::endl;
    std::cout << sizeof(std::span<int>{}) << std::endl;

    std::vector<int> data2(10);
    std::fill(data2.begin(), data2.end(), 6);
    std::ranges::fill(data2, 7);
    std::ranges::fill(data2.begin(), data2.cend(), 7); //cend is a sentinel

    std::vector<Data> data3{ 2, 4, 6, 8 };
    auto found = std::ranges::find(data3, 6, &Data::get_val);
    std::cout << std::boolalpha << (found != data3.end()) << std::endl;

    std::array<int, 7> numbers{ 1, 2, 3, 4, 5, 6, -1 };
    for (auto it{ std::ranges::begin(numbers) }; it != MySentinel{}; ++it) {
        std::cout << *it << ", ";
    }
    std::cout << '\n';

    std::ranges::copy(std::ranges::cbegin(numbers), MySentinel{}, std::ostream_iterator<int>(std::cout, ", "));
    std::cout << char(10);

    for (auto i : std::ranges::iota_view{ 0, 10 }) {
        std::cout << i << ", ";
    }
    std::cout << '\n';

    for (auto i : std::views::iota(0, 10)) {
        std::cout << i << ", ";
    }
    std::cout << '\n';

    for (auto i : std::views::iota(data.begin(), data.end())) {
        std::cout << *i << ", ";
    }
    std::cout << '\n';

    //auto results = std::ranges::istream_view<std::string>(std::cin);
    //std::ranges::copy(results, std::ostream_iterator<std::string>{std::cout, ", "});
    //LINE

    std::istringstream msg{ "34.3 65.5 654.2" };
    auto results = std::ranges::istream_view<std::string>(msg);
    std::ranges::copy(results, std::ostream_iterator<std::string>{std::cout, ", "});
    LINE;

    auto found2 = std::ranges::find(get_data(), 2);
    //std::cout << (*found2) << std:end; //dangling

    auto found3 = std::ranges::find(std::string_view(get_msg()), 'e');
    std::cout << *found3 << std::endl;

    //TODO use std::ranges::find with a std::span
    //std::span<int> sp{ get_data().begin(), get_data.end() };

    return EXIT_SUCCESS;
}