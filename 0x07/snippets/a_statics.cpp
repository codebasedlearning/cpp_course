// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * This file demonstrates:
 *  – Static variables/functions at file scope (visibility limited to file).
 *  – Static members in classes (shared across all instances).
 *  – Static local variables (retain value between function calls).
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>
#include <memory>

using std::cout, std::endl;
using std::string, std::string_view;
using std::unique_ptr, std::make_unique;

void count_instances();
void count_calls();

int main() {
    cout << endl << "--- " << __FILE__ << " ---" << endl << endl;

    count_instances();
    count_calls();

    return EXIT_SUCCESS;
}

/*
 * A global variable or function marked static is only visible inside that file.
 * Modern C++ often prefers anonymous namespaces instead.
 */
static int secret{42};

/*
 * Anonymous namespace (or 'unnamed namespace').
 * Contents are only visible within this .cpp file (similar to 'static'.
 * Works also for types and functions.
 */
namespace {
    constexpr int magicNr{23};
}

struct number {
    int n;

    explicit number(const int num) : n{num} {
        ++count_;
        cout << " a| -> ctor(), n=" << n << "(" << count_ << ")" << endl;
    }

    number(const number &num) : n{num.n} {
        ++count_;
        cout << " b| -> ctor(&), n=" << n << "(" << count_ << ")" << endl;
    }

    ~number() {
        --count_;
        cout << " c| -> dtor(), n=" << n << "(" << count_ << ")" << endl;
    }

    /*
     * A static member belongs to the class, not to an object.
     *  - Only one shared instance for all objects.
     *  - Does not require an object to access.
     *  - Must be defined outside the class too (except if it’s inline or constexpr).
     *  - Shared by all instances.
     *  - No hidden 'this' pointer.
     */
private:
    static int count_;

public:
    static int count() { return count_; }
};

// defined outside the class
int number::count_{0};

void count_instances() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    number a0{magicNr};
    cout << " 1| instances: " << number::count() << endl;
    {
        const number a1{99};
        const number a2{a1};
        cout << " 2| instances: " << number::count() << endl;

        auto p{make_unique<number>(secret)};
        cout << " 3| instances: " << number::count() << endl;
    }
    cout << " 4| instances: " << number::count() << endl;
}

void call_me();

void count_calls() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    call_me();
    call_me();
    call_me();
}

void call_me() {
    /*
    * A local static variable is created once, lives for the entire program, and retains
    * its state between function calls. It behaves like a global variable that only the
    * function can see.
    * It is initialized exactly once on first execution (not every call) and Thread-safe
    * initialization since C++11.
    */
    static int calls{0};

    ++calls;
    cout << " 1| calls: " << calls << endl;
}
