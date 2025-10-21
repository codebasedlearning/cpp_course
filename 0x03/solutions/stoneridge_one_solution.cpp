// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * This solution demonstrates coordinate points in C++:
 *   – Class declaration with member variables and methods
 *   – Constructor and copy constructor syntax
 *   – Getter/setter methods
 *   – Stream operator overloading.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>

using std::cout, std::endl, std::ostream;
using std::string, std::string_view;

class punkt {
    double x_{};
    double y_{};

public:
    punkt() = default;
    ~punkt() = default;

    punkt(double x, double y) : x_{x}, y_{y} {}; // (C)

    double x() const { return x_; };
    double y() const { return y_; };
    void set_x(double x) { x_ = x; }
    void set_y(double y) { y_ = y; }

    punkt(const punkt &p) = default;
};

ostream &operator<<(ostream &os, const punkt &p) {
    os << "(" << p.x() << ", " << p.y() << ")";
    return os;
}

int main() {
    cout << "\n--- " << __FILE__ << " ---" << endl;

    // Tests
    punkt punkt1;
    punkt punkt2(3.3, 4.4);
    punkt punkt3{punkt2};

    cout << " 1| " << punkt1 << endl;
    cout << " 2| " << punkt2 << endl;
    cout << " 3| " << punkt3 << endl;

    punkt1.set_x(1.1);
    punkt1.set_y(2.2);

    punkt3.set_x(5.5);
    punkt3.set_y(6.6);

    cout << " 4| " << punkt1 << endl;
    cout << " 5| " << punkt2 << endl;
    cout << " 6| " << punkt3 << endl;

    const punkt &punktref{punkt1};
    double x{punktref.x()};
    double y{punktref.y()};

    cout << " 7| x=" << x << ", y=" << y << endl;

    return EXIT_SUCCESS;
}
