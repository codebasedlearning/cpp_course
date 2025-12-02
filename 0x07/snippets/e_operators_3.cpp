// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 *
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

void assign_values();

int main() {
    cout << endl << "--- " << __FILE__ << " ---" << endl << endl;

    assign_values();

    return EXIT_SUCCESS;
}

constexpr int dim{4};

class polynom {                                             // (A)
public:
    array<double,dim> coefficients;

    //  double eval(double x) {
    double operator()(const double x) const {                           // (B)
        double r{0.0};
        for (int i=dim-1; i>=1; --i)
            r = x*(coefficients[i]+r);
        r += coefficients[0];
        return r;
    }

    //  double at(size_t i) const {
    double operator[](const size_t i) const {                     // (C)
        if (i>=dim)
            throw invalid_argument("index too large");
        return coefficients[i];
    }

    // from C++23: double operator[](size_t i, size_t j)

    //  double& at(size_t i) {                                  // (D)
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

void assign_values() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    polynom p{1.0,2.0,3.0,4.0};
    cout << "01|    p=" << p << endl;

    cout << "-----" << endl;

    cout << "02|    p(1)=" << p(1.0) << endl;               // (F)
    cout << "03|    p(2)=" << p(2.0) << endl;

    cout << "-----" << endl;

    polynom q1{4.0,5.0,6.0}, q2{1.0,2.0,3.0}, q3;
    cout << "04|    q1=" << q1 << endl;
    cout << "05|    q2=" << q2 << endl;

    q3 = q1;                                             // (G)
    cout << "06|    q3=" << q3 << endl;

    //cout << "07|    q3[1,2] " << q3[1,2] << endl;           // (H)
}
