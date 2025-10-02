// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * This snippet discusses Variable declaration and initialization methods.
 *
 * Additionally, this snippet also covers the programmer's responsibility for correct behavior
 * and two of C++'s core design principles: you only pay for what you use (zero overhead) and
 * making things const whenever they don’t modify observable state (const correctness).
 */

#include <iostream>                         // cout, cin, and endl
#include <string>                           // string
#include <string_view>                      // string_view
#include <cstdlib>                          // EXIT_SUCCESS

using std::cout, std::endl;
using std::string, std::string_view;

// Compiler instruction: Ignore warning for uninitialized variables (for didactic purposes here).
#pragma GCC diagnostic ignored "-Wuninitialized"

// Introduce uniform initialization in a separate function. More on functions later.
void define_and_init() {
    // Prints the function name and a separator line — ignore string and string_view for a moment.
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    /*
     * Each output starts with a number, so one can associate the respective output with
     * the corresponding code line.
     */

    int v1;                                 // Variable v1 not initialized yet, what does it contain?
    cout << " 1| v1=" << v1 << endl;        // Note the warning (Undef. behavior, UB). Such a declaration is also a definition.

    int v2 = 23;                            // Variable v2 initialized with 23 in old/classic style.
    cout << " 2| v2=" << v2 << endl;

    int v3{42};                             // Variable v3 initialized with 42 in new style (C++11, uniform initialization).
    cout << " 3| v3=" << v3 << endl;        // See also 'Final remarks'.

    int v4{};                               // Variable v4 initialized with default value, that is 0 for integers.
    cout << " 4| v4=" << v4 << endl;
}

// Make things const.
void const_variables() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    /*
     * Placing 'const' before a data type means that the variable cannot be modified thereafter – it
     * becomes constant. All types can be declared as const.
     *
     * The reverse case is equally valid. Everything not marked as const can potentially be modified.
     * We'll revisit this in other units.
     */
    int i{1};
    const int j{2};
    
    cout << " 1| i=" << i << ", j=" << j << endl;

    i = 3;                                  // valid
    // j = 4;                               // compiler error, try it
    cout << " 2| i=" << i << ", j=" << j << endl;
}

int main() {
    // '__FILE__' is a constant (macro) containing the cpp filename, printed at the beginning.
    cout << "\n--- " << __FILE__ << " ---" << endl;

    define_and_init();
    const_variables();

    return EXIT_SUCCESS;
}

/*
 * Final remarks
 *
 * When converting between data types with potential loss of precision (narrowing conversion)
 * classical style initialization gives a warning while uniform initialization gives an error.
 *      int v2 = 123456789012345;
 *      int v3{123456789012345};
 * or
 *      int a = 1.2;
 *      int b{1.2};
 *
 *  const ≠ immutable
 *    – const applies to the object you see, not necessarily the whole reachable state. It is
 *      a compile-time qualifier preventing certain writes through a particular handle.
 *    – Immutability means the entire logical state of the object never changes after construction.
 *      It is a stronger design property about an object’s whole (logical) state over time.
 */
