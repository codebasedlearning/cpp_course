// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * This snippet demonstrates unique pointers in C++:
 *  – Memory leaks with raw pointers
 *  – Creating and using smart pointers (RAII)
 *  – Unique pointer ownership and transfer
 *  – Different ways to handle unique pointers in functions
 *  – Unique pointer array version.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>
#include <memory>
#include <vector>

using std::cout, std::endl;
using std::string, std::string_view;
using std::runtime_error;
using std::unique_ptr, std::make_unique, std::move;
using std::vector;

void leak_memory();
void creating_smart_pointers();
void using_smart_pointers();
void using_unique_ptrs();
void unique_ptr_array_version();

int main() {
    cout << endl << "--- " << __FILE__ << " ---" << endl << endl;

    leak_memory();
    creating_smart_pointers();
    using_smart_pointers();
    using_unique_ptrs();
    unique_ptr_array_version();

    return EXIT_SUCCESS;
}

struct my_pair {
    int key{};
    int value{};

    my_pair() {
        cout << " a| -> ctor (" << key << "," << value << ")" << endl;
    }

    my_pair(int k, int v) : key{k}, value{v} {
        cout << " b| -> ctor (" << key << "," << value << ")" << endl;
    }

    ~my_pair() {
        cout << " c| -> dtor (" << key << "," << value << ")" << endl;
    }
};

int read_file() { throw runtime_error("file read error"); }

void leak_memory() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    try {
        cout << " 1| start working" << endl;

        auto p = new my_pair{23,42};
        read_file();
        delete p;

        cout << " 2| work done" << endl;
    } catch (...) {
        cout << " 3| catch error" << endl;
    }
}

void creating_smart_pointers() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    try {
        cout << " 1| start working" << endl;

        // two ways of creating a unique_ptr (also see below)
        unique_ptr<my_pair> p{new my_pair{23,42}};  // no deduction guides, so we have to state the type
        auto q = make_unique<my_pair>(69,99);       // standard
        read_file();

        cout << " 2| work done" << endl;
    } catch (...) {
        cout << " 3| catch error" << endl;
    }

    /*
     * This is RAII (Resource Acquisition Is Initialization), a C++ technique where
     * an object takes ownership of a resource when it’s constructed and releases
     * that resource when it’s destroyed.
     * This makes resource management automatic: if an object goes out of scope — whether
     * by normal flow, early return, or exceptions — its destructor reliably cleans up.
     *
     * -> Tie the lifetime of a resource to the lifetime of an object, and you never
     * forget to free memory, close files, unlock mutexes, etc.
     *
     *
     * Why make_unique?
     *
     * Before C++17 this was possible:
     *      consume( unique_ptr<my_pair>(new my_pair{23,42}), read_file() )
     * could be evaluated as
     *  1) call new, but not ctor of unique_ptr
     *  2) call read_file() -> exceptions
     *  3) no owner of raw pointer -> leak
     *
     * C++17 introduced guaranteed sequencing between full expressions of arguments:
     *   – Each function argument is fully evaluated before the next, and there’s no
     *     interleaving.
     *   – But the compiler may pick either order.
     */

}

void using_smart_pointers() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    unique_ptr<my_pair> p = make_unique<my_pair>(23,42);
    unique_ptr<my_pair> q;

    cout << " 1| p:" << p.get() << ", q:" << q.get() << endl;

    /*
     * What would
     *      q = p
     * do?
     * How many copies should be allowed?
     * What does this mean for the idea of 'ownership'?
     */

    // p = q;                               // not allowed

    // Transfer ownership to q.
    q = std::move(p);
    cout << " 2| p:" << p.get() << ", q:" << q.get() << endl;

    // Assign a new value.
    // q.reset(new my_pair{33,44});
    q = make_unique<my_pair>(-1,-2);
    cout << " 3| p:" << p.get() << ", q:" << q.get() << endl;

    // Free memory.
    q.reset();
    cout << " 4| p:" << p.get() << ", q:" << q.get() << endl;

    p = make_unique<my_pair>(100,200);
    cout << " 5| p:" << p.get() << ", q:" << q.get() << endl;

    // Detach pointer
    auto r = p.release();
    cout << " 6| p:" << p.get() << ", q:" << q.get()
         << ", r:(" << r->key << "," << r->value << ")" << endl;
    delete r;
}

// Observe a unique_ptr without changing ownership (read-only borrow, no reset, no move out).
void print_pair_v1(const unique_ptr<my_pair>& p) {
    cout << " d| -> out1 (" << p->key << "," << p->value << ")" << endl;
}

// Borrow a unique_ptr, it *could* modify/reset the pointer (write borrow, change ownership).
void print_pair_v2(unique_ptr<my_pair>& p) {
    cout << " e| -> out2 (" << p->key << "," << p->value << ")" << endl;
}

// Classic borrowed raw pointer: no ownership, just read access.
void print_pair_v3(const my_pair* p) {
    cout << " f| -> out3 (" << p->key << "," << p->value << ")" << endl;
}

// Takes ownership by value. Caller must move(p) and after that p is empty.
// It can or can't modify p (depends on const), but it will delete the managed my_pair.
void print_pair_v4(const unique_ptr<my_pair> p) {
    cout << " g| -> out4 (" << p->key << "," << p->value << ")" << endl;
}

void using_unique_ptrs() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    cout << " 1| ownerships" << endl;

    auto p = make_unique<my_pair>(23,42);

    print_pair_v1(p);
    print_pair_v2(p);
    print_pair_v3(p.get());
    print_pair_v4(std::move(p));

    cout << " 2| print done, p:" << p.get() << endl;

    // vector takes ownership of each unique_ptr by moving them in
    vector<unique_ptr<my_pair>> v;

    auto q = make_unique<my_pair>(69,99);
    v.push_back(std::move(q));              // q becomes nullptr
    v.push_back(make_unique<my_pair>(-1,-2));

    cout << " 3| vector filled, q:" << q.get() << endl;

    // some special cases

    cout << " 4| print vector" << endl;
    for (const auto &r : v)
        cout << " h| -> *r=(" << r->key << "," << r->value << ")" << endl;

    vector w{1,2,3};
    vector w_copy{w};                           // this is ok

    // vector<unique_ptr<my_pair>> v_copy{v};   // this is not

    auto v0 = std::move(v[0]);              // element in v is still there, but empty
    cout << " 5| vector: v[0]: " << v[0].get() << ", v.size: " << v.size() << endl;

    // more smart pointers (shared_ptr, weak_ptr) in coming units
}

void unique_ptr_array_version() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    cout << " 1| create pairs v1" << endl;

    // unique_ptr<my_pair[]> a{ new my_pair[3] };
    auto a = make_unique<my_pair[]>(3);
}

/*
 * We are conceptually doing something like a Rust borrow:
 *  - No ownership transfer
 *  - Caller keeps ownership
 *  - Callee gets access
 *
 * But C++ does not enforce exclusivity, no-aliasing guarantees, or lifetime safety.
 * You can still:
 *  - Create multiple references to the same unique_ptr
 *  - Store references that outlive the owner (UB time bomb)
 *  - Move the unique_ptr while a reference still exists
 *  - Delete it early
 *  - Pass raw pointers everywhere
 *
 * Rust borrow rules (enforced at compile time):
 *  - Either:
 *    * 1 mutable reference
 *    * 0 immutable references
 *  - Or:
 *    * Unlimited immutable references
 *    * 0 mutable references
 *  - No references may outlive the owned value
 *  - No use-after-free
 *  - No data races
 *  - Move rules enforced
 *
 *  C++ references and pointers do none of this.
 */
