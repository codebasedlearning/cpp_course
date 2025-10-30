// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * This file demonstrates C++ generics through several examples:
 *  – Template function 'join' for printing containers
 *  – point class template with x,y coordinates
 *  – my_array class template implementing fixed-size array
 *  – my_pair class template with pair-making function.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>
#include <sstream>
#include <array>
#include <vector>
#include <set>
#include <ranges>

using std::cout, std::endl, std::ostream;
using std::string, std::string_view;
using std::array, std::vector, std::set;
using std::ostringstream;
using std::initializer_list;
using std::out_of_range;

void printing_containers();
void printing_points();
void printing_my_arrays();
void printing_my_pairs();

int main() {
    cout << "\n--- " << __FILE__ << " ---" << endl;

    printing_containers();
    printing_points();
    printing_my_arrays();
    printing_my_pairs();

    return EXIT_SUCCESS;
}

/*
 * This is a generic function, called a 'template function' in C++.
 * 'T' is some container class with range-based for.
 * (Older code often uses 'template<class T>')
 */
template <typename T>
string join(const T &container) {
    ostringstream os;
    // string_view delim;                      // "delimiter string" idiom
    // for (const auto &x : container) {
    //     os << delim << x;
    //     delim = ",";                         // save here, but never construct a string_view from a temporary.
    // }
    bool first = true;
    for (const auto &x : container) {
        if (!first) os << ',';
        os << x;
        first = false;
    }
    return os.str();
}

void printing_containers() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    const array a{1, 1, 2, 3};
    cout << " 1| a=[" << join(a) << "]" << endl;

    const vector v{2, 3, 5, 7};
    cout << " 2| v=[" << join(v) << "]" << endl;

    set s{1, 1, 2, 3};
    cout << " 3| s={" << join(s) << "}" << endl;
}

/*
 * 'using', or 'typedef', defines a concrete data type under a new name, here as example
 * 'math_type' for a type that is used for calculations (float, double, long double).
 * The name can be freely chosen, but endings like '.._type' or '.._t' are commonly found.
 *
 * You cannot make a templated 'typedef', but you can make a template alias with 'using'.
 */
using math_type = double;                   // old: typedef double math_type;
const math_type PI{3.1415926};

template<typename T>
struct point {
    using value_type = T;
    value_type x{}, y{};

    // This works for all points, no extra template necessary.
    friend ostream& operator<<(ostream& os, const point& p) {
        os << "(" << p.x << "," << p.y << ")";
        return os;
    }
};

void printing_points() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    point p1{1,2};
    point<int> p2{3,4};
    point<int>::value_type v{5};
    cout << " 1| p1=" << p1 << ", p2=" << p2 << ", v=" << v << endl;
}

/*
 * A very simple (!) example of a generic raw array class like std::array. 'size' is a
 * static class function that returns the dimension. We have defined the [] operators, so
 * the array itself, i.e. 'data', can remain private.
 * There is a ctor with a so-called initializer_list. The compiler can handle constructor
 * calls with an arbitrarily long list of arguments.
 * Note that 'DIM' is not a type but a constant integer.
 */
template<typename T, size_t DIM>
class my_array {
public:
    static size_t size() { return DIM; }
    using value_type = T;

    my_array() = default;
    my_array(const initializer_list<value_type> l) {
        size_t i{0};
        for (auto& x : l) {
            if (i>=size())
                throw out_of_range("list too long");
            data[i++] = x;
        }
    }

    const value_type& operator[](size_t n) const { return data[n]; }
    value_type& operator[](size_t n) { return data[n]; }

    friend ostream& operator<<(ostream &os, const my_array &a) {
        os << '[';
        for (size_t i = 0; i < DIM; ++i) {
            if (i) os << ',';
            os << a.data[i];
        }
        return os << ']';
    }

private:
    value_type data[DIM];
};

void printing_my_arrays() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    my_array<int,3> ai{1,2,3};              // No class template argument deduction (CTAD) available.
    my_array<char,4> ac{'H','u','h','u'};
    cout << " 1| ai=" << ai << ", ac=" << ac << endl;
}

/*
 * my_pair is a template class with two type parameters. Additionally, we kept the constructor
 * private here to demonstrate the 'make_my_pair' (template) function (friend of class).
 */
template<typename T1, typename T2>
class my_pair {
    my_pair(const T1 &first, const T2 &second) : first(first), second(second) {};

    template<typename S1, typename S2>
    friend my_pair<S1,S2> make_my_pair(const S1& first, const S2& second);

    friend ostream& operator<<(ostream &os, const my_pair &p) {
        return os << "(" << p.first << "," << p.second << ")";
    }

public:
    using first_type = T1;
    using second_type = T2;
    first_type first;
    second_type second;
};

template<typename S1, typename S2>
my_pair<S1,S2> make_my_pair(const S1& first, const S2& second) {
    // copy-list-initialize the return object from the given braced-init-list.
    return {first,second};
}

void printing_my_pairs() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    // my_pair p1{1,2};                     // ctor not public
    auto p = make_my_pair(1,2);
    cout << " 1| p=" << p << ", p.first=" << p.first << ", p.second=" << p.second << endl;
}
