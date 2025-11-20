// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * This code demonstrates the behavior of const pointers and const values:
 *  – mutable vs const variables,
 *  – pointer to mutable/const values,
 *  – mutable/const pointers,
 *  – const-casting.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>

using std::cout, std::endl;
using std::string, std::string_view;

void const_of_const();
void const_casting();

int main() {
    cout << endl << "--- " << __FILE__ << " ---" << endl << endl;

    const_of_const();
    const_casting();

    return EXIT_SUCCESS;
}

void const_of_const() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    // What exactly is constant here?

    int n{1};                               // mutable ints (or modifiable)
    ++n;                                    // change value of n -> ok

    int *pn{&n};                            // mutable pointer to mutable int
    ++(*pn);                                // modify value of n -> ok
    pn = nullptr;                           // modify pointer -> ok

    cout << " 1| n=" << n << ", &n=" << &n << ", pn=" << pn << endl;

    const int cn{2};                        // const int (or readonly)
    // ++cn;                                // not allowed

    const int *pcn{&n};                     // mutable pointer to const int
    int const *pcn_{&n};                    // (same type)
    // ++(*pcn);                            // not allowed (even n is mutable)
    pcn = nullptr;                          // modify pointer -> ok

    cout << " 2| n=" << n << ", pcn=" << pn << endl;

    int* const pnc = &n;                    // const pointer to mutable int
    ++(*pnc);                               // modify value of n -> ok
    // pnc = nullptr;                       // not allowed

    const int* const pcnc = &n;             // const pointer to const int
    // ++(*pcnc);                           // not allowed (even n is mutable)
    // pcnc = nullptr;                      // not allowed

    cout << " 3| n=" << n << ", pnc=" << pnc << ", pcnc=" << pcnc << endl;

    /*
     * Remarks
     *    - As for references, initializing a pointer to const with a non-const is no problem,
     *      e.g. pcn above, but initializing a pointer to non-const with a const variable is.
     *    - Read declarations from right to left, where '*' reads 'pointer to'
     *          int *p              => p is a pointer to mutable int
     *          const int *p        => q is a pointer to const int
     *          int* const p        => p is a const pointer to mutable int
     *          const int* const p  => p is a const pointer to const int
     *    - Because you cannot change a reference once set, there are only two cases
     *          int &r          => r is a reference (alias)
     *          const int &r    => r is a reference to const int
     */
}

void const_casting() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    // Compare the actual value of 'n' with the output.

    const int n{15};
    cout << " 1| n=" << n << endl;

    // Note: Undefined Behavior UB !!!

    int *pn = const_cast<int*>(&n);         // or (int*)(&n)

    *pn = 23;                               // Modifying an object that was originally declared const is UB.
    cout << " 2| n=" << n << ", *pn=" << *pn << endl;

    int& rn = const_cast<int&>(n);
    rn = 42;                                // Same here -> UB
    cout << " 3| n=" << n << ", *pn=" << *pn << ", rn=" << rn << endl;

    /*
     * When 'const_cast' is not UB:
     *    - If the object was not originally declared const, but you just temporarily see it as const,
     *      then 'const_cast' back to non-const is fine, and writing is well-defined.
     *    - This is the only case where 'const_cast' is well-defined.
     */

    int m{23};
    const int *pm{&m};
    cout << " 4| m=" << m << ", *pm=" << *pm << endl;

    auto p = const_cast<int*>(pm);
    *p = 99;
    cout << " 5| m=" << m << ", *pm=" << *pm << endl;
}
