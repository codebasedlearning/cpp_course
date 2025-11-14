// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * This file demonstrates concepts of pointers, including local variables on stack
 * and pointer-to-pointer relationships. It contains examples showing memory 
 * addresses, variable sizes, multiple levels of pointer indirection, void pointers
 * and null pointer safety.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>

using std::cout, std::endl;
using std::string, std::string_view;

void understanding_locals();
void pointers_to_pointers();
void multiple_pointers();
void void_pointers();
void null_pointers();

int main() {
    cout << endl << "--- " << __FILE__ << " ---" << endl << endl;

    understanding_locals();
    pointers_to_pointers();
    multiple_pointers();
    void_pointers();
    // null_pointers();

    return EXIT_SUCCESS;
}

void understanding_locals() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    // view locals in 'Memory View'

    int n{15};
    cout << " 1| &n=" << &n << " (" << sizeof(int) << "), n=" << n << endl;

    long l{65};
    cout << " 2| &l=" << &l << " (" << sizeof(long) << "), l=" << l << endl;

    double d{3.14};
    cout << " 3| &d=" << &d << " (" << sizeof(double) << "), d=" << d << endl;

    bool b{true};
    cout << " 4| &b=" << &b << " (" << sizeof(bool) << "), b=" << b << endl;

    float f{2.71};
    cout << " 5| &f=" << &f << " (" << sizeof(float) << "), f=" << f << endl;

    int m{97};
    cout << " 6| &m=" << &m << " (" << sizeof(int) << "), m=" << m << endl;

    int *p{&m};
    cout << " 7| &p=" << &p << " (" << sizeof(int*) << "), p=" << p << ", *p=" << *p << endl;
}

void pointers_to_pointers() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    int n{15};
    cout << " 1|  &n=" << &n << ",  n=" << n << endl;

    // a pointer to an int
    int *p{&n};
    cout << " 2|  &p=" << &p << ",  p=" << p << ",  *p=" << *p << endl;

    // a pointer to a pointer to an int
    int **pp{&p};
    cout << " 3| &pp=" << &pp << ", pp=" << pp << ", *pp=" << *pp << ", **pp=" << **pp << endl;

    auto q = &n;                            // &(int) -> int*
    auto r = &q;                            // &(int*) -> int**
    auto s = &r;                            // &(int**) -> int***

    auto k = *q;                            // *(int*) -> int
    auto l = *r;                            // *(int**) -> int*
    auto ll = **r;                          // **(int**) -> int
    auto m = *s;                            // *(int***) -> int**
    auto mm = **s;                          // **(int***) -> int*
    auto mmm = ***s;                        // ***(int***) -> int
}

void multiple_pointers() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    // What types? (hint: hover)
    int* p, q;

    // To declare two pointers in one line, use this.
    int *r, *s;
}

void void_pointers() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    int n{15};
    cout << " 1| n=" << n << ", &n=" << &n << endl;

    int *p{&n};
    cout << " 2| p=" << p << ", *p=" << *p << endl;

    // This is a pure address, no type associated.
    void *q{p};
    cout << " 3| q=" << q << ", *q=?" << endl;

    // It is unclear how many bytes it should read from memory and how to interpret the data.
    // auto x = *q;
}

void null_pointers() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    int *p{nullptr};

    // Dereferencing a null pointer results in an error.
    int n = *p;
}
