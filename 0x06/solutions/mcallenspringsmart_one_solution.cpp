// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * McAllen Spring Smart solution.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>
#include <memory>

using std::cout, std::endl, std::ostream;
using std::string, std::string_view;
using std::unique_ptr, std::make_unique;

class Node {
    int payload;
    std::unique_ptr<Node> next;


public:
    explicit Node(int payload, std::unique_ptr<Node> next = nullptr)
        : payload{payload}, next{std::move(next)} {
    }
    ~Node() {
        cout << " a| -> dtor: payload=" << payload << endl;
    }

    [[nodiscard]] int get_payload() const { return payload; }
    [[nodiscard]] const Node *get_next() const { return next.get(); }
};

int main() {
    cout << "\n--- " << __FILE__ << " ---" << endl;

    auto node_c = std::make_unique<Node>(7);
    auto node_b = std::make_unique<Node>(5, std::move(node_c));
    auto node_a = std::make_unique<Node>(3, std::move(node_b));
    auto root = std::make_unique<Node>(2, std::move(node_a));

    // or
    // auto root = std::make_unique<Node>(
    //     2, std::make_unique<Node>(
    //         3, std::make_unique<Node>(
    //             5, std::make_unique<Node>(7)
    //         )
    //     )
    // );

    // 'one owner, many observers' model

    cout << " 1| numbers:" << endl;
    for (const Node *node = root.get(); node != nullptr; node = node->get_next()) {
        cout << " a| -> n=" << node->get_payload() << endl;
    }

    return EXIT_SUCCESS;
}
