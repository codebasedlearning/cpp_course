// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * A fraction is a basic aggregate example – a class/struct that allows direct member initialization.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>

using std::cout, std::endl, std::cin;
using std::string, std::string_view;

/*
 * The class 'fraction' below is an aggregate. Special rules exist for its (aggregate) initialization.
 *      fraction f1; (no braces) leaves both doubles uninitialized (indeterminate).
 *      fraction f2{}; value-initializes, i.e. both doubles to 0.
 *      fraction f3{2}; with a single element initializes leads to num=2 and denom value-initialized.
 *
 * A class/struct is an aggregate if it:
 *    – has no user-declared constructors,
 *    – has no private or protected non-static data members,
 *    – has no virtual functions or virtual/base classes,
 *    – has no user-declared or inherited base classes (only public, non-virtual bases are allowed in recent standards),
 *    – has no user-declared destructor (pre-C++17); in C++17+ a non-virtual, defaulted destructor is okay.
 *
 * So: if disqualifying features exist, e.g., private members, it’s not an aggregate.
 * Try to comment-in the private member.
 */
class fraction {
public:
    double num;
    double denom;

// private:
//    int m;
};

void create_fractions() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    cout << " 1| before creating fractions" << endl;

    // Here an object instance 'f1' is created at this point.
    fraction f1;
    cout << " 2| f1: num=" << f1.num << ", denom=" << f1.denom << endl;

    fraction f2{};
    cout << " 3| f2: num=" << f2.num << ", denom=" << f2.denom << endl;

    // fraction f3a(1.2);                   // Tries to call a constructor taking a single double.
    fraction f3{2};                         // Aggregate initialization, see below.
    cout << " 4| f3: num=" << f3.num << ", denom=" << f3.denom << endl;

    fraction f4{3.1,3.2};
    cout << " 4| f4: num=" << f4.num << ", denom=" << f4.denom << endl;
}

int main() {
    cout << "\n--- " << __FILE__ << " ---" << endl;

    create_fractions();

    return EXIT_SUCCESS;
}
