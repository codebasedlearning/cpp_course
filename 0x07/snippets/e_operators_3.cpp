// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * This snippet demonstrates operator overloading:
 *  – Implementing function call operator () for polynomial evaluation
 *  – Implementing index operator [] for element access
 *  – Implementing stream output operator <<.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>
#include <stdexcept>
#include <array>

using std::cout, std::endl, std::ostream;
using std::string, std::string_view;
using std::invalid_argument;
using std::array;

void eval_polynom();

int main() {
    cout << endl << "--- " << __FILE__ << " ---" << endl << endl;

    eval_polynom();

    return EXIT_SUCCESS;
}

constexpr int dim{4};

class polynom {
public:
    array<double,dim> coefficients;

    // double eval(double x) { ...
    double operator()(const double x) const {
        double r{0.0};
        for (int i=dim-1; i>=1; --i)
            r = x*(coefficients[i]+r);
        r += coefficients[0];
        return r;
    }

    // double at(size_t i) const { ...
    double operator[](const size_t i) const {
        if (i>=dim)
            throw invalid_argument("index too large");
        return coefficients[i];
    }

    // from C++23: double operator[](size_t i, size_t j)

    // double& at(size_t i) { ...
    double& operator[](const size_t i) {
        if (i>=dim)
            throw invalid_argument("index too large");
        return coefficients[i];
    }
};

ostream& operator<<(ostream& os, const polynom& p) {
    os << p[0];
    for (int i=1; i<dim; ++i)
        os << "+" << p[i] <<"x^" << i;
    return os;
}

void eval_polynom() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    polynom p{1.0,2.0,3.0,4.0};             // make it const, what happens?

    cout << " 1| p=" << p << endl;

    cout << " 2| p(1)=" << p(1.0) << endl;
    cout << " 3| p(2)=" << p(2.0) << endl;

    cout << " 4| p[3]=" << p[3] << endl;

    p[2] = 12.0;
    cout << " 5| p[2]=" << p[2] << endl;

    cout << " 6| p=" << p << endl;
}
