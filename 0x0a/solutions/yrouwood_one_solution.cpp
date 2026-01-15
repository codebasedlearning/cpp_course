// (C) 2025 A.Voß, a.voss@fh-aachen.de, cpp@codebasedlearning.dev

/*
 * Yrouwood solution.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>
#include <functional>
#include <iomanip>
#include <cmath>

using std::cout, std::endl, std::ostream;
using std::string, std::string_view;
using std::function;

double approx(double x0, const function<double(double)> &f, double eps) {
    double x_old = x0;
    double x_new = f(x_old);
    while (std::abs(x_new - x_old) > eps) {
        x_old = x_new;
        x_new = f(x_old);
    }
    return x_new;
}

int main() {
    cout << endl << "--- " << __FILE__ << " ---" << endl << endl;

    double eps{1e-10};

    double a;
    auto heron = [&a](double x) -> double { return 0.5 * (x + (a / x)); };

    a = 2;
    cout << " 1| sqrt(" << a << ")=" << approx(1, heron, eps) << endl;

    a = 4;
    cout << " 2| sqrt(" << a << ")=" << approx(1, heron, eps) << endl;

    return EXIT_SUCCESS;
}
