// (C) 2025 A.Voß, a.voss@fh-aachen.de, cpp@codebasedlearning.dev

/*
 * Wintervale solution.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>
#include <iomanip>

using std::cout, std::endl, std::ostream;
using std::string, std::string_view;

template <size_t B, size_t N>
struct power {
    static constexpr int res{B * power<B, N - 1>::res};
};

template <size_t B>
struct power<B, 1> {
    static constexpr int res{B};
};

int main() {
    cout << endl << "--- " << __FILE__ << " ---" << endl << endl;

    cout << " 1| 2^12=" << power<2, 12>::res << endl;

    return EXIT_SUCCESS;
}
