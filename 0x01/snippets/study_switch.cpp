// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * This code demonstrates the usage of switch statements:
 *  - switch with integral arguments (int, char)
 *  - case labels for different values
 *  - break statements to exit cases
 *  - optional default case
 *  - fall through behavior between cases.
 */

#include <iostream>
#include <cstdlib>

using std::cout, std::endl, std::cin;

int main() {
	cout << "\n--- " << __FILE__ << " ---" << endl;

    int n{4};
	switch(n) {								// The 'switch' statement works with integral arguments.
	case 3:									// Individual cases, here 3 and 4.
        cout << " 1| case 3" << endl;
        break;								// 'break' jumps to the end, but it is optional - see also next 'switch'.
	case 4:
        cout << " 2| case 4" << endl;
		break;
    default:								// When no other case matches, there is the optional 'default' block.
        cout << " 3| default" << endl;
	}

    char c{'A'};							// Type 'char' is also allowed since it is integral.
	switch(c)
	{
	case 'A':								// 'fall through', meaning it also executes the code for 'B'.
        cout << " 4| case 'A'" << endl;		// Sometimes a missing 'break' is a feature, often it's a bug.
	case 'B':
        cout << " 5| case 'B'" << endl;
		break;
    default:
        cout << " 6| default" << endl;
	}
       
    return EXIT_SUCCESS;
}
