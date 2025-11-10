// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * McAllen Spring solution.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>

using std::cout, std::endl, std::ostream;
using std::string, std::string_view;

class Node {
    int payload;
    Node *next;

public:
    explicit Node(int payload, Node* next = nullptr) : payload{payload}, next{next} { }

    [[nodiscard]] int get_payload() const { return payload; }
    [[nodiscard]] Node* get_next() const { return next; }
};

int main() {
    cout << "\n--- " << __FILE__ << " ---" << endl;

    Node node_c{7};
    Node node_b{5, &node_c};
    Node node_a{3, &node_b};
    Node root{2, &node_a};

    cout << " 1| numbers:" << endl;
    for (auto node = &root; node != nullptr; node = node->get_next()) {
        cout << " a| -> n=" << node->get_payload() << endl;
    }

    return EXIT_SUCCESS;
}
