// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * Rose Pond solution.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>
#include <unordered_map>

using std::cout, std::endl, std::ostream;
using std::string, std::string_view;
using std::unordered_map;
using std::unique_ptr, std::make_unique;

struct address {
    string name;
    string number;
};

int main() {
    cout << "\n--- " << __FILE__ << " ---" << endl;

    cout << " 1| create map" << endl;

    unordered_map<int,address*> ptr_map;
    ptr_map[1] = new address{"Max","112"};
    ptr_map[2] = new address{"Mini","110"};
    ptr_map[3] = new address{"Jane","911"};

    cout << " 2| print map, size: " << ptr_map.size() << endl;

    for (const auto &kv: ptr_map) {
        cout << " a| -> {id: " << kv.first
             << ", name: '" << kv.second->name << "'"
             << ", number: '" << kv.second->number << "'}" << endl;
    }

    cout << " 3| delete map data" << endl;

    // Manual memory management (not recommended in modern code)

    // auto it = ptr_map.begin();
    // while (it != ptr_map.end()) {
    //     delete it->second;
    //     it = ptr_map.erase(it);  // C++11, before: map.erase(it++);
    //     ptr_map.erase(it++);
    // }

    for (auto &kv: ptr_map) {
        delete kv.second;
    }
    ptr_map.clear();

    cout << " 4| empty map? size:" << ptr_map.size() << endl;

    unordered_map<int, unique_ptr<address>> uni_map;

    // one way
    // uni_map[0] = make_unique<address>("Alex", "+49 1234");

    // better
    uni_map.emplace(0, make_unique<address>("Alex", "+49 1234"));

    cout << " 5| map size: " << uni_map.size() << ", [0]:" << uni_map[0]->name << endl;
    uni_map.clear();

    return EXIT_SUCCESS;
}
