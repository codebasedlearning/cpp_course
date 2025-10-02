// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * This code demonstrates different integral and floating-point data types:
 *  – short (2 bytes)
 *  – long long (8 bytes)
 *  – fixed width integers like uint16_t, int32_t etc.
 *  – int8_t with special trick for printing
 *  – long double (16 bytes).
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>

using std::cout, std::endl, std::cin;
using std::string, std::string_view;

int main() {
    cout << "\n--- " << __FILE__ << " ---" << endl;

    short sh{1};                            // type 'short', 2 bytes, integer, signed and unsigned.
    cout << " 1| sh=" << sh << ", sizeof(short)=" << sizeof(short) << endl;

    long long ll{2};                        // type 'long long', 8 bytes, integer, signed and unsigned.
    cout << " 2| ll=" << ll << ", sizeof(long long)=" << sizeof(long long) << endl;

    uint16_t u2{4};                         // type 'int8_t', 'uint8_t', 'int16_t', 'uint16_t', up to 64
    int32_t i4{5};                          // signed and unsigned, the number indicates the guaranteed size in bits.
    uint64_t u8{6};
    cout << " 3| u2=" << u2 << ", sizeof(uint16_t)=" << sizeof(uint16_t) << endl;
    cout << " 4| i4=" << i4 << ", sizeof(int32_t)=" << sizeof(int32_t) << endl;
    cout << " 5| u8=" << u8 << ", sizeof(uint64_t)=" << sizeof(uint64_t) << endl;

    /*
     * When printing the int8_t variable 'i1', it would normally be interpreted as a char.
     * Adding the unary plus operator converts it to its numeric value for output.
     */
    int8_t i1{3};
    cout << " 6| i1=" << +i1 << ", sizeof(int8_t)=" << sizeof(int8_t) << endl;

    long double ld{1};                      // type 'long double', floating point number, 16 bytes,
    cout << " 7| ld=" << ld << ", sizeof(long double)=" << sizeof(long double) << endl;
      
    return EXIT_SUCCESS;
}
