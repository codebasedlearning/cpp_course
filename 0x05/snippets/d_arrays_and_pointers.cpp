// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * This code demonstrates the relationship between arrays and pointers, including
 *  – basic array operations and memory addresses,
 *  – pointer arithmetic and array traversal,
 *  – different data type sizes affecting pointer arithmetic,
 *  – dangerous/illegal pointer operations.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>

using std::cout, std::endl;
using std::string, std::string_view;

void recap_arrays();
void arrays_and_pointers();
void pointer_math();
void illegal_math();

int main() {
    cout << endl << "--- " << __FILE__ << " ---" << endl << endl;

    recap_arrays();
    arrays_and_pointers();
    pointer_math();
    illegal_math();

    return EXIT_SUCCESS;
}

void recap_arrays() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    constexpr int dim{3};
    int a[dim]={1,22,333};

    cout << " 1| a=[" << a[0] << "," << a[1] << "," << a[2] << "]" << endl;
    cout << " 2| &a[0]=" << &a[0] << ", &a[1]=" << &a[1] << ", &a[2]=" << &a[2] << endl;

    cout << " 3| traverse a" << endl;
    for (auto i{0}; i<dim; ++i) {
        int *p = &a[i];
        cout << " a| - p=" << p << ", *p=" << *p << endl;
    }
}

void arrays_and_pointers() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    constexpr int dim{3};

    /*
     * Pointer arithmetic means that integers can be added to pointers, and instead of simply
     * counting up the memory address, the size of the data type is added.
     * Similarly, pointers can be incremented, or the difference of two typed pointers
     * can be formed, which is also calculated in number of elements rather than bytes.
     *
     * Note that any array type is implicitly convertible to a pointer to its first element.
     */

    // int case

    int a[dim]={1,22,333};

    cout << " 1| a=[" << a[0] << "," << a[1] << "," << a[2] << "]" << endl;
    cout << " 2| &a[0]=" << &a[0] << ", &a[1]=" << &a[1] << ", &a[2]=" << &a[2] << endl;

    // Compare the addresses p-1, p+0, p+1, or ++p

    int *p = a;
    cout << " 3| p+0=" << p+0 << ", p+1=" << p+1 << ", p+2=" << p+2 << endl;
    cout << " 4| a=[" << *(p+0) << "," << *(p+1) << "," << *(p+2) << "]" << endl;

    p = a;
    cout << " 5| a=[" << *p;
    ++p;
    cout << "," << *p;
    ++p;
    cout << "," << *p << "]" << endl;

    p = a;
    cout << " 6| a=[" << *(p++);
    for (; p-a < dim; ++p)                  // p-a is also pointer arithmetic
        cout << "," << *p;
    cout << "]" << endl;

    cout << endl;

    // double case

    double d[dim]={1.1,2.2,3.3};

    cout << " 7| d=[" << d[0] << "," << d[1] << "," << d[2] << "]" << endl;
    cout << " 8| &d[0]=" << &d[0] << ", &d[1]=" << &d[1] << ", &d[2]=" << &d[2] << endl;

    double *q = d;
    cout << " 9| q+0=" << q+0 << ", q+1=" << q+1 << ", q+2=" << q+2 << endl;
    cout << "10| d=[" << *(q+0) << "," << *(q+1) << "," << *(q+2) << "]" << endl;

    q = d;
    cout << "11| d=[" << *q;
    ++q;
    cout << "," << *q;
    ++q;
    cout << "," << *q << "]" << endl;

    q = d;
    cout << "12| d=[" << *(q++);
    for (; q-d < dim; ++q)
        cout << "," << *q;
    cout << "]" << endl;
}

void pointer_math() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    // Different types and pointers.

    int n{15};
    int *p{&n};
    cout << " 1| &n=" << &n << ", p-1=" << p-1 << ", p=" << p << ", p+1=" << p+1 << ", p+2=" << p+2 << endl;

    bool b{true};
    bool *q{&b};
    cout << " 2| &b=" << &b << ", q-1=" << q-1 << ", q=" << q << ", q+1=" << q+1 << ", q+2=" << q+2 << endl;

    float f{2.71};
    float *r{&f};
    cout << " 3| &f=" << &f << ", r-1=" << r-1 << ", r=" << r << ", r+1=" << r+1 << ", r+2=" << r+2 << endl;

    // char pointers (C-strings) in combination with operator<< are special.
    // Note that this may not work with a sanitizer.

    char c{'a'};
    char *s{&c};
    cout << " 4| &c=" << &c << ", s-1=" << s-1 << ", s=" << s << ", s+1=" << s+1 << ", s+2=" << s+2 << endl;

    cout << " 5| Lirum larum." << endl;
    cout << " 4| &c=" << static_cast<void*>(&c)
         << ", s-1=" << static_cast<void*>(s-1)
         << ", s=" << static_cast<void*>(s)
         << ", s+1=" << static_cast<void*>(s+1)
         << ", s+2=" << static_cast<void*>(s+2) << endl;
}

void illegal_math() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    int n{15};
    int m{97};
    cout << " 1| n=" << n << ", m=" << m << endl;

    int *p{&n};
    *(p-1) = 123;
    cout << " 2| n=" << n << ", m=" << m << endl;
}
