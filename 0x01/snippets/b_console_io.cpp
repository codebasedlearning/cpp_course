// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * This snippet discusses
 *   – console output using cout
 *   – input using cin
 *   – runtime assertions.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cassert>                          // assert
#include <cstdlib>

using std::cout, std::endl, std::cin;
using std::string, std::string_view;

// Use the '<<' operator for console output streaming.
void print_to_console() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    int i{23};
    cout << " 1| i=" << i << endl;

    // Output any chain of valid expressions: here 2*i+3 and i*i demonstrate arithmetic operations.
    cout << " 2| 2*i+3=" << 2 * i + 3 << " or i*i=" << i * i << endl;
}

// Use the '>>' operator for console input streaming.
void read_from_console() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    int n;                                  // intentionally uninitialized!

    /*
     * Input data is read into n using the '>>' operator. For numeric input, this reads until
     * a non-numeric character is encountered.
     * 
     * Note: This input method is for demonstration purposes only and lacks robust error handling.
     */
    cout << " 1| Enter a number n: ";
    cin >> n;

    cout << " 2| n=" << n << endl;

    /*
     * 'assert' guarantees (for non-release builds) that the expression is valid at runtime,
     * otherwise the program is aborted. You can use this command for simple testing.
     *
     * Note: the program is aborted – no "Oops exception, no warning, just the end!".
     * And the exit code is non-zero.
     */
    assert(n > 0);
}

int main() {
    cout << "\n--- " << __FILE__ << " ---" << endl;

    print_to_console();
    read_from_console();

    return EXIT_SUCCESS;
}
