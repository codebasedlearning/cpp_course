// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * Include the iostream library which provides input/output stream functionality,
 * enabling objects like cout for console output and endl for line breaks (with flush).
 */
#include <iostream>

/*
 * When using objects from the std namespace like cout, you need to either use the full
 * namespace path (std::cout) or import them with 'using'. This allows omitting the 'std::'
 * prefix for the specified items.
 */
using std::cout;
using std::endl;

/*
 * Use of multiple declarators in a single using declaration is possible and a C++17 extension.
 *      using std::cout, std::endl;
 * A global 'using' directive for the std namespace is also possible. While convenient, it should
 * be avoided as it pollutes the global namespace and increases the chance of name collisions.
 *      using namespace std;
 */

/*
 * The 'main' function serves as the program's entry point and returns an error code.
 * A return value of 0 or EXIT_SUCCESS indicates successful execution, while non-zero
 * values indicate errors. The error code can be evaluated in command line operations,
 * such as 'make && a.out'. The function signature follows the same structure as in Java.
 *
 * Btw. EXIT_SUCCESS is a macro, not in the namespace std and defined in cstdlib.
 */
#include <cstdlib>

int main()
{
    /*
     * Using cout for console output, we connect the output items with '<<' operators
     * and use endl for line breaks. Since we have imported these objects with
     * 'using std::cout' and 'using std::endl', we don't need to prefix them with
     * 'std::' namespace.
     *
     * Note: Using "\n" is more efficient than endl for simple line breaks since endl
     * also flushes the output buffer. However, we often prefer endl at the end of
     * significant output blocks or program termination to ensure output is flushed.
     */
    cout << "Hello course! Explained!" << endl;
       
    return EXIT_SUCCESS;
}
