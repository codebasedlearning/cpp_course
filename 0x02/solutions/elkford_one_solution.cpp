// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

#include <iostream>
#include <string>
#include <cstdlib>
using std::cout, std::endl, std::ostream;
using std::string;

constexpr int dim = 3;                          // global var

struct polynom {
    double coeffs[dim];                     // raw array
};

// shift-operator, used for output
ostream &operator<<(ostream &os, const polynom &p) {
    os << p.coeffs[0] << " + " << p.coeffs[1] << "x" << " + " << p.coeffs[2] << "x^2";
    return os;
}

double eval(const polynom &p, const double &x);

int main() {
    cout << "\n--- " << __FILE__ << " ---\n" << endl;

    // test code
    polynom p{2.0, 3.0, 4.0};
    cout << "p: " << p << endl;
    cout << "eval(p, 4.0): " << eval(p, 4.0) << endl;

    return EXIT_SUCCESS;
}

double eval(const polynom &p, const double &x) {
    return p.coeffs[0] + x * (p.coeffs[1] + x * p.coeffs[2]);
}
