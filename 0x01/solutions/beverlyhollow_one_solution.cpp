// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

#include <iostream>
#include <cstdlib>
using std::cout, std::endl, std::cin;

int fib_iter(int n);
int fib_rec(int n);

int main() {
    cout << "\n--- " << __FILE__ << " ---\n" << endl;

    int n;
    cout << "Compute Fibonacci \nenter max index n (int): ";
    cin >> n;

    // f_i = f_{i-1} + f_{i-2} mit f_0 = f_1 = 1
    cout << "-> iteratively: f_" << n << " = " << fib_iter(n) << endl;

    cout << "-> recursively: f_" << n << " = " << fib_rec(n) << endl;

    return EXIT_SUCCESS;
}

int fib_iter(int n) {
    if (n <= 1) { return 1; }               // looks like a guard

    int fi{0};                              // for large n use long
    int fi_minus_1{1};
    int fi_minus_2{1};

    while (n > 1) {
        fi = fi_minus_1 + fi_minus_2;
        fi_minus_2 = fi_minus_1;
        fi_minus_1 = fi;
        --n;
    }
    return fi;
}

int fib_rec(int n) {
    return n <= 1 ? 1 : fib_rec(n - 1) + fib_rec(n - 2);
}
