// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * This snippet explains the [[nodiscard]] attribute.
 */

#include <iostream>
#include <string>
#include <cstdlib>

using std::cout, std::endl;
using std::string;

// If someone calls this function and ignores the return value, maybe your compiler warns,
// maybe it doesn’t. In this case, please warn them, because that’s probably a bug.
[[nodiscard]] int open_file(const string &filename) { return -1; }
void close_file(const int handle) {}

int main() {
    cout << "\n--- " << __FILE__ << " ---" << endl;

    open_file("example.txt");               // A warning, always.

    return EXIT_SUCCESS;
}

/*
 * There are more attributes, e.g.
 *    - [[maybe_unused]]    Suppresses "unused variable/function" warnings.
 *    - [[noreturn]]        Marks a function that never returns.
 *    - [[fallthrough]]     Explicitly marks an intentional switch fallthrough.
 *    - [[deprecated]]      Marks something as deprecated — emits a warning when used.
 *    - [[no_unique_address]] Allows empty member optimization in structs.
 *    - [[assume(expr)]]    Tells the compiler that expr is true.
 */
