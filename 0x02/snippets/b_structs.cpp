// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * This snippet introduces structures in C++:
 *   – Definition of a fraction structure with numerator and denominator
 *   – Initialization and member access
 *   – Member value modification
 *   – Type casting of fraction to double.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>

using std::cout, std::endl;
using std::string, std::string_view;

struct fraction {                           // A "composite" data type. What does this remind you of?
	int num;
	int denom;
};

void use_struct() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

	/*
	 * A variable of type 'fraction', initialized with n=1, d=2. Note that the variable clearly
	 * exists without needing 'new' or similar.
	 */
	fraction f{1,2};
	// fraction f(1,2);						// no matching ctor
	// fraction f{.denom=3,.num=1};         // valid, but wrong order

	// Accessing members, the elements of the fraction.
	cout << " 1| f.num=" << f.num << ", f.denom=" << f.denom << endl;

	// Changing the components n and d of f.
	f.num = 5;
	f.denom = 8;
	cout << " 2| f.num=" << f.num << ", f.denum=" << f.denom << endl;

	// A change of data type, a cast.
	cout << " 3| f=" <<  (double)f.num/(double)f.denom << endl;
}

int main() {
	cout << "\n--- " << __FILE__ << " ---" << endl;

	use_struct();

    return EXIT_SUCCESS;
}
