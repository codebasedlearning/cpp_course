// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * This solution demonstrates a class for fractions in C++:
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

class fraction {
    int num_{};   // numerator
    int denom_{}; // denominator

public:
    fraction() = default;
    ~fraction() = default;

    fraction(int num, int denom) : num_{num}, denom_{denom} {}

    int num() const { return num_; }
    int denom() const { return denom_; }
    void set_num(int num) { num_ = num; }
    void set_denom(int denom) { denom_ = denom; }

    fraction(const fraction &frac) = default;
};

ostream &operator<<(ostream &os, const fraction &frac) {
    os << frac.num() << "/" << frac.denom();
    return os;
}

int main() {
    cout << "\n--- " << __FILE__ << " ---" << endl;

    // Tests
    fraction frac1;
    fraction frac2{2, 3};
    fraction frac3{frac2};

    cout << " 1| " << frac1 << endl;
    cout << " 2| " << frac2 << endl;
    cout << " 3| " << frac3 << endl;

    frac1 = fraction{1, 2};
    frac3 = fraction{5, 6};

    cout << " 4| " << frac1 << endl;
    cout << " 5| " << frac2 << endl;
    cout << " 6| " << frac3 << endl;

    const fraction &fracref{frac1};
    int num{fracref.num()};
    int denom{fracref.denom()};
    cout << " 7| num: " << num << ", denom" << denom << endl;

    return EXIT_SUCCESS;
}
