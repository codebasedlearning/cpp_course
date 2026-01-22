// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * This file demonstrates a basic smart pointer implementation with ownership transfer semantics.
 *  – smart_ptr: Custom template class managing dynamic memory via raw pointer.
 *  – Ownership transfer: Copy constructor transfers ownership.
 *  – Copy-and-swap idiom: Assignment operator uses pass-by-value and swap for exception safety.
 *  – Problems shown: Transfer on copy can leave objects in invalid state (nullptr).
 *  – Motivation: Demonstrates need for move semantics and unique_ptr in modern C++.
 *  – STL issues: Shows how ownership transfer breaks with containers (vector, sort).
 */

#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>
#include <vector>
#include <ranges>

using std::cout, std::endl, std::ostream;
using std::string, std::string_view;
using std::vector;

void create_and_copy();
void use_with_vector();
void use_with_sort();
void motivation_a_dangerous_copy();

int main() {
    cout << endl << "--- " << __FILE__ << " ---" << endl << endl;

    create_and_copy();
    use_with_vector();
    use_with_sort();
    motivation_a_dangerous_copy();

    return EXIT_SUCCESS;
}

template <typename T>
struct smart_ptr {
    static int cnt;                         // global instance cnt

    mutable T *p;                           // raw ptr, we need to modify even if const...

    smart_ptr() : p{nullptr} {
        ++cnt;
        cout << " a| --> ctor " << *this << endl;
    }

    explicit smart_ptr(T* val) : p{val} {
        ++cnt;
        cout << " b| --> ctor " << *this << endl;
    }

    // Transfer of ownership - first attempt!
    smart_ptr(const smart_ptr& arg) : p{arg.p} {
        ++cnt;
        cout << " c| --> copy " << *this << endl;
        arg.p = nullptr;                    // works because of 'mutable'
    }

    ~smart_ptr() {
        --cnt;
        cout << " d| --> dtor " << *this << endl;
        delete p;
        p = nullptr;
    }

    /* What can be improved here?

    smart_ptr& operator=(const smart_ptr &other) {
        if (this != &other) {
            delete p;
            p = other.p;
            other.p = nullptr;
        }
        return *this;
    }
    */

    // Also transfers.
    smart_ptr& operator=(smart_ptr other) noexcept {    // Note: pass by value
        std::swap(p,other.p);
        cout << " e| --> op= " << *this << endl;
        return *this;
    }

    T operator*() const { return *p; }

    T& operator*() { return *p; }

    friend ostream& operator<<(ostream& os, const smart_ptr &arg) {
        os << "(" << &arg << " ->" << static_cast<void*>(arg.p);
        if (arg.p != nullptr) os << " *" << *arg.p;
        return os << ")";
    }
};

template <typename T>
int smart_ptr<T>::cnt = 0;                  // static counter per class!

template <typename T>
smart_ptr<T> make_smart_ptr(const T& t) { return smart_ptr{new T(t)}; }

void create_and_copy() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    {
        smart_ptr<int> p;
        cout << " 1| p=" << p << endl;

        smart_ptr<int> q{new int{23}};
        cout << " 2| q=" << q << endl;

        smart_ptr<int> r{make_smart_ptr(42)};
        cout << " 3| r=" << r << endl;

        *r = 12;
        cout << " 4| r=" << r << endl;

        p = q;
        cout << " 5| p=" << p << endl
             << "  | q=" << q << endl;
    }
    assert(smart_ptr<int>::cnt == 0);
}

void use_with_vector() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    {
        vector<smart_ptr<int>> v;

        auto p{make_smart_ptr(99)};
        v.push_back(p);                     // transfers

        cout << " 1| p=" << p << endl;

        auto &q = v[0];
        cout << " 2| q=" << q << endl;      // ok, no transfer

        auto r = v[0];
        cout << " 3| r=" << r << endl       // also ok, but transfers
             << "  | q=v[0]=" << q << endl; // ok

        /*
         * Ownership is transferred back, leaving a deleted item in vector.
         * This is, at least, error-prone and a little confusing.
         */
    }
    assert(smart_ptr<int>::cnt == 0);
}

void use_with_sort() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    {
        vector<smart_ptr<int>> v;
        v.reserve(2);

        v.push_back(make_smart_ptr(42));
        v.push_back(make_smart_ptr(23));
        cout << " 1| v.size()=" << v.size() << endl;

        auto &p = v[0];                     // observe
        auto &q = v[1];
        cout << " 2| p=" << p << ", q=" << q << endl;

        std::ranges::sort(v, [](const auto& lhs, const auto& rhs)->bool { return *lhs < *rhs; });
        cout << " 3| p=" << p << ", q=" << q << endl;

        std::ranges::sort(v, [](const auto lhs, const auto rhs)->bool { return *lhs < *rhs; });
        cout << " 4| p=" << p << ", q=" << q << endl;
    }
    assert(smart_ptr<int>::cnt == 0);

    /*
     * Whether the vector is valid or not after sort depends on the signature
     * of comparator/lambda. Moreover, in many cases standard STL containers
     * work with smart_ptr without a visible crash, but sometimes not.
     * In general, we need another concept of ownership and copy-behavior
     *      -> move semantic and unique_ptr!
     * This topic is far more complex than presented here.
     *      https://stackoverflow.com/questions/3106110/what-is-move-semantics
     */
}

void motivation_a_dangerous_copy() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    {
        smart_ptr<int> p;
        smart_ptr<int> q{new int{23}};

        p = q;                                  // ownership transfer, q is still there
        cout << " 1| p=" << p << endl
             << "  | q=" << q << endl;

        smart_ptr<int> r{make_smart_ptr(42)};   // also ownership transfer, no problem here
        cout << " 2| r=" << r << endl;
    }
    assert(smart_ptr<int>::cnt == 0);

    /*
     * In the first case we have a variable (q) which still exists and might be used later.
     * This is an example of a so-called lvalue (locator value or, historically, left value
     * from 'a = b').
     * In short, q has an address in memory, a location.
     *
     * In contrast, the instance created in the second case is temporary. It is gone at the
     * end of the expression (slightly simplified). That means there is no danger in using
     * them later. These are examples of rvalues (historically, right value).
     *
     * From https://stackoverflow.com/questions/3106110/what-is-move-semantics
     *      We now understand that moving from lvalues is potentially dangerous, but moving
     *      from rvalues is harmless. If C++ had language support to distinguish lvalue arguments
     *      from rvalue arguments, we could either completely forbid moving from lvalues, or at
     *      least make moving from lvalues explicit at call site, so that we no longer move by accident.
     *      From C++11 on the language has this support.
     */
}
