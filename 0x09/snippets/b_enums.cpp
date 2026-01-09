// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * Demonstrates enumeration types:
 *  – Traditional enums with implicit int conversion and global scope.
 *  – Scoped enums (enum class) with type safety and explicit conversions.
 */
#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>

using std::cout, std::endl;
using std::string, std::string_view;

void using_enums();
void use_scoped_enums();

int main() {
    cout << endl << "--- " << __FILE__ << " ---" << endl << endl;

    using_enums();
    use_scoped_enums();

    return EXIT_SUCCESS;
}


/*
 * Enum constants are ints. They are numbered consecutively from 0, unless otherwise
 * specified. If a constant is specified in between, it will be counted from there.
 * Double values are no problem.
 *
 * In general, however, it is unpleasant that these constants (often written in capitals)
 * are available everywhere in the global namespace.
 */

enum COLOR { RED, GREEN, BLUE };
enum SYMBOL { CROSS=1, SPADE, HEART=11, DIAMOND };
enum CARD { NINE=9, ACE=11, JACK=10, QUEEN=10 };

void using_enums() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    cout << " 1| Colors:  { r:" << RED << ", g:" << GREEN << ", b:" << BLUE << " }" << endl;
    cout << " 2| Symbols: { Cross:" << CROSS << ", Spade:" << SPADE << ", Heart:" << HEART << ", Diamond:" << DIAMOND << " }" << endl;
    cout << " 3| Cards:   { 9:" << NINE << ", Ace:" << ACE << ", Jack:" << JACK << ", Queen:" << QUEEN << ", ... }" << endl;

    CARD nine = NINE, donno = (CARD)12;     // The compiler sees the enum type as an int, so all casts are allowed.
    cout << " 4| nine:" << nine << ", ?: " << donno << endl;
}


/*
 * Scoped enumerations; use in principle as above, based on the int type.
 * Usage only with "class"/"scope", syntax comparable to a static element of a class.
 *
 * There is also 'using enum' from C++20, e.g. cppreference.
 */

enum class Color { red, green = 20, blue };

void use_scoped_enums() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    Color x = Color::blue;
    switch (x) {
        case Color::red  : std::cout << " 1| x:red" << endl;   break;
        case Color::green: std::cout << " 2| x:green" << endl; break;
        case Color::blue : std::cout << " 1| x:blue" << endl;  break;
    }

    // int n = x;                           // No implicit conversion. Use static_cast instead.
    int n = static_cast<int>(x);
    cout << " 2| x:" << n << endl;
}
