// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * Study reversed iterations over vector<int> by comparing:
 *  – using rbegin() and rend() with reverse_iterator
 *  – using end() and iterating backwards manually.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>
#include <vector>

using std::cout, std::endl, std::cin, std::ostream;
using std::string, std::string_view;
using std::vector;

void reverse_iteration();

int main() {
    cout << "\n--- " << __FILE__ << " ---" << endl;

    reverse_iteration();

    return EXIT_SUCCESS;
}

void reverse_iteration() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    vector v{2, 3, 5, 7};

    cout << " 1| rev v=[";
    for (vector<int>::reverse_iterator rit = v.rbegin(); rit != v.rend(); ++rit)
        cout << " " << *rit;
    cout << " ]" << endl;

    /*
     * rbegin() returns a reverse_iterator to the first element. Seen from the iterator,
     * it runs forward.
     * Or traverse from the end backwards manually; see below.
     */

    cout << " 2| rev v=[";
    vector<int>::iterator rit = v.end();
    while (rit != v.begin()) {
        --rit;
        cout << " " << *rit;
    }
    cout << " ]" << endl;
}
