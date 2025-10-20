// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * This snippet demonstrates
 *   – references as aliases to variables
 *   – the role of const
 *   – reference behavior with assignments and modifications.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>

using std::cout, std::endl;
using std::string, std::string_view;

void using_references() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    int n = 1;

    // m is a reference to n, an alias for n, i.e. m cannot be distinguished from n -> m is n.
    int& m{n};
    cout << " 1| n=" << n << ", m=" << m << endl;           // Reading m returns the value of n.

    n = 2;                                                  // Changing n also results in a new value for m (as m is n).
    cout << " 2| n=" << n << ", m=" << m << endl;

    m = 3;                                                  // Change the value of n through m.
    cout << " 3| n=" << n << ", m=" << m << endl;

    int k{4};
    m = k;                                                  // A reference cannot be reassigned! See n.
    cout << " 4| n=" << n << ", m=" << m << endl;
}

void using_const_references() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    int n = 1;

    // m is still a reference to n, an alias for n, but now, it is considered const!
    const int& m{n};

    // as before
    cout << " 1| n=" << n << ", m=" << m << endl;

    n = 2;
    cout << " 2| n=" << n << ", m=" << m << endl;

    // m = 3;                               // error
    // Cannot modify n using m (!) because m is a const reference even n is not const.
}

void references_syntax() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    int n = 1;
    int& m1{n};                             // suggests a type 'int&'
    int &m2{n};                             // it is more part of the variable
    int & m3{n};                            // hmmm, what?

    n = 23;
    cout << " 1| n=" << n << ", m1=" << m1 << ", m2=" << m2 << ", m3=" << m3 << endl;

    int& k1{n}, k2{n};                      // misleading
    n = 42;
    cout << " 2| n=" << n << ", k1=" << k1 << ", k2=" << k2 << endl;

    /*
     * While the syntax 'int&' suggests a reference type, it's important to note
     * that the '&' is actually part of the variable name, not the type.
    */

    // This is equivalent and emphasizes the idea of reading it from right to left: m is a reference to const int
    int const &m{n};
    cout << " 3| n=" << n << ", m=" << m << endl;
}

int main() {
    cout << "\n--- " << __FILE__ << " ---" << endl;

    using_references();
    using_const_references();
    references_syntax();

    return EXIT_SUCCESS;
}
