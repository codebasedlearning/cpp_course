// (C) 2025 A.Voß, a.voss@fh-aachen.de, cpp@codebasedlearning.dev

/*
 * Kreley solution.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>
#include <functional>
#include <iomanip>

using std::cout, std::endl, std::ostream;
using std::string, std::string_view;
using std::function;


using funktion_t = double (*)(int x, int y);
// typedef double (*funktion_t)(int x, int y);

double Q(int x, int y) { return 1.0 * x / y; }

int main() {
    cout << endl << "--- " << __FILE__ << " ---" << endl << endl;

    funktion_t Q_ptr{Q};
    cout << " 1| Q_ptr(1,2)=" << Q_ptr(1, 2) << endl;

    function<double(int, int)> Q_fcn{Q};
    cout << " 2| Q_fcn(1,2)=" << Q_fcn(1, 2) << std::endl;

    return EXIT_SUCCESS;
}
