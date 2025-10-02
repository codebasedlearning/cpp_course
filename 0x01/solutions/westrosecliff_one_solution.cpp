// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

#include <iostream>
#include <cstdlib>
using std::cout, std::endl, std::cin;

int main() {
    cout << "\n--- " << __FILE__ << " ---\n" << endl;

    // read int
    int n;
    cout << "Enter a number (int): ";
    cin >> n;

    // read char
    char c;
    cout << "and a character (char): ";
    cin >> c;

    // test n>0
    bool is_n_greater_than_0 = n > 0;

    // and if uppercase
    bool is_c_a_uppercase_letter = c >= 'A' && c <= 'Z';

    // use if
    if (is_n_greater_than_0) {
        cout << "-> n>0" << endl;
    } else {
        cout << "-> n<=0" << endl;
    }

    // use ?:
    cout << "-> '" << c << "' uppercase? " << (is_c_a_uppercase_letter ? "yes" : "no ") << endl;

    return EXIT_SUCCESS;
}
