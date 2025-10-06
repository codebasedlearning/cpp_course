// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * This snippet demonstrates trailing return type syntax:
     – Traditional vs. trailing return type syntax
     – Implicit return type deduction
     – Using decltype with trailing return
     – Cases where trailing return is necessary.
 */

#include <iostream>
#include <cstdlib>

using std::cout, std::endl;

// Trailing return type, here int (explicitly given).
auto add(int a, int b) -> int { return a+b; }

// Compiler determines return type from the type of the return statement.
auto sub(int a, int b) { return a-b; }

// Here the type is also implicitly determined, but as result of an operation between different types.
auto mul(int a, double b) { return a*b; }

// This is why 'trailing return type' becomes necessary: a and b are first known with the parameters.
auto div(int a, double b) -> decltype(a/b) { return a/b; }
// so this is an error.
// decltype(a/b) div(int a, double b) { return a/b; }

int main() {
    cout << "\n--- " << __FILE__ << " ---" << endl;
    
    cout << " 1| add(2,3)=" << add(2,3) << endl;
    cout << " 2| sub(3,4)=" << sub(3,4) << endl;

    cout << " 3| mul(2,5.1)=" << mul(2,5.1) << endl;
    cout << " 4| div(4,8.0)=" << div(4,8.0) << endl;
      
    return EXIT_SUCCESS;
}
