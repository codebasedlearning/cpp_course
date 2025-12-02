// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * Deerwoods solution.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>

using std::cout, std::endl, std::ostream;
using std::string, std::string_view;

template <typename T>
class nullable {
    using value_type = T;                   // or: typedef T value_type;

    value_type value{};
    bool is_null{true};

public:
    nullable() = default;

    explicit nullable(const value_type &val) : value{val}, is_null{false} {};

    nullable(const nullable &val) : value{val.value}, is_null{val.is_null} {};

    nullable& operator=(const value_type &val) {
        value = val;
        is_null = false;
        return *this;
    }

    void reset() { is_null = true; }

    nullable& operator+=(const value_type &val) {
        if (!is_null) { value += val; }
        return *this;
    }

    bool operator!() const { return !is_null; }

    operator T() const { return value; }

    friend ostream &operator<<(ostream &os, const nullable &num) {
        if (num.is_null) {
            os << "NULL";
        } else {
            os << num.value;
        }
        return os;
    }
};

template <typename T>
nullable<T> operator+(const nullable<T> &num1, const nullable<T> &num2) {
    nullable<T> res{num1};
    return res += num2;
}

int main() {
    cout << "\n--- " << __FILE__ << " ---" << endl;

    nullable<int> num0{};
    nullable<int> num1(23);
    nullable<int> num2(num1);

    cout << " 1| num0:" << num0 << ", num1:" << num1 << ", num2:" << num2 << endl;

    num0 = 0;
    num1 = 1;
    num2.reset();

    cout << " 2| num0:" << num0 << ", num1:" << num1 << ", num2:" << num2 << endl;

    num0 += 10;
    num1 += 10;
    num2 += 10;

    cout << " 3| num0:" << num0 << ", num1:" << num1 << ", num2:" << num2 << endl;

    cout << " 4| !num0:" << !num0 << ", !num1:" << !num1 << ", !num2:" << !num2 << endl;

    num0 = 0;
    num1 = 1;
    num2 = 2;

    cout << " 5| num0:" << num0 << ", num1:" << num1 << ", num2:" << num2 << endl;

    cout << " 6| (int)num2:" << static_cast<int>(num2) << endl;
    cout << " 7| num1 + num2:" << num1 + num2 << endl;

    return EXIT_SUCCESS;
}
