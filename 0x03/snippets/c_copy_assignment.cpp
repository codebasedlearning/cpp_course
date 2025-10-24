// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * This snippet demonstrates copy assignment and object initialization in C++:
 *   – Constructor and copy constructor syntax
 *   – Copy assignment operator implementation
 *   – Default copy constructor vs custom copy constructor
 *   – Deep vs shallow copying of objects.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>

using std::cout, std::endl, std::cin;
using std::string, std::string_view;

class number {
    unsigned int n;
    
public:
    // Default constructor, usage without arguments (also without parentheses).
    number() : n{1} {
        cout << " a|   ctor(), n=" << n << endl;
    }

    // Constructor with 'int' argument.
    number(unsigned int n) : n{n} {
        cout << " b|   ctor(int), n=" << n << endl;
    }

    // Copy constructor (copy-ctor), it initializes the instance based on the argument and often copies the content.
    number(const number &a) : n{a.n+1} {
        cout << " c|   ctor(number&), n=" << n << endl;
    }

    // Copy assignment operator, copy state from existing instance.
    number& operator=(const number &a) {
        n = a.n + 100;
        cout << " d|   op=(number&), from n=" << a.n << ", to n=" << n << endl;
        return *this;
    }

    ~number() {
        cout << " e|   dtor(), n=" << n << endl;
    }
};

// A global variable, note the timing of the calls to constructor and destructor.
number nine{9};

void create_numbers() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    cout << " 1| before creating numbers" << endl;

    number a0;
    number a1(12);
    number a2(a1);
    number a3 = a2;                        // This looks like an assignment, but it's actually the copy constructor.
    number a4{a3};                         // Like before, the copy constructor.

    cout << " 2| before copying" << endl;

    a0 = a4;                                // copy assignment, a4.no = 15
    a1 = 23;                                // What happens here (again)?

    cout << " 3| end of function" << endl;
}

class mobile {
public:
    string number;

    explicit mobile(const string &number) : number{number} {
        cout << " a|     mobile::ctor(number&), number=" << number << endl;
        // why not 'this->number = number' instead of member-initializer list?
    }

    mobile& operator=(const mobile &p) {
        number = p.number;
        cout << " b|     number::op=(number&), number=" << number << endl;
        return *this;
    }

    ~mobile() {
        cout << " c|     mobile::dtor(), number=" << number << endl;
    }
};

class address_card {
public:
    string street;
    unsigned int no;
    mobile home;
    mobile office;
    double secret;

    address_card() : address_card{"No Way", 1,"-","--",0.0} { }

    address_card(
        const string &street,
        const unsigned int no,
        const string &home,
        const string &office,
        const double secret
    ) : street{street}, no{no}, home{home}, office{office}, secret{secret} {
        cout << " d|   address_card::ctor(), street=" << street << ", no=" << no
             << ", home=" << home << ", office=" << office
             << ", secret=" << secret << endl;
    }

    // There is a default copy assignment operator. Does it perform a deep or a shallow copy?
};

void deep_or_shallow() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    cout << " 1| before creating objects" << endl;

    address_card card1{"Seffenter Weg", 23, "+49 123 456789", "+31 241 654321", 123.456};
    address_card card2;

    cout << " 2| before copying" << endl;

    card2 = card1;
    cout << " 3| card2: no=" << card2.no << ", number1=" << card2.home.number << ", number2="
         << card2.office.number << ", secret=" << card2.secret << endl;

    cout << " 4| end of function" << endl;
}

class single_number {
public:
    // Initializes the member before the constructor body runs.
    mobile home{"+49 202 461234"};

    // Creates a default constructor.
    single_number() = default;

    // Member-initializer list directly constructs members and avoids default-construction.
    explicit single_number(const string &number) : home{number} { }
};

void using_defaults() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    cout << " 1| before creating objects" << endl;
    single_number s1;

    single_number s2{"+32 123 456789"};

    cout << " 2| end of function" << endl;
}

int main() {
    cout << "\n--- " << __FILE__ << " ---" << endl;

    create_numbers();
    deep_or_shallow();
    using_defaults();

    cout << "\nend of main" << endl;

    return EXIT_SUCCESS;
}                                           // Destructor of the global variable.
