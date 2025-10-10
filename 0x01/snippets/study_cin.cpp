// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * This snippet discusses console input using cin with examples of:
 *   – Simple input using cin
 *   – Input with error checking using cin flags
 *   – Failed input handling and buffer state.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>

using std::cout, std::endl, std::cin;
using std::string, std::string_view;

void cin_simple() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    int n;
    cout << " 1| Input n: ";
    cin >> n;
    cout << " 2| n=" << n << endl;
}

void cin_with_flags() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    int n;
    cout << " 1| Input n: ";
    if (cin >> n) {
        cout << " 2| n=" << n << ", good:" << cin.good() << ", fail:" << cin.fail() << endl;
    } else {
        cout << " 3| Input failed, good:" << cin.good() << ", fail:" << cin.fail() << endl;
        // successive reads fail as well until cleared
        char c1,c2,c3;
        cin >> c1;
        cin >> c2;
        cin >> c3;
        cout << " 4| c1=" << c1 << ", c2=" << c2 << ", c3=" << c3 << endl;
    }
}

int main() {
    cout << "\n--- " << __FILE__ << " ---" << endl;

    // cin_simple();
    cin_with_flags();

    return EXIT_SUCCESS;
}
