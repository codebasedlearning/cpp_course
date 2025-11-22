// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * The code demonstrates the use of the address-of operator & and std::addressof.
 *
 * So, basically you cannot trust the '&' operator, but there are very few use cases
 * where it is necessary to redefine the '&' operator.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>

using std::cout, std::endl;
using std::string, std::string_view;

void surprise_surprise();

int main() {
    cout << endl << "--- " << __FILE__ << " ---" << endl << endl;

    surprise_surprise();

    return EXIT_SUCCESS;
}

class number {
    int n;
public:
    explicit number(const int num) : n{num} {}

    [[nodiscard]] int value() const { return n; }

    /*
     *
     * didactical gap
     *
     */

    number* operator&() const { return nullptr; }
};

/*
 *
 * didactical gap
 *
 */

void surprise_surprise() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    number n{23};
    cout << " 1| n=" << n.value() << endl;

    number *pn{&n};
    cout << " 2| n=" << pn->value() << " " << endl;

    /*
     *
     * didactical gap
     *
     */

    auto p = std::addressof(n);
    cout << " 3| n=" << p->value() << " " << endl;
}
