// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * This code snippet demonstrates operator overloading in C++ by implementing a class 'int3' 
 * that represents numbers modulo 3 (0,1,2). It showcases various operators like assignment,
 * arithmetic (+, *, +=), and type conversion operators, both as member functions and free 
 * functions. The code follows modern C++ practices with noexcept specifications for 
 * exception safety.
 *
 *
 * Remarks on operators:
 *  – Core idea: For arithmetic-like types, implement the logic once in the compound operators
 *    (+=, -=, *=, etc.) and express the plain operators (+, -, *, …) in terms of those.
 *    Use a single source of truth for the operation for less duplication (DRY).
 *  – If an operation is symmetric, your interface should be too.
 *  – If you define one operator, consider which others logically 'belong with it'.
 *  – If someone reading the code would be surprised by what the operator does,
 *    it’s a bad overload, i.e. only overload operators when the meaning is natural.
 *  – Member vs non-member (rule of thumb):
 *      – Member operators:
 *          operator=, operator[], operator(), operator->, operator* (dereference)
 *          Compound assignment: +=, -=, *=, /=, etc. — because they mutate *this
 *      – Non-member operators (often friends or free functions):
 *          Symmetric binary operators: +, -, *, /, ==, !=, <, >…
 *          This allows implicit conversions on both sides and better symmetry.
 *  – Respect algebraic laws (when applicable).
 *  – Avoid exotic operators like operator,, operator&&, operator||, unless you
 *    really know what you’re doing.
 *
 *
 * Remarks on 'noexcept':
 *  – Mark a function 'noexcept' if and only if you intend to promise that it will never throw.
 *  – Early in a design: be conservative
 *  – Finalized simple type: use noexcept aggressively
 *
 * This is safe:
 *  – no calls to user code
 *  – no allocations
 *  – no container operations
 *  – no undefined behavior on built-ins
 *  – no narrowing conversions
 *  – no hidden branches that could throw exceptions.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>

using std::cout, std::endl, std::ostream, std::istream;
using std::string, std::string_view;

void use_operators();

int main() {
    cout << endl << "--- " << __FILE__ << " ---" << endl << endl;

    use_operators();

    return EXIT_SUCCESS;
}

// class represents a number between 0 and 2, i.e., everything mod 3.
class int3 {
    unsigned int n{0};

public:
    int3() noexcept = default;

    explicit int3(const unsigned int n) noexcept : n{n % 3} {}

    int3(const int3 &n) noexcept = default;

    int3& operator=(const int3 &rhs) noexcept = default;
    int3& operator=(const unsigned int rhs) noexcept { return *this = int3{rhs}; }

    explicit operator unsigned int() const noexcept { return n; }

    int3& operator+=(const unsigned int rhs) noexcept {
        n = (n + rhs) % 3;                  // This is where the operation takes place.
        return *this;
    }

    int3& operator+=(const int3& rhs) {     // DRY
        return *this += rhs.n;
    }

    // as member -> where is the problem?

    int3 operator*(const unsigned int rhs) const {
        return int3{n*rhs};
    }

    int3 operator!() const {
        return int3{3-n};
    }

    // ++p
    int3& operator++() {
        return *this = int3{n+1};
    }

    // p++
    int3 operator++(int) {
        // ++(*this);
        // return *this - 1     // same?

        int3 tmp(*this);
        ++(*this);
        return tmp;
    }
};

// free operators

// long version
// int3 operator+(const int3 &lhs, const int3 &rhs) {
//     int3 res{lhs};
//     return res+=rhs; // res.operator+=(rhs)
// }
int3 operator+(int3 lhs, const int3 &rhs) noexcept {
     return lhs+=rhs;
}

int3 operator+(const int3 &lhs, const unsigned int rhs) noexcept {
    return lhs+int3{rhs};
}

int3 operator+(const unsigned int lhs, const int3 &rhs) noexcept {
    return rhs+lhs;
}

bool operator==(const int3 &lhs, const int3 &rhs) {
    return static_cast<unsigned int>(lhs) == static_cast<unsigned int>(rhs);
}

bool operator!=(const int3 &lhs, const int3 &rhs) {
    return !(lhs==rhs);
}

bool operator<(const int3 &lhs, const int3 &rhs) {
    return static_cast<unsigned int>(lhs) < static_cast<unsigned int>(rhs);
}

bool operator>=(const int3 &lhs, const int3 &rhs) {
    return !(lhs<rhs);
}

// also from C++20: Three-way_comparison: https://en.cppreference.com/w/cpp/language/operator_comparison


ostream& operator<<(ostream& os, const int3& i) {
    os << static_cast<unsigned int>(i);
    return os;
}

istream& operator>>(istream& is, int3& n) {
    //is >> n.vorname;
    //is >> n.nachname;
    unsigned int tmp;
    is >> tmp;
    n = tmp;
    return is;
}

void use_operators() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    int3 n{2}, m{4};
    cout << " 1| n=" << n << ", m=" << m << endl;

    n += 5;
    m += n;
    cout << " 2| n=" << n << ", m=" << m << endl;

    int3 k;
    k = n + m + 1;
    cout << " 3| k=" << k << endl;

    k = 2 + n + m;
    cout << " 4| k=" << k << endl;

    k = n * 5;
    cout << " 5| k=" << k << endl;

    // k = 5 * n; // missing

    // etc.
}
