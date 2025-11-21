// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * This snippet demonstrates different approaches to create and use 2D arrays:
 *  - Fixed-size 2D arrays with compile-time dimensions
 *  - Dynamic contiguous allocation using a 1D array with indexing helper
 *  - Dynamic allocation using pointer-to-pointer approach
 *
 * Each method shows memory layout and access patterns.
 *
 * Btw.: going from 2D to 3D is 2D with one more nested loop and one more * size in the index.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>

using std::cout, std::cerr, std::endl, std::ostream;
using std::string, std::string_view;
using std::unique_ptr, std::make_unique, std::move;

void fixed_size_2D_array();
void contiguous_dynamic_2D_array();
void pointer_to_pointer_2D_array();

int main() {
    cout << "\n--- " << __FILE__ << " ---" << endl;

    fixed_size_2D_array();
    contiguous_dynamic_2D_array();
    pointer_to_pointer_2D_array();

    return EXIT_SUCCESS;
}

void fixed_size_2D_array() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    int a[3][4] = {
        { 11, 12, 13, 14 },
        { 21, 22, 23, 24 },
        { 31, 32, 33, 34 }
    };

    cout << " 1| fixed-size 2D array, a: " << a << endl;

    cout << " 2| addresses and values:\n";
    for (int r = 0; r < 3; ++r) {
        cout << " 3| -> a[" << r << "]: " << a[r];
        for (int c = 0; c < 4; ++c) {
            cout << " | &a[" << r << "][" << c
                 << "]: " << &a[r][c] << " (" << a[r][c] << ")";
        }
        cout << endl;
    }
}

void contiguous_dynamic_2D_array() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    // obtained at runtime
    size_t rows = 3;
    size_t cols = 4;

    // one contiguous block for all elements
    unique_ptr<int[]> a = make_unique<int[]>(rows * cols);
    // or raw: int* a = new int[rows * cols];

    cout << " 1| contiguous dynamic 2D array, a: " << a << endl;

    // helper for 2D indexing (lambdas will be discussed)
    auto idx = [cols](const int r, const int c) { return r * cols + c; };

    // fill/access data
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            a[idx(r, c)] = (r+1) * 10 + (c+1);
        }
    }

    cout << " 2| addresses and values:\n";
    for (int r = 0; r < rows; ++r) {
        cout << " 3| -> a[" << r << "]";
        for (int c = 0; c < cols; ++c) {
            int* p = &a[idx(r, c)];
            cout << " | &a[" << r << "][" << c
                      << "]: " << p << " (" << *p << ")";
        }
        cout << endl;
    }

    // if raw -> delete[] a;
}

void pointer_to_pointer_2D_array() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    // obtained at runtime
    size_t rows = 3;
    size_t cols = 4;

    /*
     * Allocate array of raw pointers.
     * Here, smart pointers add complexity but no real gain, and this gets ugly very fast:
     *    - ownership is nested
     *    - need arrays of smart pointers:
     *          unique_ptr<unique_ptr<int[]>[]> a;
     * It works — but it’s teaching the tool, not the concept.
     */
    int **a = new int*[rows];

    // allocate each row separately
    for (int r = 0; r < rows; ++r)
        a[r] = new int[cols];

    cout << " 1| pointer to pointer 2D array, a: " << a << endl;

    /*
     * You sometimes observe that:
     *    - a itself is a contiguous array of pointers (guaranteed).
     *    - The rows you allocate with individual new[] calls happen to be physically
     *      next to each other (not guaranteed). This is allocator behavior.
     */

    // fill
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            a[r][c] = (r+1) * 10 + (c+1);
        }
    }

    cout << " 2| addresses and values:\n";
    for (int r = 0; r < rows; ++r) {
        cout << " 3| -> a[" << r << "]: " << a[r];
        for (int c = 0; c < cols; ++c) {
            int* p = &a[r][c];
            cout << " | &a[" << r << "][" << c
                      << "]: " << p << " (" << *p << ")";
        }
        cout << endl;
    }

    // free in reverse order of allocation
    for (int r = 0; r < rows; ++r)
        delete[] a[r];

    delete[] a;

    // Finally: if you’re building a real abstraction, use a Matrix class
    // or vector<T> internally, not int**.
}
