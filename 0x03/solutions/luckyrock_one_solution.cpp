// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * Class definition and testing:
 *   – private attributes with public access through getters & setters
 *   – constructor with initializer list
 *   – operator << overloading for formatted output.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>

using std::cout, std::endl, std::cin;
using std::string, std::string_view;

class contakt {
    string name_{};
    unsigned int age_{};

public:
    contakt() = default;
    ~contakt() = default;

    contakt(const std::string &name, unsigned int alter) // (A)
    : name_{name}, age_{alter} {};

    // Implementieren Sie 'getter' und 'setter'.
    std::string name() const { return name_; };
    unsigned int age() const { return age_; };
    void set_name(const std::string &name) { name_ = name; };
    void set_age(unsigned int alter) { age_ = alter; };

    // Erweiterung:
    // Implementieren Sie einen copy-ctor.
    contakt(const contakt &kon) = default;
};

// Implementieren Sie einen operator '<<' zur Ausgabe.
std::ostream &operator<<(std::ostream &os, const contakt &kon) {
    os << "Name: " << kon.name() << " (" << kon.age() << ")";
    return os;
}

int main() {
    cout << "\n--- " << __FILE__ << " ---" << endl;

    // Schreiben Sie aussagekräftigen Testcode.
    contakt contakt1;
    contakt contakt2("contakt2", 2);
    contakt contakt3{contakt2};

    cout << " 1| " << contakt1 << endl;
    cout << " 2| " << contakt2 << endl;
    cout << " 3| " << contakt3 << endl;

    contakt1.set_name("contakt1");
    contakt1.set_age(1);
    contakt3.set_name("contakt3");
    contakt3.set_age(3);

    cout << " 4| " << contakt1 << endl;
    cout << " 5| " << contakt2 << endl;
    cout << " 6| " << contakt3 << endl;

    const contakt &kontaktref{contakt1};
    unsigned int age{kontaktref.age()};
    string name{kontaktref.name()};
    cout << " 7| Name=" << name << ", Age=" << age << endl;

    return EXIT_SUCCESS;
}
