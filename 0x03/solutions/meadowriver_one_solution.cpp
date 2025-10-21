// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * This solution demonstrates the usage of polynoms which includes:
 *   – Constructor initialization
 *   – Operator overloading
 *   – Evaluation of polynoms
 *   – Addition of polynoms
 *   – Exception handling.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>
#include <stdexcept>

using std::cout, std::endl, std::ostream;
using std::string, std::string_view;
using std::invalid_argument;

constexpr int dim = 4;

class polynom {
public:
    double coeffs[dim];

    [[nodiscard]] double eval(double x) const {
        double res{0.0};
        for (int i = dim - 1; i >= 1; --i) {
            res = x * (coeffs[i] + res);
        }
        res += coeffs[0];
        return res;
    }

    [[nodiscard]] double at(size_t i) const {
        if (i >= dim) {
            throw invalid_argument("invalid index");
        }
        return coeffs[i];
    }
};

ostream &operator<<(ostream &os, const polynom &pol) {
    os << pol.coeffs[0] << "+" << pol.coeffs[1] << "x"
    << "+" << pol.coeffs[2] << "x^2";
    return os;
}

polynom add(const polynom &polynom1, const polynom &polynom2) {
    polynom res{};
    for (size_t i = 0; i < dim; i++) {
        res.coeffs[i] = polynom1.at(i) + polynom2.at(i);
    }
    return res;
}

int main() {
    cout << "\n--- " << __FILE__ << " ---" << endl;

    polynom pol_p{2.0, 3.0, 4.0, 5.0};

    cout << " 1| pol_p: " << pol_p << endl;
    cout << " 2| pol_p.eval(4.0): " << pol_p.eval(4.0) << endl;

    polynom pol_q1{4.0, 5.0, 6.0};
    polynom pol_q2{1.0, 2.0, 3.0};

    cout << " 3| pol_q1: " << pol_q1 << endl;
    cout << " 4| pol_q2: " << pol_q2 << endl;

    polynom pol_q = add(pol_q1, pol_q2);

    cout << " 5| pol_q = pol_q1 + pol_q2: " << pol_q << endl;

    try {
        double coeff_start{pol_p.at(0)};
        cout << " 6| coeff_start: " << coeff_start << endl;
        double coeff_end{pol_p.at(dim)};
        cout << " 7| coeff_end: " << coeff_end << endl;
    } catch (const std::invalid_argument &e) {
        cout << " 8| error: " << e.what() << endl;
    }

    return EXIT_SUCCESS;
}
