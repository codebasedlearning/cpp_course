// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * This snippet explains the [[nodiscard]] attribute.
 *
 * Typical use: functions returning error codes, handles, or RAII wrappers, where
 * ignoring the result means a potential resource leak or logic bug.
 */

#include <iostream>
#include <string>
#include <cstdlib>

using std::cout, std::endl;
using std::string;

/*
 * [[nodiscard]] on a function: If someone calls this function and ignores the return value,
 * maybe your compiler warns, maybe it doesn’t. In this case, please warn them, because
 * that’s probably a bug.
 */
[[nodiscard]] int open_file(const string &filename) { return -1; }
int close_file(const int handle) { return -1; }

/*
 * [[nodiscard]] on a type: Whenever a function returns a Resource, it’s probably important.
 * Warn if the caller ignores it.
 */
struct [[nodiscard]] Resource {
    int fd;
};

Resource connect_to(const std::string&) { return {-1}; }

int main() {
    cout << "\n--- " << __FILE__ << " ---" << endl;

    open_file("example.txt");               // Warning: ignoring return value.
    const auto handle = open_file("other.txt");
    close_file(handle);                     // and maybe.

    connect_to("postgres://localhost/db");  // Warning: ignoring nodiscard type.

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
