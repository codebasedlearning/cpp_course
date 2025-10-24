// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * This snippet demonstrates
 *   – class declarations compared to structs
 *   – class constructors and destructors
 *   – access modifiers (public/private)
 *   – member functions and scope resolution.
 *
 *  It provides an initial overview of class definitions and instance creation.
 *  However, there are many more rules to consider when defining classes.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>

using std::cout, std::endl, std::cin;
using std::string, std::string_view;

/*
 * Definition of a class 'complex', compare 'struct'.
 */
class complex {
    /*
     * The attributes of a class are private by default, meaning they are only accessible
     * from within the class itself. The 'public:' keyword makes any member accessible
     * from outside the class.
     */
    double re;
    double im;

public:
    /*
     * Default constructor (ctor) without arguments. A ctor is called after
     * memory for the instance has been allocated (internally) and serves to
     * initialize the object.
     * The initialization list after the colon initializes the attributes.
     * This avoids double initialization.
     */
    complex() : re{0}, im{0} {
        cout << " a|   complex::ctor(), re=" << re << ", im=" << im << endl;
        // or this->re, or (*this).im
    }

    /*
     * Ctor with one argument.
     */
    complex(double re) : re{re}, im{0} {    // const? warning?
        cout << " b|   complex::ctor(re), re=" << re << ", im=" << im << endl;
    }

    /*
     * Ctor with two arguments.
     */
    complex(const double re, const double im) : re{re}, im{im} {
        cout << " c|   complex::ctor(re,im), re=" << re << ", im=" << im << endl;
    }

    /*
     * Destructor (dtor). It is called when the instance leaves its scope.
     * Note: C++ has no garbage collection, instead the destructor is called
     * immediately in any case. One of its main tasks is releasing the object's
     * resources.
     */
    ~complex() {
        cout << " d|   complex::dtor(), re=" << re << ", im=" << im << endl;
    }

    /*
     * A simple member function.
     */
    void print() {                          // const?
        cout << " e|     re=" << re << ", im=" << im << endl;
    }
};                                          // Note the ';' at the end of the class.

void create_complex_numbers() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    cout << " 1| before creating complex numbers c1, c2, c3" << endl;

    /*
     * Here an object instance 'n1' is created and initialized at this point.
     */
    complex c1;
    c1.print();

    // cout << " 2| access internals: c1.re=" << c1.re << endl; // Private, inaccessible.

    complex c2a{2.1};
    c2a.print();

    complex c2b(2.2);                       // In both cases ctor with one arg is called.
    c2b.print();

    complex c3a{3.1, 3.2};
    c3a.print();

    complex c3b(3.3, 3.4);                  // In both cases ctor with two args is called.
    c3b.print();

    {
        cout << " 2| before creating c4" << endl;
        complex c4{4.1, 4.2};
        c4.print();
        cout << " 3| end of block" << endl;
    }

    cout << " 4| end of function; free locals" << endl;
}

void do_nothing() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;
}

int main() {
    cout << "\n--- " << __FILE__ << " ---" << endl;

    create_complex_numbers();
    do_nothing();

    return EXIT_SUCCESS;
}
