// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

#include <iostream>
#include <cstdlib>
using std::cout, std::endl, std::cin;

bool isPrim(const unsigned int n);

int main() {
    cout << "\n--- " << __FILE__ << " ---\n" << endl;

    unsigned int n;
    cout << "Compute primes \nenter number n (int): ";
    cin >> n;

    cout << "-> " << n << " is " << (isPrim(n) ? "" : "not ") << "prime" << endl;

    return EXIT_SUCCESS;
}

bool isPrim(const unsigned int n) {
    for (unsigned int i = 2; i < n; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}
