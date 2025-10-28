// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * Example of stream insertion operator (operator<<) overloading for complex and number classes.
 * Demonstrates both member function friend declaration and standalone function approaches.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>

using std::cout, std::endl, std::ostream;
using std::string, std::string_view;

void print_complex();
void print_number();

int main() {
    cout << "\n--- " << __FILE__ << " ---" << endl;

    print_complex();
    print_number();

    return EXIT_SUCCESS;
}

class complex {
    double re_;
    double im_;

public:
    complex() : re_{0}, im_{0} { }
    explicit complex(const double re, const double im = 0.0) : re_{re}, im_{im} { }

    [[nodiscard]] double re() const { return re_; }
    [[nodiscard]] double im() const { return im_; }
};

/*
 * An overload of the stream insertion operator (operator<<) for a complex, also called
 * 'shift operator'. It builds a textual representation of the instance.
 *
 * Returning the ostream enables chaining (is discussed again with operators).
 */
ostream& operator<<(ostream &os, const complex &c) {
    os << "(" << c.re() << "," << c.im() << ")";
    return os;
    // or shorter: return os << "(" << c.re() << "," << c.im() << ")";
}

void print_complex() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    const complex c{1,2};
    cout << " 1| c=" << c << endl;
}

class number {
    int n;

public:
    explicit number(const int n) : n{n} { }

    /*
     * Declares a friend function to overload the stream insertion operator (<<). Being
     * a friend (not a member) allows the function to access private members while maintaining
     * the expected left-to-right operator syntax: os << num
     * Note: often it is about declaring the function inside the class, not about accessing
     * the internals.
     */
    friend ostream &operator<<(ostream &os, const number &num) {
        return os << "(" << num.n << ")";
    }
};

void print_number() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    const number n{23};
    cout << " 1| n=" << n << endl;
}
