// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * Ashfield solution.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>
#include <unordered_map>

using std::cout, std::endl, std::ostream;
using std::string, std::string_view;
using std::unordered_map;

struct book {
    string autor;
    string titel;
};

using catalog_t = std::unordered_map<std::string, book>;

int main() {
    cout << "\n--- " << __FILE__ << " ---" << endl;

    catalog_t catalog;

    catalog["44245381X"] = { "Walter Moers", "The 13 1/2 Lives of Captain Bluebear" };
    catalog["9781338345728"] = { "Rowling, J.K.", "Harry Potter Books 1-7 Special Edition Boxed Set" };
    catalog["9780593157718"] = { "Soule, Charles", "Star Wars: Light of the Jedi (The High Republic)" };
    catalog["9780358439196"] = { "Tolkien, J.R.R.", "The Lord of the Rings Boxed Set" };

    cout << " 1| books:" << endl;
    for (const auto &book : catalog) {
        if (book.second.titel.size() > 40) {
            cout << " a|   " << book.second.autor << ": " << book.second.titel << endl;
        }
    }

    return EXIT_SUCCESS;
}
