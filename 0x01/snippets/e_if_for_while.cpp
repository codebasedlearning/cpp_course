// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * This snippet discusses control flow statements in C++:
 *   – if/else conditional branching
 *   – for loops
 *   – while and do-while loops
 *   – modern if-init syntax.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>

using std::cout, std::endl, std::cin;
using std::string, std::string_view;

void print_tables() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    // 'do'-'while'-loop
    int r;
    do {
        cout << " 1| Input base (in [2..20]): ";
        cin >> r;                           // usually we need more error checks
    } while (r<=1 || r>20);

    // 'if'-clause, 'else' is optional
    int n;
    if (r<10) {
        cout << " 2| the small times tables:" << endl;
        n=10;
    } else {
        cout << " 3| the large times tables:" << endl;
        n=20;
    }

    // classical 'for' with initialization, condition and increment
    for (int i=1; i<=n; ++i) {
        cout << " 4|   " << r << "*" << i << "=" << r*i << endl;
    }

    // or with 'while'
    // int i=1;
    // while (i<=n) {
    //     cout << " 5|   " << r << "*" << i << "=" << r*i << endl;
    //     ++i;
    // }
}

void if_again() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    int n = 23;
    /*
     * init-statement in if: The scope of n2 is the if/else.
     * 
     * Watch out here:
     *    – This
     *          if (int n2=n*n > 12) ...
     *      is different – try it.
     *    – {} are optional, but it is good practice to use them even for one-line statements.
     */
    if (int n2=n*n; n2 > 12) {
        cout << " 1| n^2=" << n2 << endl;
    } else {
        cout << " 2| n^2=" << n2 << endl;
    }

    // cout << " 2| n^2=" << n2 << endl; // error
}

int main() 
{
    cout << endl << "--- " << __FILE__ << " ---" << endl << endl;
    
    print_tables();
    if_again();
    
    return EXIT_SUCCESS;
}
