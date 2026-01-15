// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * This file contains a few examples using the algorithms library.
 * More can be found at
 *      https://en.cppreference.com/w/cpp/algorithm.html
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>
#include <functional>
#include <array>
#include <algorithm>
#include <ranges>

using std::cout, std::endl, std::ostream;
using std::string, std::string_view;
using std::array;

void algorithms_examples();

int main() {
    cout << endl << "--- " << __FILE__ << " ---" << endl << endl;

    algorithms_examples();

    return EXIT_SUCCESS;
}

// print
template <typename T, size_t DIM>
ostream& operator<<(ostream& os, const array<T,DIM>& a) {
    os << "[ ";
    for (auto x : a) {
        os << x << " ";
    }
    os << "]";
    return os;
}

/*
 * The algorithms library and the range library (from C++20) define functions for a variety
 * of purposes that operate on ranges or collections.
 */

void algorithms_examples() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    array a = {5, 7, 4, 2, 8, 6, 1, 9, 0, 3, 5};
    cout << " 1| a=" << a << endl;

    // Batch operations
    int sum1{0}, sum2{0};
    std::for_each(a.begin(), a.end(), [&sum1](int i) { sum1 += i; });
    std::ranges::for_each(a, [&sum2](int i){ sum2 += i; });
    cout << " 2| for_each, sum1=" << sum1 << ", sum2=" << sum2 << endl;

    // Search operations
    cout << " 3| all>=0 ? " << std::ranges::all_of(a, [](int i){return i>=0;}) << endl;
    cout << " 4| count>6:" << std::ranges::count_if(a, [](int i){return i>6;}) << endl;

    array b = {1, 2, 4};
    auto find_one = std::ranges::find_first_of(a, b);
    cout << " 5| find first of ? " << (find_one!=a.end() ? std::distance(a.begin(),find_one) : -1) << endl;

    // Generation operations
    int f1{0},f2{0};
    array<int,10> v{};
    std::ranges::generate(v, [&f1,&f2] { int f{(f2>0)?f1+f2:1}; f1=f2; f2=f; return f; });
    cout << " 6| generate fib, v=" << v << endl;

    // Order-changing operations
    std::ranges::reverse(v);
    cout << " 7| reverse, v=" << v << endl;

    // Sorting operations
    cout << " 8| is a sorted ? " << std::ranges::is_sorted(a) << endl;
    std::ranges::sort(a);
    cout << " 9| a=" << a << ", now sorted ? " << std::ranges::is_sorted(a) << endl;

    // and many more...

    // and there is also the ranges lib...
    // auto view = a | std::views::filter([](int n){ return n % 2 == 0; });
}
