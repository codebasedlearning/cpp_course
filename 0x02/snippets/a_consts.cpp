// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * This snippet demonstrates const-related keywords and concepts:
 *   – const for creating immutable variables
 *   – constexpr for compile-time constants
 *   – consteval for compile-time function evaluation.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>

using std::cout, std::endl, std::cin;
using std::string, std::string_view;

int mal3(int n) { return n*3; }

void using_const() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    /*
     * const: object of any type cannot be modified after initialization (through that name,
     * more on this with references). It's value may be known at runtime or compile time.
     */

    int i{1};
    const int j{2};
    const int k = mal3(3);

    cout << " 1| i=" << i << ", j=" << j << ", k=" << k << endl;

    i = 3;
    // j = 4; // not allowed, compiler error
}

constexpr int mal4(int n) { return n*4; }

void using_constexpr() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    /*
     * constexpr: compile-time constant if possible; forces constant evaluation.
     * Initializer for variables must be a constant expression. Functions can be
     * evaluated at compile time when called with constant arguments; otherwise
     * usable at runtime too.
     *
     * The compiler can constant-fold any expression as an optimization, but
     * constexpr guarantees it’s semantically legal to do so.
     * Even if a compiler could inline an expression and compute it at
     * compile time — it’s not required to, and the language must stay portable
     * even for compilers that don’t.
     *
     * const on a function’s return type almost never does what you want.
     * Returning a const value type (e.g. const int) is discarded and doesn’t
     * prevent assignment to the receiving variable.
     * const is appropriate on references/pointers, see later units.
     *
     * constexpr marks the function as eligible for compile-time evaluation
     * when arguments are constant and the body permits it
     */
    constexpr int j{2};
    // constexpr int k = mal3(3);       // compiler error
    constexpr int l = mal4(3);
    // constexpr int l = mal4(mal3(3)); // compiler error

    cout << " 1| j=" << j << ", l=" << l << endl;

    int m;
    cout << " 2| Input number m (int): "; cin >> m;
    cout << " 3| m=" << m << ", mal4(m)=" << mal4(m) << endl;   // called at runtime
}

consteval int ten() { return 10; }
consteval int mal5(int n) { return n*5; }

void using_consteval() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    /*
     * consteval: function must produce a compile-time result every time it’s called.
     * If a call cannot be evaluated at compile time, it’s a compile error.
     */

    int i = ten();
    constexpr int k = mal5(3);
    cout << " 1| i=" << i << ", k=" << k << endl;

    // int m;
    // cout << " 2| Input number m (int): "; cin >> m;
    // cout << " 3| m=" << m << ", mal4(m)=" << mal5(m) << endl;
}

int main() {
    cout << "\n--- " << __FILE__ << " ---" << endl;

    using_const();
    using_constexpr();
    using_consteval();

    return EXIT_SUCCESS;
}
