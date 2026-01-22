// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * This file demonstrates smart pointers with move semantics (rvalue references).
 *  – Move semantics: Transfers ownership without copying, using && syntax for rvalues.
 *  – smart_ptr<T>: Custom smart pointer preventing copies but allowing moves.
 *  – Transfer of ownership: move-ctor and move-assignment op. transfer pointer.
 *  – Copy elision: Compiler optimization avoids move-ctor when returning from function.
 *  – std::move: Explicitly converts lvalue to rvalue to trigger move semantics.
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

void lvalue_and_rvalue();
void create_and_copy();
void use_with_vector();
void use_with_sort();

int main() {
    cout << endl << "--- " << __FILE__ << " ---" << endl << endl;

    lvalue_and_rvalue();
    create_and_copy();
    use_with_vector();
    use_with_sort();

    return EXIT_SUCCESS;
}

string bob() { return "Bob"; }

void f(const string &s)  {
    cout << " a| f(&), s='" << s << "'" << endl;
}

void f(string &&s) {
    cout << " b| f(&&), s='" << s << "'" << endl;
}

/*
 * T& → lvalue reference
 * T&& → rvalue reference
 * const T& → universal read-only view
 * const T&& → rvalues accepted, but moving forbidden... (usually pointless)
 */

void lvalue_and_rvalue() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    string a{"Alice"};                      // 'a' is an lvalue, it has a name and a stable identity (an address) for its lifetime
    f(a);                                   // selects overload 'f(const string&)' (binds to lvalue)
    f(bob());                               // selects overload 'f(string&&)' (binds to rvalue temporary)
}

/*
 * This class is fundamentally structured like before. The difference is that we
 * can now distinguish between lvalues and rvalues.
 */

template <typename T>
struct smart_ptr {
    static int cnt;                         // global instance cnt

    mutable T *p;

    smart_ptr() : p{nullptr} {
        ++cnt;
        cout << " a| --> ctor " << *this << endl;
    }

    explicit smart_ptr(T* val) : p{val} {
        ++cnt;
        cout << " b| --> ctor " << *this << endl;
    }

    // Transfer of ownership by copy is prohibited.
    smart_ptr(const smart_ptr& arg) = delete;

    ~smart_ptr() {
        --cnt;
        cout << " d| --> dtor " << *this << endl;
        delete p;
        p = nullptr;
    }

    // The same is true for assignment.
    smart_ptr& operator=(const smart_ptr &arg) = delete;

    /*
     * New kids in town: move-ctor and move-assignment op.
     */

    smart_ptr(smart_ptr &&arg)  noexcept : p{arg.p} {   // move-ctor
        cout << "cc| --> ctor " << *this << endl;
        ++cnt;
        arg.p = nullptr;
    }

    smart_ptr& operator=(smart_ptr&& arg)  noexcept {   // move-assignment op.
        cout << "ee| --> op= " << *this << endl;
        delete p; p=arg.p; arg.p = nullptr;
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

        smart_ptr<int> r{make_smart_ptr(42)};   // note: no move-ctor because of guaranteed copy elision.
        cout << " 3| r=" << r << endl;

        *r = 12;
        cout << " 4| r=" << r << endl;

        // p = q;                           // error
        p = std::move(q);                   // explicit transfer of ownership
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
        // v.push_back(p);                  // transfers
        v.push_back(std::move(p));          // move-ctor

        cout << " 1| p=" << p << endl;

        auto &q = v[0];
        cout << " 2| q=" << q << endl;      // ok

        auto r = std::move(v[0]);           // explicitly transfers
        cout << " 3| r=" << r << endl
             << "  | q=v[0]=" << q << endl;
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

        // not allowed because of copies
        // std::ranges::sort(v, [](const auto lhs, const auto rhs)->bool { return *lhs < *rhs; });
    }
    assert(smart_ptr<int>::cnt == 0);
}
