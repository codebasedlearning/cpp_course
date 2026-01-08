// (C) 2025 A.Voß, a.voss@fh-aachen.de, cpp@codebasedlearning.dev

/*
 * Openshaw solution.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>
#include <iomanip>
#include <memory>
#include <vector>

using std::cout, std::endl;
using std::string, std::string_view;
using std::vector, std::unique_ptr, std::make_unique, std::shared_ptr, std::make_shared;

// A very small class.
struct X {
    X() { cout << " a| -> ctor" << endl; }
    ~X() { cout << " b| -> dtor" << endl; }
};

int main() {
    cout << endl << "--- " << __FILE__ << " ---" << endl << endl;

    cout << " 1| raw pointers" << endl;
    {
        vector<X*> vRaw;
        vRaw.push_back(new X);
        vRaw.push_back(new X);
        vRaw.push_back(new X);

        cout << " 2| vRaw:";
        for (const auto &x : vRaw)
            cout << " " << &x;
        cout << endl;

        for (const auto &x : vRaw)
            delete x;
    }
    cout << endl;

    cout << " 3| unique pointers" << endl;
    {
        vector<unique_ptr<X>> vUnique;
        vUnique.push_back(make_unique<X>());
        vUnique.push_back(make_unique<X>());
        vUnique.push_back(make_unique<X>());

        cout << " 4| vUnique:";
        for (const auto &x : vUnique)
            cout << " " << &x;
        cout << endl;
    }
    cout << endl;

    cout << " 5| shared pointers" << endl;
    {
        vector<shared_ptr<X>> vShared;
        vShared.push_back(make_shared<X>());
        vShared.push_back(make_shared<X>());
        vShared.push_back(make_shared<X>());

        cout << " 6| vShared:";
        for (const auto &x : vShared)
            cout << " " << &x;
        cout << endl;
    }
    cout << endl;

    return EXIT_SUCCESS;
}
