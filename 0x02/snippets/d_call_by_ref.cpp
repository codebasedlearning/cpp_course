// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * This snippet demonstrates parameter passing for complex data types:
 *   – Call-by-value vs call-by-reference for struct parameters
 *   – Using const references for read-only access
 *   – Impact on performance and memory usage.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>

using std::cout, std::endl;
using std::string, std::string_view;

// pair serves as an example of a non-trivial data structure where copying costs time and memory.
struct pair { 
    int key;
    int value;
};

void init_val(pair p);
void init_ref(pair &p);
void read_const_ref(const pair &p);

void call_by_value() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    pair p{1,2};

    cout << " 1| val: vorher p.key=" << p.key << ", p.value=" << p.value << endl;
    init_val(p);                                            // (B)
    cout << " 2| val: nachher p.key=" << p.key << ", p.value=" << p.value << endl;
}

void call_by_ref() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    pair p{3,4};

    cout << " 1| ref: vorher p.key=" << p.key << ", p.value=" << p.value << endl;
    init_ref(p);
    cout << " 2| ref: nachher p.key=" << p.key << ", p.value=" << p.value << endl;
}

void call_by_const_ref() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    pair p{5,6};

    cout << " 1| const_ref: vorher p.key=" << p.key << ", p.value=" << p.value << endl;
    read_const_ref(p);
    cout << " 2| const_ref: nachher p.key=" << p.key << ", p.value=" << p.value << endl;
}

int main() {
    cout << "\n--- " << __FILE__ << " ---" << endl;

    call_by_value();
    call_by_ref();
    call_by_const_ref();

    return EXIT_SUCCESS;
}

// In this form it is call-by-value, i.e. the parameter p is copied and the copy is set to 0.
void init_val(pair p) {
    cout << " a|   p.key=" << p.key << ", p.value=" << p.value << endl;
    p.key = p.value = 0;
    cout << " b|   p.key=" << p.key << ", p.value=" << p.value << endl;
}

// In this form it is call-by-ref (&), i.e. p is an alias and no copy is created; important for large objects.
void init_ref(pair &p) {
    cout << " c|   p.key=" << p.key << ", p.value=" << p.value << endl;
    p.key = p.value = 0;
    cout << " d|   p.key=" << p.key << ", p.value=" << p.value << endl;
}

/*
 * This is an example of parameter passing for a complex data structure passed by const reference.
 * With const reference:
 *   – The data is not copied (efficient)
 *   – The data cannot be modified inside the function (safe).
 * 
 * Convention: If a parameter should not be modified, it should be declared as const.
 * Otherwise, if not const, assume the parameter will be modified.
 */
void read_const_ref(const pair &p) {
    cout << " e|   p.key=" << p.key << ", p.value=" << p.value << endl;
}
