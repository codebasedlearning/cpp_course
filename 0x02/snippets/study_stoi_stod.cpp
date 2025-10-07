// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * This snippet demonstrates type conversion with stoi and stod:
 *   – String to integer conversion with error handling
 *   – String to double conversion with error handling
 *   – Exception handling for invalid input and range errors.
 */

#include <iostream>
#include <string>
#include <cstdlib>

using std::cout, std::endl, std::cin;
using std::string;

int main() {
    cout << "\n--- " << __FILE__ << " ---" << endl;

    string s;
    
    cout << " 1| Enter number (int): "; cin >> s;

    try {
        int n = std::stoi(s);               // Or stoi(s, pos) to detect partial parses.
        cout << " 2|   n=" << n << endl;
//        double d = std::stod(s);
//        cout << " 2|   d=" << d << endl;
    } catch (const std::invalid_argument& e) {
        cout << " 3| invalid_argument, e=" << e.what() << endl;
    } catch (const std::out_of_range& e) {
        cout << " 4| out_of_range, e=" << e.what() << endl;
    } catch(...) {
        cout << " 5| unknown error" << endl;
    }
      
    return EXIT_SUCCESS;
}
