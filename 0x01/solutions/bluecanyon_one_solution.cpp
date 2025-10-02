// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

#include <iostream>
#include <cstdlib>
using std::cout, std::endl, std::cin;

int pot(const int base, int pow);

int main() {
    cout << "\n--- " << __FILE__ << " ---\n" << endl;

    int b, n;                               // for two uninitialized ints a one-liner might be ok

    // enter b and n
    cout << "Compute b^n \nenter base b (int): ";
    cin >> b;

    //
    cout << "and n (int): ";
    cin >> n;

    // calc b^n using for
    int res{1};
    for (int i{0}; i < n; ++i) {
        res *= b;
    }
    cout << "-> using for: " << b << "^" << n << " = " << res << endl;
    cout << "-> using pot: " << b << "^" << n << " = " << pot(b, n) << endl;

    return EXIT_SUCCESS;
}

int pot(const int base, int pow) {
    // calc b^n using while
    int res{base};
    while (pow > 1) {
        res *= base;
        --pow;
    }
    return res;
}
