// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

#include <iostream>
#include <cstdlib>
using std::cout, std::endl, std::cin;

bool isPrim(const int n);

int main() {
    cout << "\n--- " << __FILE__ << " ---\n" << endl;

    int n;
    cout << "Compute primes \nenter number n (int): ";
    cin >> n;

    cout << "-> " << n << " is " << (isPrim(n) ? "" : "not ") << "prime" << endl;

    return EXIT_SUCCESS;
}

bool isPrim(const int n) {
    for (size_t i = 2; i < n; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}
