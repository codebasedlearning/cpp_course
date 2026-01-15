// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * This file demonstrates function pointers and std::function.
 *  – Function pointers: Store addresses of functions for callbacks and higher-order functions.
 *  – std::function: Type-erased wrapper that can store any callable (functions, lambdas, functors).
 *  – Examples include applying functions to values and numerical integration using the trapezoidal rule.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>
#include <functional>
#include <array>
#include <cmath>

using std::cout, std::endl, std::ostream;
using std::string, std::string_view;
using std::array;

void using_function_pointers();
void using_functions();

int main() {
    cout << endl << "--- " << __FILE__ << " ---" << endl << endl;

    using_function_pointers();
    using_functions();

    return EXIT_SUCCESS;
}

/*
 * This is a function pointer type, named 'function_t'. Variables of this type can be pointers
 * to functions (as in vtbl, for instance). They essentially contain the address of the function's
 * start in memory.
 * With this datatype we can now define functions which get a function pointer, e.g. for evaluation.
 *
 * Note, there is no explicit data type for lambda expressions, but a lambda expression can easily
 * be converted to a function pointer or into the data type "function_t".
 */

// typedef double (*function_t)(double x);
using function_t = double (*)(double);

double apply(function_t f, double x) { return f(x); }

double x2(double x) { return x*x; }
double x3(double x) { return x*x*x; }

void using_function_pointers() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    double x{2.0};
    cout << " 1| x=" << x << endl;
    cout << " 2| apply(x^2,x)=" << apply(x2, x) << endl
         << "  | apply(x^3,x)=" << apply(x3, x) << endl
         << "  | apply(sqrt,x)=" << apply(sqrt,x) << endl
         << "  | apply(2x+3,x)=" << apply([](double x) { return 2*x+3; },x)
         << endl;

    /*
     * We define the trapezoidal rule as a lambda expression with fixed a and b.
     *      https://en.wikipedia.org/wiki/Trapezoidal_rule
     */
    double a{1.0}, b{2.0};
    auto trapez = [=](function_t f) { return (b-a)/2.0*(f(b)+f(a)); };

    cout << " 3| integral(x^2)_[a,b]=" << trapez(x2) << endl
         << "  | integral(x^3)_[a,b]=" << trapez(x3) << endl;
}

/*
 * Since the evaluation of a function is a common pattern, there are predefined templates
 * in <functional>, e.g. 'function' <return type(params)>
 *
 * But there is more:
 *  – Function Pointer: Can only store regular functions or lambdas with no captures [].
 *    It cannot store a lambda that needs to remember local variables.
 *  – std::function: Can store anything that can be called with (), e.g. regular functions,
 *    lambdas with captures [=] or [&], functors (classes with operator()),
 *    Member function pointers (via std::bind).
 *    Because std::function is a heavy-weight class object (unlike a raw function pointer),
 *    passing it by value involves a copy, which can be expensive.
 */

double distance(const std::function<double(double,double)>& d, double x, double y) {
    return d(x,y);
}

void using_functions() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    double x{1.5}, y{2.0};
    cout << " 1| x=" << x << ", y=" << y << endl;
    cout << " 2| distance(|.|,x,y)=" << distance([](double x, double y) { return abs(x-y); }, x, y) << endl;
}
