// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 *
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>
#include <functional>
#include <utility>

using std::cout, std::endl, std::cin, std::ostream;
using std::string, std::string_view;
using std::function;

class identifier {
    long id_;                               // Note: name with trailing '_' indicating privates.
    // long m_id;                           // Other naming style for members.

public:
    explicit identifier(const long id) : id_{id} { }

    // '[[nodiscard]]' suppress compiler warnings in case the return value is not used.

    // One version of getter and setter
    [[nodiscard]] long get_id() const { return id_; }
    void set_id(const long id) { id_ = id; }

    // another version to access members; any pros/cons?
    [[nodiscard]] long id() const { return id_; }
    long& id() { return id_; }

    // This is an implicit conversion to long and a discussion in itself (operator preview).
    operator long() const { return id_; }
};

void print_identifier(const identifier &object) {
    // Note that 'object' is an alias for local 'ident' and in this context marked as 'const'.
    cout << " a|   object=" << object.id() << endl;

    // ident.id() = 123; // error
}

void create_identifiers() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    identifier ident(1);
    cout << " 1| ident1.id()=" << ident.id()     // Using a simple getter.
         << ", or ident1.get_id()=" << ident.get_id()
         << ", or long(ident)=" << ident << endl;

    ident.set_id(2);                        // Using a simple setter.
    cout << " 2| ident1=" << ident.id() << endl;

    ident.id() = 3;                         // What happens here?
    cout << " 3| ident1=" << ident.id() << endl;

    identifier &pass{ident};                // 'pass' is an alias for 'ident'
    pass.id() = 4;
    cout << " 4| ident1=" << ident.id() << ", pass=" << pass.id() << endl;

    const identifier &copy{ident};          // another alias, now const, here we need the 'const' at id()
    cout << " 5| ident1=" << ident.id() << ", copy=" << copy.id() << endl;

    // copy.id() = 4; // error because of const

    print_identifier(ident);
}

// one not-so-bad-choice (IMHO) of an address class according to many discussion...
class set_card {

    // I do not like this attribute style, but get_xy is worse, so...
    int id_;
    string name_;
    string number_;
    unsigned int age_;

    // Note, this is a private ctor.
    // An explanation of 'move' follows, but in a nutshell (!):
    //    – We have to copy string data, so one way is to copy from a const reference,
    //      the other is using move to reuse resources. More can be read here
    //      https://clang.llvm.org/extra/clang-tidy/checks/modernize-pass-by-value.html
    set_card(int id, string name, string number, unsigned int age)
            : id_{id}, name_{std::move(name)}, number_{std::move(number)}, age_{age} { }

public:
    // Preview: 'static' marks a class function, i.e. there is no 'this' available.
    // This is a factory method, hiding the actual creation process.
    static set_card make(
        const int id,
        string name, string number,
        const unsigned int age)
    {
//        return set_card(id, std::move(name), std::move(number), age);
        return {id, std::move(name), std::move(number), age};
    }

    // '[[nodiscard]]' suppress compiler warnings in case the return value is not used.
    // '[[maybe_unused]]' suppress compiler warnings for not using the functions.

    // Simple getters to access attributes.
    [[nodiscard]] int id() const { return this->id_; }
    [[nodiscard]] string name() const { return name_; }
    [[nodiscard]] string number() const { return number_; }
    [[nodiscard]] unsigned int age() const { return age_; }

    // Instead of providing plain setters, and thus show internal structures/states implicitly,
    // functions with a concrete purpose may be a better choice (even if they simply set some data).
    [[maybe_unused]] void correct_data(const string &new_name, unsigned int new_age) {
        name_ = new_name;
        age_ = new_age;
    }

    [[maybe_unused]] void set_number(const string &new_number) {
        number_ = new_number;
    }
};

// Preview: An overload of the stream insertion operator (operator<<) for set_card,
// also called 'shift operator'. It builds a textual representation of the card.
ostream &operator<<(ostream &os, const set_card &card) {
    os << "{id:" << card.id() << ",name:'" << card.name()
       << ",number:" << card.number() << ",age:" << card.age()
       << "}";
    return os;                              // Enables chaining.
}

void create_set_cards() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    set_card card = set_card::make(1, "Max Mustermann", "0241/12345", 46);
    cout << " 1| card=" << card << "!" << endl;
}

int main() {
    cout << "\n--- " << __FILE__ << " ---" << endl;

    create_identifiers();
    create_set_cards();

    cout << "\nend of main" << endl;

    return EXIT_SUCCESS;
}
