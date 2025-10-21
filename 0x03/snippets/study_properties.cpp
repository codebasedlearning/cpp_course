// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * Property wrapper class example, showing type-safe properties with getter and setter,
 * including validation and notification of value changes through callback functions.
 *
 * This is just one (incomplete) example of how you can use a wrapper class to program the
 * usual syntax for setters to a certain extent. This example contains a few features that
 * we haven't covered yet and is just intended as a taster.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>
#include <functional>
#include <utility>

using std::cout, std::endl, std::ostream;
using std::string, std::string_view;
using std::function, std::runtime_error;

template <typename T>
class property {
    T value_{};
    function<void(const T& newVal, const T& oldVal)> on_set_;

public:
    property() = default;

    explicit property(const T &v) : value_{v} {}

    property(const T &v,
             function<void(const T& newVal, const T& oldVal)> onSet
    ) : value_{v}, on_set_{std::move(onSet)} {}

    // Getter with implicit conversion.
    operator const T&() const {
        return value_;
    }

    // Setter.
    property& operator=(const T& v) {
        if (on_set_) on_set_(v, value_);
        value_ = v;
        return *this;
    }
};

// This operator<< makes property 'printable' by delegating to T’s own streaming behavior
// through an explicit conversion.
template <typename T>
ostream& operator<<(ostream& os, const property<T>& p) {
    return os << static_cast<const T&>(p);
}

class address {
public:
    // A simple property without special setter-logic.
    property<string> street;
    // And a property with a range-check, given as lambda.
    property<int> no{
        1,
        [](const int& newV, const int& oldV) {
            if (newV <= 0) throw runtime_error("number must be > 0");
            std::cout << " a|   old:" << oldV << ", new:" << newV << endl;
        }
    };
};

void build_properties() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    address itc;
    itc.street = "Seffenter Weg";
    itc.no = 23;

    cout << " 1| itc: " << itc.street << " " << itc.no << endl;
}

int main() {
    cout << "\n--- " << __FILE__ << " ---" << endl;

    build_properties();

    return EXIT_SUCCESS;
}
