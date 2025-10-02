// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * This snippet discusses string handling in C++:
 *   – String initialization and operations
 *   – String concatenation
 *   – String member functions.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>

using std::cout, std::endl, std::cin;
using std::string, std::string_view;

// Introduce string.
void using_strings() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    /*
     * In C++ strings are objects. This means we are already seeing a first use of objects here, 
     * which is syntactically very similar to working with objects in Java or C#, but shows 
     * significant differences upon closer inspection.
     */
    string s1;                              // Initialization of an empty string.
    cout << " 1| s1='" << s1 << "'" << endl;

    /*
     * Please look again. The object s1 exists from this point on and is initialized by the
     * default constructor. It is neither
     *      string s1 = new string();
     * nor
     *      string s1();
     * Unfortunately,
     *      string s();
     * is a valid syntax, but for something completely different. Another reason for inventing
     * 'uniform initialization' with {}.
     */

    string s2{"Hallo"};                     // Initialization of a string with content "Hallo".
    cout << " 2| s2='" << s2 << "'" << endl;

    string s3{"Kurs"};
    cout << " 3| s3='" << s3 << "'" << endl;

    cout << " 4| s2+' '+s3='" << s2+" "+s3  // String objects can be concatenated with the + operator.
        << "'" << endl;

    /*
     * For string objects, member functions can be called in a 'classical' way.
     * More functions of the string class can be found in the online references.
     */
    cout << " 5| s3.size()=" << s3.size()
        << ", s3.empty()=" << s3.empty()
        << ", s3.substr(1,2)='" << s3.substr(1,2) << "'" << endl;
}

int main()
{
    cout << "\n--- " << __FILE__ << " ---" << endl;

    using_strings();

    return EXIT_SUCCESS;
}
