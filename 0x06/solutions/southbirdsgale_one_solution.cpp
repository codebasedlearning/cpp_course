// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * South Birds Gale solution.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>
#include <cstring>

using std::cout, std::endl, std::ostream;
using std::string, std::string_view;
using std::make_unique, std::unique_ptr;

size_t length(const char *word) {
    auto p{word};
    while (*p != '\0')
        ++p;
    return p - word;
    // return std::strlen(word);
}

char *reverse(const char *str) {
    const size_t len = length(str);
    const auto result = new char[len + 1];

    for (size_t i = 0; i < len; i++)
        result[i] = str[len - 1 - i];

    result[len] = '\0';

    return result;
}

std::unique_ptr<char[]> make_reverse(const char *str) {
    // is this the same?
    // return unique_ptr<char[]>(reverse(str));

    const size_t len = length(str);
    auto result = make_unique<char[]>(len + 1);

    for (size_t i = 0; i < len; i++)
        result[i] = str[len - 1 - i];

    result[len] = '\0';

    return result;
}

/*
 * Where is the move in the return value?
 *    - unique_ptr can’t be copied, only moved.
 *    - In 'return result;' where result is a local unique_ptr,
 *      C++ automatically uses the move constructor (unknown right now).
 *    - You don’t need std::move(result) in the return statement.
 *    - The compiler may even optimize away the move entirely (NRVO).
 *
 * Where is a potential leak?
 *    - If something throws inside `reverse`, e.g. after `new`, the
 *      destructor of the smart pointer can’t run -> leak.
 */

int main() {
    cout << "\n--- " << __FILE__ << " ---" << endl;

    const char *sentence[] = {"This", "is", "a", "sentence"};
    cout << " 1| lengths: [";
    for (auto word : sentence)
        cout << " " << length(word);
    cout << " ]" << endl;

    const auto palindrome = "Sei fein, nie fies";

    // C-style manual memory management
    auto p = reverse(palindrome);
    cout << " 2| reversed: '" << p << "'" << endl;
    delete[] p;                             // comment out for sanitizer leak check

    // Modern C++ with automatic resource management
    auto q = make_reverse(palindrome);
    cout << " 3| reversed: '" << q.get() << "'" << endl;

    return EXIT_SUCCESS;
}
