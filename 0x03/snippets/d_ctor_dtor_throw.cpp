// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * This code demonstrates:
 *   – Constructors can throw exceptions
 *   – Objects initialized before the exception are properly destructed
 *   – Destructors must never throw exceptions to avoid crash.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>

using std::cout, std::endl, std::cin;
using std::string, std::string_view;
using std::runtime_error;

class street {
public:
    string name;

    explicit street(const string &name) : name{name} {
        cout << " a|   street::ctor(), street=" << name << endl;
    }

    ~street() {
        cout << " b|   street::dtor(), street=" << name << endl;
    }
};

/* Notes on exceptions in constructors and destructors
 *
 * An exception in the constructor results in an incompletely initialized object.
 * Consequently, the destructor won't be called since it assumes the object is
 * in a valid state. However, all member variables that were initialized before the
 * exception will be properly destroyed (including their destructors).
 *
 * An exception in the destructor is often impossible to handle meaningfully.
 * Consider one of the thrown exceptions that causes previously created objects
 * to be destroyed and these then generate another exception during cleanup in
 * their destructors - this cannot work!
 * Therefore, there's only one solution: You must never throw exceptions in a destructor!
 * Otherwise... boom!
 */

class address { 
public:
    street street;                          // this is our object
    string city;

    address(const string &street_name, const string &city_name) : street{street_name}, city{city_name} {
        cout << " c|   address::ctor(), street='" << street.name << "', city='" << city << "'" << endl;
        if (street.name=="Baker Street")
            throw runtime_error("Baker Street not supported");
    }

    ~address()  {
        cout << " d|   address::dtor(), street='" << street.name << "', city='" << city << "'" << endl;
        if (street.name=="Templergraben")
            throw runtime_error("Templergraben not supported");
    }
};

void create_and_throw() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    cout << " 1| standard construction" << endl;
    {
        address a{"Sunset Boulevard", "New York"};
    }

    cout << " 2| construction with exception" << endl;
    try {
        address a{"Baker Street", "London"};
    } catch(runtime_error &e) {             // note that the street attribute is cleaned up
        cout << " e|   exception, e=" << e.what() << endl;
    }

    cout << " 3| destruction with exception" << endl;
    try {
        address a{"Templergraben", "Aachen"};
    } catch(...) {
        cout << " e|   any exception"  << endl;
    }

    cout << " 4| end... never reached" << endl;
}

int main() {
    cout << "\n--- " << __FILE__ << " ---" << endl;

    try {
        create_and_throw();
    } catch(...) {
        cout << " f|   fallback exception... never reached" << endl;
    }

    return EXIT_SUCCESS;
}
