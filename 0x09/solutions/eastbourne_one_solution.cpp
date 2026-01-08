// (C) 2025 A.Voß, a.voss@fh-aachen.de, cpp@codebasedlearning.dev

/*
 * Eastbourne solution.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>
#include <iomanip>

using std::cout, std::endl;
using std::string, std::string_view;

template <typename T> class point {
private:
    T x_{};
    T y_{};

public:
    point() = default;
    point(T x, T y) : x_{x}, y_{y} {};

    [[nodiscard]] T x() const { return x_; };
    [[nodiscard]] T y() const { return y_; };

    // [...]
};

template <> class point<bool> {
private:
    point() = default;
};

template <typename T>
std::ostream &operator<<(std::ostream &os, const point<T> &pt) {
    return os << "(" << pt.x() << "," << pt.y() << ")";
}

int main() {
    cout << endl << "--- " << __FILE__ << " ---" << endl << endl;

    point<int> pt1(11,22);
    cout << " 1| pt1=" << pt1 << endl;

    // point<bool> pt2;

    return EXIT_SUCCESS;
}
