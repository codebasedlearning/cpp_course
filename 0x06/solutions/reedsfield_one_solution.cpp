// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * Reeds Field solution.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>

using std::cout, std::endl, std::ostream;
using std::string, std::string_view;

int main() {
    cout << "\n--- " << __FILE__ << " ---" << endl;

    const char *str{"hallo"};

    // new pointer
    const char *ptr{str};

    /*
     * See also:
     *    - https://www.learncpp.com/cpp-tutorial/void-pointers/
     *    - https://google.github.io/styleguide/cppguide.html#Casting
     */
    cout << " 1| traverse:" << endl;
    do {
        cout << " a| -> "
             << "ptr: " << static_cast<const void*>(ptr)
             << ", char: '" << *ptr << "'"
             << ", ASCII: " << static_cast<int>(*ptr) << "]" << endl;
    } while (*(ptr++) != '\0');

    return EXIT_SUCCESS;
}
