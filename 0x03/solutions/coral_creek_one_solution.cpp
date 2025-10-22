// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * Solution for Coral Creek One exercise using an optional integer type 
 * that tracks whether a value has been set and provides safe access to it.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>

using std::cout, std::endl, std::ostream;
using std::string, std::string_view;
using std::runtime_error;

class OptionalInt {
    bool has_value_;
    int value_;

public:
    OptionalInt() : has_value_{false}, value_{0} {
        cout << " a| OptionalInt::ctor()" << endl;
    }

    explicit OptionalInt(const int v) : has_value_{true}, value_{v} {
        cout << " b| OptionalInt::ctor(int), value=" << value_ << endl;
    }

    OptionalInt(const OptionalInt &other)
        : has_value_{other.has_value_}, value_{other.value_} {
        cout << " c| OptionalInt::ctor(&)" << endl;
    }

    ~OptionalInt() {
        cout << " d| OptionalInt::dtor()" << endl;
    }

    [[nodiscard]] bool hasValue() const { return has_value_; }
    explicit operator bool() const { return hasValue(); }

    void setValue(const int v) {
        has_value_ = true;
        value_ = v;
    }

    void clear() { has_value_ = false; }

    [[nodiscard]] int getValue() const {
        if (has_value_) return value_;
        throw runtime_error("no value");
    }

    explicit operator int() const { return getValue(); }

    [[nodiscard]] int getValueOr(const int fallback) const {
        return has_value_ ? value_ : fallback;
    }
};

ostream& operator<<(ostream& os, const OptionalInt& opt) {
    if (opt.hasValue())
        os << opt.getValue();
    else
        os << "(none)";
    return os;
}

int main() {
    cout << "\n--- " << __FILE__ << " ---" << endl;

    OptionalInt n1{};
    OptionalInt n2{23};
    OptionalInt n3{n2};

    cout << " 1| n1=" << n1 << ", n2=" << n2 << ", n3=" << n3 << endl;

    n1.setValue(42);
    n2.clear();
    const auto n3a = static_cast<int>(n3);

    cout << " 2| n1=" << n1 << ", n2=" << n2 << ", n3a=" << n3a << endl;

    const auto n1a = n1.getValueOr(-1);
    const auto n2a = n2.getValueOr(99);
    cout << " 3| n1a=" << n1a << ", n2a=" << n2a << endl;

    return EXIT_SUCCESS;
}
