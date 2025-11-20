// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * This snippet introduces working with dynamic memory allocation using new/delete:
 *  – Allocating and freeing single objects and arrays on the heap,
 *  – handling memory allocation exceptions (bad_alloc),
 *  – creating and managing linked list structures,
 *  – proper cleanup to avoid memory leaks.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>

using std::cout, std::endl;
using std::string, std::string_view;
using std::pair, std::exchange;
using std::nothrow, std::bad_alloc;

void memory_from_the_heap();
void array_from_the_heap();
void handling_exceptions();
void nodes_from_the_heap_v1();
void nodes_from_the_heap_v2();
void nodes_arrays_from_the_heap();

int main() {
    cout << endl << "--- " << __FILE__ << " ---" << endl << endl;

    memory_from_the_heap();
    array_from_the_heap();
    handling_exceptions();
    nodes_from_the_heap_v1();
    nodes_from_the_heap_v2();
    nodes_arrays_from_the_heap();

    return EXIT_SUCCESS;
}

void memory_from_the_heap() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    int n{15};

    int *loc_pn{&n};                        // Pointer to a local int.
    int *heap_pn{new int{23}};              // Pointer to an int on the heap.

    cout << " 1| n=" << n << ", loc_pn=" << loc_pn << ", *loc_pn=" << *loc_pn
         <<", heap_pn=" << heap_pn << ", *heap_pn=" << *heap_pn << endl;

    delete heap_pn;                         // Free memory on the heap.

    cout << " 2| n=" << n << ", loc_pn=" << loc_pn << ", *loc_pn=" << *loc_pn
         <<", heap_pn=" << heap_pn << ", *heap_pn=" << *heap_pn << endl;

    // Anything strange here? This is for demonstration only.

    // Sometimes: delete heap_pn; heap_pn = nullptr;
}

void array_from_the_heap() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    /*
     * Assume the size is given (and valid) at runtime, for example,
     * from the user: cin >> n;
     */
    int n{12};
    cout << " 1| Input n(>2): " << n << endl;

    // Get an int array from the heap. Note, that does not work well on the stack as we have seen.
    int *fibs = new int[n];

    fibs[0]=1;
    fibs[1]=1;
    for (int i=2; i<n; ++i)
        fibs[i] = fibs[i-2] +fibs[i-1];

    cout << " 2| fibs=[1,1";
    for (int i=2; i<n; ++i)
        cout << "," << fibs[i];
    cout << "]" << endl;

    delete[] fibs;                          // Free the array, note the '[]' - why?

    /*
     * 'new int[n]' must be paired with 'delete[] fibs', otherwise only the
     * first element's destructor would be called (for non-trivial types).
     *
     * In real code, prefer std::vector to manage memory automatically.
     */
}

void handling_exceptions() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    auto large_size = 1L<<60;               // Large number (actual behavior depends on the platform/memory avail.).

    try {
        // If the allocation fails, throw bad_alloc
        const auto a = new int[large_size];
        cout << " 1| memory available" << endl;
        delete[] a;
    } catch (const bad_alloc &e) {
        cout << " 2| exception " << e.what() << endl;
    }
    try {
        // If the allocation fails, don’t throw bad_alloc but return nullptr.
        const auto a = new(nothrow) int[large_size];
        cout << " 3| memory available? " << a << endl;
        delete[] a;
    } catch (const bad_alloc &e) {
        cout << " 4| exception " << e.what() << endl; // never executed!
    }

    // Don't confuse 'nothrow' this with 'noexcept', this means something totally different.
}

struct node {
    int payload;
    node* next;

    node(): payload{}, next{nullptr} {
        cout << " a| -> ctor(), payload=" << payload << endl;
    }

    explicit node(int payload) : payload{payload}, next{nullptr} {
        cout << " b| -> ctor(int), payload=" << payload << endl;
    }

    ~node() {
        cout << " c| -> dtor(), payload=" << payload << endl;
    }
};

void nodes_from_the_heap_v1() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    cout << " 1| create nodes:" << endl;
    node *head{new node{1}}, *p;

    p = head;
    for (int i=2; i<=5; ++i, p = p->next) {
        p->next = new node{i};
        cout << " 2| -> p=" << p << ", p->next=" << p->next << endl;
    }

    cout << " 3| payloads: [";
    p = head;
    while (p!=nullptr) {
        cout << " " << p->payload;
        p = p->next;
    }
    cout << " ]" << endl;

    cout << " 4| delete nodes:" << endl;
    p = head;
    while (p!=nullptr) {                    // don't: delete p, then p=p->next
        node *q{p};
        p = p->next;
        delete q;
    }
    // head = nullptr;                      // good practice: no dangling head after deletion
}

void nodes_from_the_heap_v2() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    cout << " 1| create nodes:" << endl;
    node *head{new node{1}};

    for (auto [p,i]=pair(head,2); i<=5; ++i) {
        p = p->next = new node{i};
        cout << " 2| -> p=" << p << ", p->next=" << p->next << endl;
    }

    cout << " 3| payloads: [";
    for (auto p=head; p; p=p->next)
        cout << " " << p->payload;
    cout << " ]" << endl;

    cout << " 4| delete nodes:" << endl;
    while (head)
        delete exchange(head, head->next);  // exchange(head, head->next) returns the old head and advances head.
}

void nodes_arrays_from_the_heap() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    cout << " 1| create nodes:" << endl;
    auto a = new node[5];                   // default ctor is needed

    cout << " 2| delete nodes:" << endl;
    delete[] a;
}
