// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * This code demonstrates memory allocation using C-style functions malloc, realloc and free:
 *  – malloc allocates raw memory
 *  – realloc changes size of allocated memory
 *  – free releases allocated memory
 *  – Important: Always check if allocation was successful
 *  – Important: Free memory when no longer needed.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>
#include <cstdlib>                          // malloc, calloc, realloc, free

using std::cout, std::cerr, std::endl, std::ostream;
using std::string, std::string_view;
using std::malloc, std::calloc, std::free;

void alloc_and_free_mem();

int main() {
    cout << "\n--- " << __FILE__ << " ---" << endl;

    alloc_and_free_mem();

    return EXIT_SUCCESS;
}

void alloc_and_free_mem() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    cout << " 1| allocating memory" << endl;

    // old C-style

    const size_t count{5};
    int *a = (int*)malloc(count * sizeof(int)); // or calloc for zero-initialized memory
    cout << " 2| a=" << a << endl;

    if (!a) {
        std::cerr << " a| -> malloc failed" << endl;
        return;
    }

    const size_t new_count{10};
    int* b = (int*)realloc(a, new_count * sizeof(int));
    cout << " 3| a=" << a << ", b=" << b << endl;

    if (!b) {
        cerr << "realloc failed; original pointer is still valid" << endl;
        free(a);   // must free the old pointer!
        return;
    }

    // If realloc fails, the original pointer stays valid, so this is wrong
    //      a = realloc(a, new_count * sizeof(int));

    // do something meaningful with the memory

    free(b);
}
