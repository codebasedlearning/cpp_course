// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * This code demonstrates how to use std::vector container.
 * It covers initialization, element access, size management,
 * and memory allocation behaviors through examples.
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <sstream>

using std::cout, std::endl;
using std::string, std::string_view, std::ostringstream;
using std::vector;
using std::ranges::find;

void initialize();
void access_elements();
void grow_and_shrink();
void understand_capacity();

int main() {
    cout << "\n--- " << __FILE__ << " ---" << endl;

    initialize();
    access_elements();
    grow_and_shrink();
    understand_capacity();

    return EXIT_SUCCESS;
}

template <typename T>
string join(const T &container) {
    ostringstream os;
    string_view delim;
    for (const auto &x : container) {
        os << delim << x;
        delim = ",";
    }
    return os.str();
}

// understand how to initialize
void initialize() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    vector<int> v0;
    cout << " 1| v0=[" << join(v0) << "]" << endl;

    vector v1 = {1, 2, 3, 4};
    cout << " 2| v1=[" << join(v1) << "]" << endl;

    vector v2(5, 23);                       // 5 copies of 23
    cout << " 3| v2=[" << join(v2) << "]" << endl;

    vector v3(v1.begin()+1, v1.end()-1);    // copy from range - be sure the range is valid
    cout << " 4| v3=[" << join(v3) << "]" << endl;
}

// understand how to access and find elements
void access_elements() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    vector v{95,96,97,98,99};
    cout << " 1| v=[" << join(v) << "]" << endl;

    // Random access, read and write, with (at) or without bound check.
    cout << " 2| v[3]=" << v[3] << ", at(4)=" << v.at(4) << endl;

    cout << " 3| front()=" << v.front() << ", back()=" << v.back() << endl;

    // find
    if (const auto it = find(v,97); it != v.end())
        *it = -1;
    cout << " 4| v=[" << join(v) << "]" << endl;
}

// understand how to add or remove elements
void grow_and_shrink() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    vector v{0,1,2,3,4,5};
    v.push_back(6);                         // append, element is copied
    v.emplace_back(7);                      // constructs in place
    v.insert(v.begin(), -1);                // insert at front (expensive)
    cout << " 1| v=[" << join(v) << "]" << endl;

    v.pop_back();                           // remove last element
    cout << " 2| v=[" << join(v) << "]" << endl;

    v.erase(v.begin());                     // remove first element
    cout << " 3| v=[" << join(v) << "]" << endl;

    // Safe manual erase loop
    for (auto it = v.begin(); it != v.end(); ) {
        if (*it % 2 == 0) {
            it = v.erase(it);               // erase() invalidates 'it', but returns a valid next iterator
        } else {
            ++it;                           // only if not erased
        }
    }

    // later: erase_if(v, [](int x){ return x % 2 == 0; });
    cout << " 4| v=[" << join(v) << "]" << endl;

    v.clear();
    cout << " 5| v=[" << join(v) << "]" << endl;
}

// understand memory management (vector-specific)
void understand_capacity() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    vector v{0,1};                          // same as vector<int>
    cout << " 1| data:" << v.data() << ", used:" << v.size() << "/" << v.capacity() << " v=[" << join(v) << "]" << endl;

    for (int i{2}; i < 10; ++i) {
        v.push_back(i);
        cout << " a| data:" << v.data() << ", used:" << v.size() << "/" << v.capacity() << " v=[" << join(v) << "]" << endl;
    }

    v.reserve(50);                          // reserve space
    cout << " 2| data:" << v.data() << ", used:" << v.size() << "/" << v.capacity() << " v=[" << join(v) << "]" << endl;

    v.resize(30, 99);                       // resize to 30 elements, also without value: resize(30)
    cout << " 2| data:" << v.data() << ", used:" << v.size() << "/" << v.capacity() << " v=[" << join(v) << "]" << endl;

    v.shrink_to_fit();
    cout << " 3| data:" << v.data() << ", used:" << v.size() << "/" << v.capacity() << " v=[" << join(v) << "]" << endl;
}
