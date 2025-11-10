// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * This snippet demonstrates three ways to implement a swap function:
 *  – swap1: pass by value, no effect on original variables,
 *  – swap2: pass by reference, swaps original variables,
 *  – swap3: pass by pointer, swaps original variables.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>

using std::cout, std::endl;
using std::string, std::string_view;

void swap_values();

int main() {
    cout << endl << "--- " << __FILE__ << " ---" << endl << endl;

    swap_values();

    return EXIT_SUCCESS;
}

void swap1(int n, int m) {
    int k = n;
    n = m;
    m = k;
}

void swap2(int &n, int &m) {
    int k = n;
    n = m;
    m = k;
}

void swap3(int *n, int *m) {
    int k = *n;
    *n = *m;
    *m = k;
}

void swap_values() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    int n{}, m{};

    n=1; m=-1; swap1(n,m);
    cout << " 1| n=" << n << ", m=" << m << endl;

    n=2; m=-2; swap2(n,m);
    cout << " 2| n=" << n << ", m=" << m << endl;

    n=3; m=-3; swap3(&n,&m);
    cout << " 3| n=" << n << ", m=" << m << endl;
}
