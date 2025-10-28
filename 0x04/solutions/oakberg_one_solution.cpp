// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * Oakberg solution.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>
#include <vector>
#include <array>
#include <sstream>
#include <ranges>

using std::cout, std::endl, std::ostream;
using std::string, std::string_view;
using std::ostringstream;
using std::vector, std::array;
using std::ranges::find, std::ranges::distance;

template <typename T>
string join(const T &container) {
    ostringstream os;
    string_view delim;                      // "delimiter string" idiom
    for (const auto &x : container) {
        os << delim << x;
        delim = ",";
    }
    return os.str();
}

template <typename T>
void perform_operations(const string_view name, T &container) {
    cout << " 1| " << name << "=[" << join(container) << "]" << endl;

    for (auto &x : container) { x *= 2; }
    cout << " 2| " << name << "=[" << join(container) << "]" << endl;

    cout << " 3| " << name << "-view=[";
    if (auto it = find(container, 6); it != container.end()) {
        cout << *it;
        for (auto it2=++it; it2!=container.end() && distance(it,it2)<2; ++it2) // or use a simple counter
            cout << " " << *it2;
    }
    cout << "]" << endl;
}

int main() {
    cout << "\n--- " << __FILE__ << " ---" << endl;

    array a{2, 3, 5, 7, 11};
    vector v(a.begin(), a.end());

    perform_operations("a",a);
    cout << endl;
    perform_operations("v",v);

    return EXIT_SUCCESS;
}
