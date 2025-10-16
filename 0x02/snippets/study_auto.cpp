// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * This snippet demonstrates the 'auto' keyword:
 *   – Type inference for primitive types and literals
 *   – Using auto with references
 *   – Auto return types from functions.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>

using std::cout, std::endl;
using std::string, std::string_view;

void auto_primitives() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    /*
     * From the literal or result type, the data type can be inferred (derived from the right side,
     * type deduction).
     *
     * But avoid 'auto' for everything, it is an anti-pattern – use it when it improves clarity.
     */

    auto f{1.23f};                          // here 'float'
    auto d{2.34};                           // here 'double'

    auto i{1};                              // here 'int'
    auto l{2l};                             // here 'long'
    auto c{'x'};                            // and 'char'

    // use case, e.g.
    //   for (auto x : v) { ... }

    cout << " 1| f=" << f << ", sizeof(f)=" << sizeof(f) << endl;
    cout << " 2| d=" << d << ", sizeof(d)=" << sizeof(d) << endl;
    cout << " 3| i=" << i << ", sizeof(i)=" << sizeof(i) << endl;
    cout << " 4| l=" << l << ", sizeof(l)=" << sizeof(l) << endl;
    cout << " 5| c='" << c << "', sizeof(c)=" << sizeof(c) << endl;
}

void auto_references() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    auto i = 1;

    // 'auto' with reference. Note: There is no 'reference'-type, this corresponds to an 'int'.
    auto &r{i};
    cout << " 1| r=" << r << ", sizeof(r)=" << sizeof(r) << endl;

    r = 2;
    cout << " 2| i=" << i << endl;
}

string doppelt(const string& s) { return s+s; } 

void auto_returns() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    // type inference also works for return types of a function.
    // Question: Why is the string 24 or 32 bytes in size?
    auto s = doppelt("01234");
    cout << " 1| s='" << s << "', sizeof(s)=" << sizeof(s) << endl;
}

int main() {
    cout << "\n--- " << __FILE__ << " ---" << endl;

    auto_primitives();
    auto_references();
    auto_returns();

    return EXIT_SUCCESS;
}
