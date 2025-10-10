// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * This is a new feature from C++23 - print with string interpolation output. For now,
 * we'll stick with cout until this feature is widely available. If your compiler
 * complains about this, comment out the entire block.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>

using std::cout, std::endl, std::cin;
using std::string, std::string_view;

#if defined(__cpp_lib_print) && __cpp_lib_print >= 202207L

#include <print>
using std::println;

void use_println() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    int n{23};
    println(" 1| here comes the number {}, also squared {}", n, n*n);   // It is not like Python f-String... but they work on it.
}

#else

void use_println() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    cout << " 1| 'println' not available in this C++ version" << endl;
}

#endif

int main() {
    cout << "\n--- " << __FILE__ << " ---" << endl;

    use_println();

    return EXIT_SUCCESS;
}
