// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * This code demonstrates how virtual function tables (vtables) work in C++.vIt shows:
 *  – How to access the vtable pointer of an object
 *  – The structure of vtables containing function pointers
 *  – How to manually invoke a virtual function through the vtable (demo!)
 *  – The memory layout of objects with virtual functions
 * 
 * Note: This is implementation-specific and relies on compiler-specific details.
 * The code accesses internal compiler structures which may vary across different
 * compilers and platforms.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>
#include <memory>
#include <format>

using std::cout, std::endl;
using std::string, std::string_view;
using std::format;
using std::unique_ptr, std::make_unique;

void call_from_vtable();

int main() {
    cout << endl << "--- " << __FILE__ << " ---" << endl << endl;

    call_from_vtable();

    return EXIT_SUCCESS;
}

class base {
public:
    int n{};
    virtual string to_string() const { return format("base ({})",static_cast<const void*>(this)); }
};

class number : public base {
public:
    string to_string() const override { return format("number ({})",static_cast<const void*>(this)); }
};

/*
 * This may work or not... if not, try a different index.
 */

void call_from_vtable() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    number n;

    cout << " 1| number: &n=" << &n << ", &n.n=" << &n.n << endl;

    /*
     * vtable: array of ptrs, got from &n at offset 0
     */
    void **vptr = *reinterpret_cast<void***>(&n);

    cout << " 2| vtable at " << vptr << endl;
    for (int i=0; i<3; ++i)
        cout << "  | - [" << i << "]: " << vptr[i] << endl;

    /*
     * On many Itanium-ABI compilers:
     *      vptr[0] = &typeinfo
     *      vptr[1] = &base::~base (or delete variant)
     *      vptr[2] = &base::to_string
     *      vptr[3] = &base::more_functions...
     * But this is ABI-specific and can differ!
     *
     * Here, on my computer (Apple M3, ARM), the vtable ptr has an offset and
     * actually points to vptr[2], hence call vptr[0].
     */

    // function pointer type to 'to_string' with invisible 'this' ptr as first arg
    using Fn = string(*)(base*);

    // "slot" for to_string()
    auto to_string = reinterpret_cast<Fn>(vptr[0]);

    cout << " 3| call to_string: '" << to_string(&n) << "'" << endl;;
}
