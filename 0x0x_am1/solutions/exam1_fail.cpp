// Ihr Name: A. Voß
// Matr.nr.: 1234567 a.voss@fh-aachen.de, info@codebasedlearning.dev

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <stdexcept>
#include <cstdlib>

using std::cout, std::endl, std::ostream;
using std::string;
using std::unordered_map;
using std::vector;
using std::runtime_error;

using index_type = unsigned int;

index_type next_id_wrong_named{1};

ostream& operator<<(ostream& os, const vector_type& v) { return os; }

class multi_set {};

int main() {
    cout << "\n--- " << __FILE__ << " ---" << endl;

    cout << "Test a) ..." << endl;

    try {
        multi_set ms;
    } catch (...) {

    }

    // n) Die Funktion gibt 42 zurück, das ist keine Antwort.

    return EXIT_SUCCESS;
}
