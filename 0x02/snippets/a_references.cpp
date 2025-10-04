// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * This snippet demonstrates references and parameter passing:
 *   – References as aliases to variables
 *   – Call-by-value vs call-by-reference parameter passing
 *   – Reference behavior with assignments and modifications
 *   – Functions showing parameter passing differences.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>

using std::cout, std::endl, std::cin;
using std::string, std::string_view;

void set_zero_val(int n);                                   // Funktion steht hinter main
void set_zero_ref(int &n);

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

void call_by_value() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    int n{1};
    cout << " 1| val: before n=" << n << endl;
    set_zero_val(n);
    cout << " 2| after n=" << n << endl;
    
    /*
     * set_zero_val sets the parameter to 0. In this form it is call-by-value, i.e. the parameter
     * is copied and the copy is set to 0.
     */
}

void call_by_ref() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    int n{2};
    cout << " 1| ref: before n=" << n << endl;
    set_zero_ref(n);
    cout << " 2| after n=" << n << endl;
    
    /*
     * set_zero_ref also sets the parameter to 0. In this form it is call-by-reference (&),
     * i.e. the calling parameter is set to 0 and no copy is created.
     */
}

int main() {
    cout << "\n--- " << __FILE__ << " ---" << endl;

    using_references();
    call_by_value();
    call_by_ref();

    return EXIT_SUCCESS;
}

void set_zero_val(int n) {
    cout << " a|   n=" << n << endl;
    n = 0;
    cout << " b|   n=" << n << endl;
}

void set_zero_ref(int& n) {
    cout << " c|   n=" << n << endl;
    n = 0;
    cout << " d|   n=" << n << endl;
}
