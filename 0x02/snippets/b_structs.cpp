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

void init_structs() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

	/*
     * A variable of type 'fraction', member access as 'usual'.
     * What are the values of f.num and f.denom?
     *
     * Note that the variable exists without needing 'new' or similar!
     */

	fraction f1;
	cout << " 1| f1.num=" << f1.num << ", f1.denom=" << f1.denom << endl;

	fraction f2{1,2};
	cout << " 2| f2.num=" << f2.num << ", f2.denom=" << f2.denom << endl;

	fraction f3(3,4);
	cout << " 3| f3.num=" << f3.num << ", f3.denom=" << f3.denom << endl;

	fraction f4{.denom=6,.num=5};			// valid, but wrong evaluation order (always the declaration order)
	cout << " 4| f4.num=" << f4.num << ", f4.denom=" << f4.denom << endl;

	// fraction f5();						// Where is the problem?
	// cout << " 5| f5.num=" << f5.num << ", f5.denom=" << f5.denom << endl;
}

void using_structs() {
	cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

	fraction f{1,2};
	cout << " 1| f.num=" << f.num << ", f.denom=" << f.denom << endl;

	// Changing the components of f.
	f.num = 5;
	f.denom = 8;
	cout << " 2| f.num=" << f.num << ", f.denum=" << f.denom << endl;

	// A change of data type, a cast.
	// cout << " 3| f=" <<  (double)f.num/(double)f.denom << endl;	// old casts
	cout << " 3| f=" <<  static_cast<double>(f.num)/static_cast<double>(f.denom) << endl;
}

int main() {
	cout << "\n--- " << __FILE__ << " ---" << endl;

	init_structs();
	using_structs();

    return EXIT_SUCCESS;
}
