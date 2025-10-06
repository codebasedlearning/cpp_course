// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

#include <iostream>
#include <cstdlib>

using std::cout, std::endl;

int main() {
    cout << "\n--- " << __FILE__ << " ---" << endl;

    const int dim{3};

    double arr_a[dim]{1.0, 2.0};
    arr_a[2] = arr_a[0] + arr_a[1];

    cout << "arr_a: ";
    for (size_t i{0}; i < dim; ++i) {
        cout << arr_a[i] << " ";
    }
    cout << endl;

    double arr_b[dim];
    for (size_t i = 0; i < dim; ++i) {
        arr_b[i] = arr_a[i];
    }

    cout << "arr_b: ";
    for (size_t i{0}; i < dim; ++i) {
        cout << arr_b[i] << " ";
    }
    cout << endl;

    return EXIT_SUCCESS;
}
