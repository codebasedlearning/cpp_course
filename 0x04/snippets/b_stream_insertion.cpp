// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * Example of the stream insertion operator (operator<<) overloading for complex and number classes.
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
void more_on_chaining();

int main() {
    cout << "\n--- " << __FILE__ << " ---" << endl;

    print_complex();
    print_number();

    //---

    more_on_chaining();

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
 * Returning the ostream enables chaining (is discussed later with operators).
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
     *
     * Note: often it is about declaring the function inside the class, not about accessing
     * the internals. Sometimes it is called 'the "hidden friend" trick' as is not declared
     * globally, so it doesn’t pollute the global namespace. It’s still found automatically
     * by ADL (Argument-Dependent Lookup), because it’s associated with the class 'number'.
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

/*
 * Associativity isn’t a global rule — it’s defined per operator. An operator comes with
 * two key properties:
 *  – Precedence – which operators bind tighter (e.g., * before +).
 *  – Associativity – how operators of the same precedence group.
 */

void more_on_chaining() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    // chaining, operator<< is left-associative (like +):
    cout << " 1| v=[" << 1 << ",2]" << endl;
    (((cout << " 2| v=[") << 1) << ",2] ") << endl;

    // op= is right-associative
    int a, b, c;
    a = b = c = 42;
    cout << " 3| a=" << a << ", b=" << b << ", c=" << c << endl;

    a = (b = (c = 23));
    cout << " 4| a=" << a << ", b=" << b << ", c=" << c << endl;
}
