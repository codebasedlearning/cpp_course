// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * 'Don't do this, or I'll tell your mum' solution.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>
#include <iomanip>


using std::cout, std::endl, std::ostream;
using std::string, std::string_view;
using std::hex, std::dec;
using std::byte;

int main() {
    cout << "\n--- " << __FILE__ << " ---" << endl;

    int n{0x11223344};
    int m{0x778899aa};
    cout << " 1| n=" << hex << n << ", m=" << m << dec << endl;

    byte* p{reinterpret_cast<byte*>(&n)};   // or byte* p{(byte*)(&n)};
    *(p-3) = static_cast<byte>(255);
    cout << " 2| n=" << hex << n << ", m=" << m << dec << endl;

    return EXIT_SUCCESS;
}
