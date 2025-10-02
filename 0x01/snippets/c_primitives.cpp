// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * This snippet discusses the different primitive data types in C++, focusing on:
 *   – Integer types (int, unsigned, long, size_t)
 *   – Character type (char)
 *   – Boolean type (bool)
 *   – Floating point types (float, double)
 *   – Memory size of each type using sizeof.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>

using std::cout, std::endl, std::cin;
using std::string, std::string_view;

// Introduce int, long, long int, signed, unsigned, size_t.
void using_integers() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    /*
     * sizeof gives the size of the type in bytes, that is the memory consumption.
     * C++ standard only guarantees: sizeof(char) == 1 byte; sizeof(short) ≤ sizeof(int) ≤ sizeof(long).
     * Commonly: 32-bit int on most modern platforms, but it can be 16 or 64 bits on some others.
     */
    int n{12};
    cout << " 1| n=" << n << ", sizeof=" << sizeof(n) << " or sizeof=" << sizeof(int) << endl;

    /*
     * Note that looking at raw memory (binary data) does not reveal the variable type.
     * The same bit pattern can be interpreted differently based on the declared type.
     *
     * 'unsigned' and 'signed' implicitly define the valid value range.
     */
    unsigned int i{1};
    signed int j{-1};
    cout << " 2| i=" << i << ", sizeof=" << sizeof(i) << endl;
    cout << " 3| j=" << j << ", sizeof=" << sizeof(j) << endl;

    long l{123456789012345};                // Commonly: 64-bit.
    cout << " 4| l=" << l << ", sizeof=" << sizeof(l) << endl;

    size_t z = sizeof(int);                 // Unsigned integer type used to represent sizes and array indexes.
    cout << " 5| z=" << z << ", sizeof=" << sizeof(z) << endl;
}

// Introduce char.
void using_chars() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    char c{'A'};                            // A single (ASCII) character.
    cout << " 1| c='" << c << "', sizeof=" << sizeof(c) << endl;
}

// Introduce bool.
void using_bools() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    bool b{true};                           // Boolean values true or false.
    cout << " 1| b=" << b << ", sizeof=" << sizeof(b) << endl;
}

// Introduce float, double.
void using_floats() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    float f{1.2f};                          // Floating point number of single precision.
    cout << " 1| f=" << f << ", sizeof=" << sizeof(f) << endl;

    double d{2.4};                          // Not guaranteed by C++, but usually double is IEEE 754 binary64.
    cout << " 2| d=" << d << ", sizeof=" << sizeof(d) << endl;
}

int main() {
    cout << "\n--- " << __FILE__ << " ---" << endl;

    using_integers();
    using_chars();
    using_bools();
    using_floats();

    return EXIT_SUCCESS;
}
