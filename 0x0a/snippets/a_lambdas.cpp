// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * Lambda expressions: A comprehensive guide covering
 *  – basic syntax,
 *  – captures,
 *  – generic lambdas, and
 *  – usage with objects.
 * Demonstrates how lambdas provide inline anonymous functions that can capture variables
 * from their scope by value or reference.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>
#include <functional>
#include <algorithm>
#include <array>
#include <utility>

using std::cout, std::endl, std::ostream;
using std::string, std::string_view;
using std::array;

void why_lambdas();
void simple_lambdas();
void lambdas_and_objects();
void generic_lambdas();

int main() {
    cout << endl << "--- " << __FILE__ << " ---" << endl << endl;

    why_lambdas();
    simple_lambdas();
    lambdas_and_objects();
    generic_lambdas();

    return EXIT_SUCCESS;
}

// print array
template <typename T, size_t DIM>
ostream& operator<<(ostream& os, const array<T,DIM>& a) {
    os << "[ ";
    for (auto x : a) {
        os << x << " ";
    }
    os << "]";
    return os;
}

bool even_odd(int a, int b) {               // dividing into two groups and sort within each group
    return (a%2==b%2) ? (a<=b) : (a%2==0);
}

void why_lambdas() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    array a = {5, 7, 4, 2, 8, 6, 1, 9, 0, 3};
    cout << " 1| init.   a=" << a << endl;

    std::ranges::sort(a);                   // same as: std::sort(a.begin(), a.end());
    cout << " 2| sort    a=" << a << endl;

    /*
     * What are the pros and cons of each approach?
     */

    std::ranges::sort(a, even_odd);
    cout << " 3| even    a=" << a << endl;

    struct {
        bool operator()(int a, int b) const {
            return (a%2==b%2) ? (a>=b) : (a%2==1);
        }
    } odd_even;
    std::ranges::sort(a, odd_even);
    cout << " 4| odd     a=" << a << endl;

    std::ranges::sort(a, std::greater<>());
    cout << " 5| greater a=" << a << endl;

    std::ranges::sort(a, [](int a, int b) -> bool { return a <= b; });
    cout << " 6| lambda  a=" << a << endl;

    /*
     * This is the shortest version with lambda expressions.
     * Advantage: can be defined directly in place without further structures or functions.
     */
}

void simple_lambdas() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    /*
     * This is a lambda expression. It consists of three parts:
     *  – The [] brackets at the beginning, aka capture – explanation follows.
     *  – The parameters a and b
     *  – The {} statement block itself.
     *  Depending on the syntax (we have two variants), we also need "->" and the return type.
     *  This expression calculates "a<b". The derivation of the return type (bool) can be left
     *  to the compiler with "auto". The syntax "->" follows the mathematical way of writing x->x^2.
     */
    auto less = [](int a, int b) -> bool { return a < b; };

    /*
     * Use a lambda expression like a function.
     */

    cout << " 1| 2<3? " << less(2,3) << endl;
    cout << " 2| 3<2? " << less(3,2) << endl;

    auto plus2 = [](int n) -> int { return n+2; };
    auto plus3 = [](int n) -> auto { return n+3; };         // As before, but result type is determined automatically.
    auto plus4 = [](int n) { return n+4; };                 // Different syntax (without "->"). And the type is derived from the return expression.
    auto const99 = [] { return 99; };                       // '()' omitted

    int k{7};
    cout << " 3| k=" << k
         << ", k+2=" << plus2(k)
         << ", k+3=" << plus3(k)
         << ", k+4=" << plus4(k)
         << ", 99=" << const99() << endl;

    /*
     * The next lambda expression function uses "m" but which "m" is used?
     * The expression "=" in the [] indicates, how and which "external" variables can be seen.
     * Here "=" says that "m" is copied and this copy is known within the expression.
     */

    int m{3};
    auto plusm = [=](int n) { return n+m; };

    cout << " 4| k=" << k << ", m=" << m
         << ", k+m=" << plusm(k) << endl;

    /*
    * Note: "m" is not always the current value, but the copy made at or before the first use!
    * Also, all values are const, unless you spend 'mutable' to remove const-ness.
    */

    m = 100;
    cout << " 5| k=" << k << ", m=" << m
         << ", k+m=" << plusm(k) << endl;

    /*
     * Same as before, but now "m" is a reference.
     */

    m = 3;
    auto plusrefm = [&](int n) { return n+m; };

    cout << " 6| k=" << k << ", m=" << m
         << ", k+m=" << plusrefm(k) << endl;

    m = 100;
    cout << " 7| k=" << k << ", m=" << m
         << ", k+m=" << plusrefm(k) << endl;

    // other types

    string A{"<"}, B{">"};
    auto compose = [&](const string& s) { return A+s+B; };

    cout << " 8| compose:'" << compose("line") << "'" << endl;

    /*
     * Selective: a and b are copies, c is a reference.
     */

    int a=1, b=2, c=3;
    auto plusmixed = [a,b,&c](int n) { return n+a+b+c; };
    a=11; b=22, c=33;
    cout << " 9| k=" << k << ", a=" << a << ", b=" << b << ", c=" << c
         << ", k+a+b+c=" << plusmixed(k) << endl;

    /*
     * Copies (here a) are const, if you want to modify them, you need to declare the lambda as 'mutable'.
     * If you need a const ref (here b), either use 'std::as_const' (utility) or declare it as const (ref) before.
     *      [a,&b=std::as_const(b)](int n)...
     */

    // auto plusmut = [a,&b](int n) { a=111; b=222; return n+a+b; };
    auto plusmut = [a,&b](int n) mutable { a=111; b=222; return n+a+b; };
    cout << "10| k=" << k << ", a=" << a << ", b=" << b
         << ", k+a+b=" << plusmut(k) << endl;
    cout << "11| a=" << a << ", b=" << b << endl;

    /*
     * Lambda with direct call (IIFE - Immediately Invoked Function Expression).
     * example use case: complex initialization of a const variable.
     */

    auto plus7result = [](int n) { return n+7; }(42);
    cout << "12| 42+7=" << plus7result << endl;

    const string status = [] {
        // if (!has_network()) return "No Network";
        // if (!is_logged_in()) return "Not Logged In";
        // if (get_signal_strength() < 80) return "Poor Connection";
        // [...] more logic
        return "Connected";
    }();
    cout << "13| status='" << status << "'" << endl;
}

/*
 * What about 'this' for lambdas in member functions?
 * Capture 'this' has changed over time, see e.g.
 *      https://en.cppreference.com/w/cpp/language/lambda
 *      https://www.nextptr.com/tutorial/ta1430524603/capture-this-in-lambda-expression-timeline-of-change
 */

void lambdas_and_objects() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    struct S {
        int n{-1};

        S() { cout << " a| ctor" << endl;}
        S(const S&) { cout << " b| copy" << endl;}

        // Capture '&' -> everything by reference, even 'this'.
        void f() {
            [&]() -> void { n = 11;}();
            cout << " 1| n=" << n << endl;
        }

        // Capture '*this' -> This is a copy of *this, i.e. a const instance, hence 'mutable'.
        void g() {
            [*this]() mutable -> void { n = 22;}();
            cout << " 2| n=" << n << endl;
        }

        // Capture 'this' without copy -> change ok, if h is not const
        void h() {
            [this]() -> void { n = 33;}();
            cout << " 3| n=" << n << endl;
        }
    };

    S().f();
    S().g();
    S().h();
}

/*
 * Generic lambda. The name of the typeid is not necessarily human-readable,
 * it is the internal name, e.g. for name mangling.
 */

void generic_lambdas() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    auto print_type = []<typename T>(T t) {
        cout << " 1| type name: " << typeid(T).name() << ", t=" << t << endl;
    };

    print_type(1);
    print_type(3.14);
    print_type("Hello, Template Lambda");
}
