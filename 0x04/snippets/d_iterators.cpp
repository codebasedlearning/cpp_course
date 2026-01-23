// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * This file discusses containers like raw arrays, arrays, vectors, and sets, along with
 * different ways to traverse them using index-based loops, range-based for loops, and iterators.
 * It demonstrates proper usage of const iterators and references when traversing containers.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>
#include <array>
#include <vector>
#include <algorithm>
#include <ranges>
#include <set>

using std::cout, std::endl, std::cin, std::ostream;
using std::string, std::string_view;
using std::vector, std::array, std::set;

void raw_arrays_again();
void traversing_arrays_and_vectors();
void range_based_for_bsc();
void using_range_based_for();
void working_with_iterators();

int main() {
    cout << "\n--- " << __FILE__ << " ---" << endl;

    raw_arrays_again();
    traversing_arrays_and_vectors();
    using_range_based_for();
    range_based_for_bsc();
    working_with_iterators();

    return EXIT_SUCCESS;
}

void print_raw_array(const int r[], const size_t dim) {
    // Note: sizeof(r) gives size of 'const int pointer', not size of array (array-to-pointer decay).
    cout << " a|   r=[";
    for (size_t i = 0; i < dim; ++i)
        cout << " " << r[i];
    cout << " ], dim=" << dim << ", sizeof(r)=" << sizeof(r) << endl;
}

void raw_arrays_again() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    int r[] = {1, 1, 2, 3};                     // raw array, same as int r[4].
    constexpr auto dim = sizeof(r)/sizeof(int); // Works only in the same scope.

    cout << " 1| sizeof(r)=" << sizeof(r) << " -> " << dim << " elements" << endl;
    // traverse traditional style
    cout << " 2| r=[";
    for (size_t i = 0; i < dim; ++i)
        cout << " " << r[i];
    cout << " ], dim=" << dim << endl;

    print_raw_array(r,dim);                     // Providing 'dim' is necessary, see 'print_raw_array'.
}

void traversing_arrays_and_vectors() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    // (fixed-size) array
    array a{1, 1, 2, 3};                    // same as array<int,4>, CTAD = class template argument deduction, C++17/20
    cout << " 1| a=[";
    for (size_t i = 0; i < a.size(); ++i)   // .size available, also .at
        cout << " " << a[i];
    cout << " ], size=" << a.size() << endl;

    /*
     * vector (dynamic array) is, simply put, an array that can grow and shrink dynamically at runtime
     * and where individual elements can be replaced.
     * If you provide a list of elements in the definition, the vector is filled with them;
     * otherwise it's empty.
     */
    vector v{1, 1};                         // same as vector<int>
    v.push_back(2);                         // Adds an element at the end.
    v.push_back(3);                         // 'emplace_back' is discussed later.

    cout << " 2| v=[";
    for (size_t i = 0; i < v.size(); ++i)   // .size available, also .at
        cout << " " << v[i];
    cout << " ], size=" << v.size() << endl;

    /*
     * set is, simply put, a collection of unique elements. If you provide a list of elements
     * in the definition, the set is filled with them; otherwise it's empty.
     *
     * The question is: How to traverse them?
     */
    set s{1, 1, 2, 3};                      // same as set<int>
    cout << " 3| s={ ? }, size=" << s.size() << endl;
}

void using_range_based_for() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    array a{1, 1, 2, 3};
    cout << " 1| a=[";
    for (int n : a)                         // range-based for, element n is a non-const copy, so
        cout << " " << n;                   // n=1 is allowed.
    cout << " ]" << endl;

    vector v{1, 1, 2, 3};
    cout << " 2| v=[";
    for (auto n : v)                        // range-based for, n non-const copy, so
        cout << " " << n;                   // n=1 is allowed.
    cout << " ]" << endl;

    // range-based for also works for sets. Note: s contains elements 1,2,3 as it is a set.
    set s{1, 1, 2, 3};
    cout << " 3| s={";
    for (const auto &n : s)                 // range-based for, n const reference, so
        cout << " " << n;                   // n=1 is not allowed.
    cout << " }" << endl;

    struct data { int x; int y; };

    vector<data> w{ {1,2}, {3,4} };
    cout << " 4| w=[";
    for (auto &d : w)                       // range-based for, d non-const reference, so
        cout << " (" << d.x << "," << (d.y++) << ")";           // y++ is allowed.
    cout << " ]" << endl;

    cout << " 5| w=[";
    for (const auto &d : w)                 // range-based for, d const reference, so
        cout << " (" << d.x << "," << d.y << ")";               // y++ is not allowed.
    cout << " ]" << endl;
}

void range_based_for_bsc() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    /*
     * Behind the range-based for is an implementation using an iterator concept, which is also
     * used in other places. Therefore, it's worth taking a look behind the scenes.
     *
     * 'iterator' is a type defined in the container itself. It can traverse the container and
     * needs to know where to start and when the end is reached. Additionally, access to the
     * current element and incrementation is needed. These operations are shown in the next loop.
     *
     * v.begin() returns an iterator to the first element of v and v.end() to the position
     * one past the last element of v. '*it' dereferences the iterator to access the element.
     * For instance, if 'it' is an iterator to a vector<T>, then '*it' is a reference to an element
     * of type T, i.e. &T. '++it' increments the iterator to point to the next element.
     */

    vector v{2, 3, 5, 7};
    cout << " 1| v=[";
    // basically: for (auto &n : v)
    for (vector<int>::iterator it = v.begin(); it != v.end(); ++it)
        cout << " " << *it;                 // v is not const, so *it=1 is allowed.
    cout << " ]" << endl;

    set s{1, 1, 2, 3};
    cout << " 2| s={";
    // basically: for (auto &n : s)
    for (set<int>::iterator it = s.begin(); it != s.end(); ++it)
        cout << " " << *it;                 // s is not const, but *it=1 is not allowed, why?
    cout << " }" << endl;

    /*
     * cbegin() returns a const_iterator to the first element. Dereferencing (*it) a const_iterator
     * yields const T&, so you can read but not modify elements.
     */

    cout << " 3| v=[";
    // basically: for (const auto &n : v)
    for (vector<int>::const_iterator it = v.cbegin(); it != v.cend(); ++it)
        cout << " " << *it;                 // const_iterator, so *it=1 is not allowed.
    cout << " ]" << endl;

    const auto &w = v;
    cout << " 4| w=[";
    // basically: for (const auto &n : w)
    for (vector<int>::const_iterator it = w.begin(); it != w.end(); ++it)
        cout << " " << *it;                 // For const vars begin and end return const_iterator.
    cout << " ]" << endl;

    /*
     * Until now, there have been several unpleasant points:
     * - the correct combination of iterator and const_iterator with begin/end or cbegin/cend is cumbersome
     * - no .begin/.end for raw arrays
     *
     * Fortunately, there are 'auto', helper functions and, later, the ranges library (from C++20).
     */

    // vector v
    cout << " 5| v=[";
    for (auto it = std::begin(v); it != std::end(v); ++it)
        cout << " " << *it;                         // *it=1 allowed
    cout << " ]" << endl;

    // const vector &
    cout << " 6| w=[";
    for (auto it = std::begin(w); it != std::end(w); ++it)
        cout << " " << *it;                         // *it=1 not allowed
    cout << " ]" << endl;

    // set
    cout << " 7| s={";
    for (auto it = std::begin(s); it != std::end(s); ++it)
        cout << " " << *it;
    cout << " }" << endl;

    // raw array
    int r[] = {2, 3, 5, 7};
    cout << " 8| r=[";
    for (auto it = std::begin(r); it != std::end(r); ++it)  // This works also for raw arrays.
        cout << " " << *it;
    cout << " ]" << endl;

    /*
     * Since C++20 the ranges library exists. It offers some advantages particularly in working
     * with views and pipelines, but it is not yet part of the curriculum.
     */
    cout << " 9| v=[";
    for (auto it = std::ranges::begin(v); it != std::ranges::end(v); ++it)
        cout << " " << *it;
    cout << " ]" << endl;
}

void working_with_iterators() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    vector v{2, 3, 5, 7};

    // version 1
    auto it1 = std::find(v.begin(),v.end(),2);
    auto found1 = it1 != v.end();
    cout << " 1| find-version 1: 2 in v: " << found1 << endl;   // 0=false, 1=true

    // version 2
    auto it2 = std::find(begin(v),end(v),2);
    cout << " 2| find-version 2: 2 in v: " << (it2 != end(v)) << endl;

    // version 3
    auto it3 = std::ranges::find(v,2);
    cout << " 3| find-version 3: 2 in v: " << (it3 != std::ranges::end(v)) << endl;

    // version 4 - special
    set s{1, 1, 2, 3};
    // auto its = std::ranges::find(s,2);   // Why not? (think of complexity)
    auto its = s.find(2);
    cout << " 4| find-version s: 2 in s: " << (its != s.end()) << endl;

    // Iterator arithmetic example: it is ok for so-called random-access iterators
    // to step by k, but only if distance(it, v.end()) >= k (see also  also std::advance)
    cout << " 5| v::2=[";
    for (auto it = begin(v); it != end(v); it+=2) // try with +=3
        cout << " " << *it;
    cout << " ]" << endl;
}
