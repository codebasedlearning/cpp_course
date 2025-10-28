// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * This snippet demonstrates
 *   – explicit constructors to prevent implicit type conversions
 *   – const member functions for immutable operations
 *   – references and memory locations of objects.
 *
 * We want to discuss the questions that arose from the first snippet
 * and answer some of them.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>

using std::cout, std::endl, std::cin;
using std::string, std::string_view;

class number {
public:
    int n;

    // Only one ctor with one argument.
    number(const int n) : n{n} {
        cout << " a|   ctor(), n=" << n << endl;
    }

    ~number() {
        cout << " b|   dtor(), n=" << n << endl;
    }

    void print() {
        cout << " c|   n=" << n << endl;
    }
};

void create_numbers() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    cout << " 1| before creating numbers" << endl;

    // number m; // There is no automatically generated default ctor when one is given.

    number num{23};
    cout << " 2| after initializing num: n=" << num.n << endl;

    num = 100;                              // What happens here?
    cout << " 3| after setting num: n=" << num.n << endl;
}

void print_number() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    cout << " 1| before creating num" << endl;
    number num{42};

    cout << " 2| before printing num" << endl;
    num.print();

    cout << " 3| before referencing num" << endl;
    const number &magic = num;

    cout << " 4| before printing magic - oops" << endl;
    // magic.print(); // Error?
}

class tower {
public:
    int floors;

    // 'explicit' added. So no implicit conversion anymore.
    explicit tower(const int floors) : floors{floors} {
        cout << " a|   ctor(), floors=" << floors << " (in memory at " << this << ")" << endl;
    }

    // Copy assignment operator added. More on that in the coming snippets.
    tower& operator=(const tower &other) {
        floors = other.floors;
        cout << " b|   op=(tower&), floors=" << floors << endl;
        return *this;
    }

    ~tower() {
        cout << " c|   dtor(), floors=" << floors << endl;
    }

    // 'const' added. So 'print' is usable for const objects.
    void print() const {
        cout << " d|   floors=" << floors << endl;
    }
};

void create_and_print_towers() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    cout << " 1| before creating towers" << endl;

    tower eiffel{3};
    cout << " 2| after initializing Eiffel: floors=" << eiffel.floors << endl;

    // eiffel = 4; // Now this is an error.
    eiffel = tower{4};
    cout << " 3| after assigning Eiffel: floors=" << eiffel.floors << endl;

    cout << " 4| before referencing Eiffel" << endl;
    const tower &magic = eiffel;

    cout << " 5| before printing magic" << endl;
    magic.print();
}

void understand_locals() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    int n{12};
    cout << " 1| n=" << n << ", &n=" << &n << endl;

    int m{23};                              // If the stack grows upwards, the address is below of n.
    cout << " 2| m=" << m << ", &m=" << &m << endl;

    tower eiffel{3};                        // Same here, below m.
    cout << " 3| floors=" << eiffel.floors << ", &eiffel=" << &eiffel << ", sizeof(eiffel)=" << sizeof(eiffel) << endl;

    int k{99};                              // eiffel, and only the int, exists between n and k.
    cout << " 4| k=" << k << ", &k=" << &k << endl;

    eiffel = tower{4};                      // No 'new' instance (or 'reference'), just a new int value on stack.
    cout << " 5| floors=" << eiffel.floors << ", &eiffel=" << &eiffel << endl;

    const tower &magic = eiffel;            // No instance is created, compare the addresses.
    cout << " 6| floors=" << magic.floors << ", &magic=" << &magic << ", sizeof(magic)=" << sizeof(magic) << endl;
}

int main() {
    cout << "\n--- " << __FILE__ << " ---" << endl;

    create_numbers();
    print_number();
    create_and_print_towers();
    understand_locals();

    return EXIT_SUCCESS;
}
