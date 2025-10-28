// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * Study of generics:
 *  – Template with multiple parameters
 *  – Template specialization
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>

using std::cout, std::endl, std::ostream;
using std::string, std::string_view;

void printing_sums();
void printing_bit_size();

int main() {
    cout << "\n--- " << __FILE__ << " ---" << endl;

    printing_sums();
    printing_bit_size();

    return EXIT_SUCCESS;
}

/*
 * Multiple template parameters, what return type does sum have?
 * Here we use the compiler and auto, so that the type is automatically determined from the
 * expression t+s.
 */
template<typename T, typename S>
auto sum(T t, S s) { return t+s; }

void printing_sums() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    int n{1}, m{2};
    cout << " 1| sum(n,m)=" << sum(n,m) << endl;

    double d{2.5};
    cout << " 2| sum(n,d)=" << sum(n,d) << endl;
}

/*
 * This function calcs the size of the data type in bits.
 */
template<typename T>
size_t size_in_bits() { return 8*sizeof(T); }

/*
 * And here is a specialization for bool, so if T=bool, take this one.
 */
template<>
size_t size_in_bits<bool>() { return 1; }

void printing_bit_size() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    cout << " 1| size_in_bits(n)=" << size_in_bits<int>() << endl;
    cout << " 2| size_in_bits<long>()=" << size_in_bits<long>() << endl;
    cout << " 3| size_in_bits(b)=" << size_in_bits<bool>() << endl;
}
