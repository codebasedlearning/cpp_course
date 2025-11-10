// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * This file demonstrates the usage of 'this' pointer in C++ classes. It shows how 
 * 'this' refers to the current instance of a class and can be used to access 
 * member variables using both arrow (->) and dereferencing (*) operators.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>

using std::cout, std::endl;
using std::string, std::string_view;

void understanding_this();

int main() {
    cout << endl << "--- " << __FILE__ << " ---" << endl << endl;

    understanding_this();

    return EXIT_SUCCESS;
}

class One {
    int n=1;

public:
    void print() const {
        // 'this' is the pointer on the instance from type C* – but where does it come from?
        cout << " a| this=" << this << ", n=" << this->n << " or n=" << (*this).n << endl;
    }

    void print(int z) const {
        // Locate 'z' in 'Memory View' (&z) and note the param before.
        cout << " b| this=" << this << ", z=" << z << endl;
    }
};

void understanding_this() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    One n;
    cout << " 1|   &n=" << &n << endl;
    n.print();

    n.print(65);
}
