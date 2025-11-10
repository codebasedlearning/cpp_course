// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * Copper View solution.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>

using std::cout, std::endl, std::ostream;
using std::string, std::string_view;

int main() {
    cout << "\n--- " << __FILE__ << " ---" << endl;

    int n{15};
    float f{2.7};

    int *pn{&n};
    float *pf{&f};

    cout << " 1| pn=" << pn << ", *pn=" << *pn << ", n=" << n << endl;
    cout << " 2| pf=" << pf << ", *pf=" << *pf << ", f=" << f << endl;

    *pn += 1;
    *pf *= 2.0;

    cout << " 3| pn=" << pn << ", *pn=" << *pn << ", n=" << n << endl;
    cout << " 4| pf=" << pf << ", *pf=" << *pf << ", f=" << f << endl;

    int **ppn{&pn};
    cout << " 5| ppn=" << ppn << ", *ppn=" << *ppn << ", **ppn=" << **ppn << endl;

    return EXIT_SUCCESS;
}
