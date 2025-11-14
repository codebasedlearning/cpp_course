// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * This snippet demonstrates memory addresses and pointer basics:
 *  – Local variables on stack,
 *  – understanding pointers and memory addresses.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>
#include <iomanip>

using std::cout, std::endl;
using std::hex, std::dec;                   // I/O manipulators
using std::string, std::string_view;

void view_locals_on_stack();
void understanding_pointers();

int main() {
    cout << endl << "--- " << __FILE__ << " ---" << endl << endl;

    view_locals_on_stack();
    understanding_pointers();

    return EXIT_SUCCESS;
}

void view_locals_on_stack() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    cout << " 1| size(int)=" << sizeof(int) << endl;

    /*
     * 'k', 'l', 'm' and 'n' are local variables on the stack. '&' denotes the memory address,
     * often shown in hexadecimal, e.g. '&n' is the address of variable 'n'.
     * These ints are usually located directly next to each other, i.e. at a distance of the
     * size of an int (4 bytes here).
     * Note that the addresses change with each program execution.
     */
    int k{0x22446688};
    int l{0x336699cc};
    int m{0x4488cc00};
    int n;
    // Breakpoint here, view memory "&k"

    cout << " 2| &k=" << &k << ", k=" << k << endl;
    cout << " 3| &l=" << &l << ", l=" << l << endl;
    cout << " 4| &m=" << &m << ", m=" << m << endl;

    // Breakpoint here, enter 'a' in memory in 'n' (0x61), 'Step Over', 'Console' -> n=97
    cout << " 5| &n=" << &n << ", n=" << dec << n << endl;
}

void understanding_pointers() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    /*
     * 'p' is a pointer to int (int*), initialized with 'nullptr'.
     * It is a local variable (so it lives also on the stack), and its value is a memory address.
     *
     * In contrast to references, pointers can be assigned a different _value_, i.e. 'pointing to
     * another location'. Additionally, pointers can change _the memory it points at_. This is what
     * the dereference operator '*' does.
     *
     * To know how many bytes are affected, the pointer needs a type, e.g. 'int*'.
     */
    int n{0x1234};
    int m{0x5678};
    int *p{nullptr};

    // local addresses and current values
    cout << " 1| &n=" << &n << ", &m=" << &m << ", &p=" << &p << endl;
    cout << " 2| n=0x" << hex << n << ", m=0x" << m << ", p=" << p << dec << endl;

    // let 'p point to n' (assign the address of 'n' to 'p'), store a value, view 'n'
    p = &n;
    *p = 0xaabb;
    cout << " 3| n=0x" << hex << n << ", m=0x" << m << ", p=" << p << ", *p=0x" << *p << dec << endl;

    // now let 'p point to m', store a value, view 'm'
    p = &m;
    *p = 0xeeff;
    cout << " 4| n=0x" << hex << n << ", m=0x" << m << ", p=" << p << ", *p=0x" << *p << dec << endl;

    // '&' = 'address of'/'pointer to' => 'int' to 'int*'
    // '*' = 'dereference' => 'int*' to 'int'
    cout << " 5| n=0x" << hex << *(&n) << ", m=0x" << *(&m) << dec << endl;

    // repeat and view 'p' in memory
}
