// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * This example demonstrates operator overloading in a 'number' class to handle
 * assignment operations, including:
 *  – Assignment from an int or another number object
 *  – Chained assignments (a=b=c).
 *
 * Associativity isn’t a global rule — it’s defined per operator. An operator comes with
 * two key properties:
 *  – Precedence – which operators bind tighter (e.g., * before +).
 *  – Associativity – how operators of the same precedence group.
 *
 * Examples
 *  – op= is right-associative
 *  – operator<< is left-associative (like +):
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>

using std::cout, std::endl, std::ostream;
using std::string, std::string_view;

void surprise_me();
void assign_values();

int main() {
    cout << endl << "--- " << __FILE__ << " ---" << endl << endl;

    surprise_me();
    assign_values();

    return EXIT_SUCCESS;
}

void surprise_me() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    auto n{0};

    n = 1,2,3;
    cout << " 1| n=" << n << endl;

    n = (1,2,3);
    cout << " 2| n=" << n << endl;

    /*
     * 'a, b, c, d' means '((a, b), c), d' (left-associative)
     *    – a, b → evaluates a, discards, returns b
     *    – (result), c → evaluates, discards, returns c
     *    – (result), d → evaluates, discards, returns d
     *
     * And, the assignment operator '=' has higher precedence
     * than the comma operator ','. So
     *      n = 1,2,3;
     * is basically (n=1),2,3
     */
}

struct number {
    int n;

    explicit number(const int num) : n{num} { }

    number& operator=(const int num) {
        n = num;
        cout << " a| -> op=(int), value=" << *this << endl;
        return *this;                       // Give a reference back to this, so that a=b=c works, see below.
    }

    number& operator=(const number &num) {
        n = num.n;
        cout << " b| -> op=(number), value=" << *this << ", from=" << num << endl;
        return *this;
    }

    friend number operator+(const number &lhs, const number &rhs) {
        cout << " c| -> op+(lhs,rhs), lhs=" << lhs.n << ", rhs=" << rhs.n << endl;
        return number{lhs.n + rhs.n};
    }

    friend ostream& operator<<(ostream& os, const number& num) {
        return os << num.n << " (" << &num << ")";
    }
};

void assign_values() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    number n{23};
    // number m = n;                        // Remember: This looks like op=, but is a copy-ctor.
    number m{42};
    cout << " 1| n=" << n << ", m=" << m << endl;

    n = 99;
    n.operator=(98);                        // n = 98;
    cout << " 2| n=" << n << ", m=" << m << endl;

    n = m;
    n.operator=(m);                         // n = m;
    cout << " 3| n=" << n << ", m=" << m << endl;

    // Execution from right to left (right-associative) -> n = (m = 5)
    n = m = 5;
    n.operator=(m.operator=(5));
    cout << " 4| n=" << n << ", m=" << m << endl;

    // Execution from left to right (left-associative)
    number x{1}, y{2}, z{4};
    n = x + y + z;
    n = (x + y) + z;
    operator+(operator+(x,y),z);
    cout << " 5| n=" << n << endl;

    // cout << " 6| " << 999 << endl;
    // operator<<(cout, " 6| ").operator<<(999).operator<<(endl);
}
