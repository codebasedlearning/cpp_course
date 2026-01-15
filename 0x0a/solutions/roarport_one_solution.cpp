// (C) 2025 A.Voß, a.voss@fh-aachen.de, cpp@codebasedlearning.dev

/*
 * Roarport solution.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>

using std::cout, std::endl, std::ostream;
using std::string, std::string_view;

int main() {
    cout << endl << "--- " << __FILE__ << " ---" << endl << endl;

    auto add = [](double a, double b, double c) -> double { return a + b + c; };
    cout << " 1| add(1.0, 2.0, 3.5)=" << add(1.0, 2.0, 3.5) << endl;

    int a{1}, b{5};
    auto is_within = [a,b](int val) -> bool { return (a <= val && val <= b); };
    cout << " 2| 3 in [" << a << "," << b << "]? " << is_within(3) << endl;
    cout << " 3| 7 in [" << a << "," << b << "]? " << is_within(7) << endl;

    int z{3};
    auto neg_z = [&z]() -> void { z = -z; };

    cout << " 4| z = " << z << endl;
    neg_z();
    cout << " 5| z = " << z << endl;

    return EXIT_SUCCESS;
}
