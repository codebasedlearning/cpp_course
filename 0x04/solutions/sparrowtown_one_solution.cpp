// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * Sparrowtown solution.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>

using std::cout, std::endl, std::ostream;
using std::string, std::string_view;

template <typename T>
class fraction {
    T num_{};                               // numerator
    T denom_{1};                            // denominator

public:
    fraction() = default;

    // Assume T is a primitive type, so no const ref.
    fraction(T num, T denom) : num_{num}, denom_{denom} {}

    fraction(const fraction &frac) = default;

    ~fraction() = default;

    [[nodiscard]] T num() const { return num_; }
    [[nodiscard]] T denom() const { return denom_; }

    void set_num(T num) { num_ = num; }
    void set_denom(T denom) { denom_ = denom; }

    explicit operator double() const { return static_cast<double>(num_) / static_cast<double>(denom_); }
};

template <typename T>
ostream& operator<<(ostream &os, const fraction<T> &frac) {
    os << frac.num() << "/" << frac.denom();
    return os;
}

int main() {
    cout << "\n--- " << __FILE__ << " ---" << endl;

    fraction<int> f1;
    fraction<int> f2{2, 3};
    fraction<int> f3{f2};

    cout << " 1| f1=" << f1 << " = " << double{f1} << endl;
    cout << " 2| f2=" << f2 << " = " << double{f2} << endl;
    cout << " 3| f3=" << f3 << " = " << double{f3} << endl;

    cout << " 4| f3.num=" << f3.num() << ", f3.denom=" << f3.denom() << endl;

    f3.set_num(4);
    f3.set_denom(5);
    cout << " 5| f3=" << f3 << " = " << double{f3} << endl;

    fraction<long> g1{1, 2};
    cout << " 6| g1=" << g1 << " = " << double{g1} << endl;

    return EXIT_SUCCESS;
}
