// (C) 2025 A.Voß, a.voss@fh-aachen.de, cpp@codebasedlearning.dev

/*
 * Banrockburn solution.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>
#include <iomanip>
#include <memory>
#include <vector>

using std::cout, std::endl, std::ostream;
using std::string, std::string_view;
using std::vector, std::unique_ptr, std::make_unique, std::shared_ptr, std::make_shared, std::weak_ptr;

template <typename T>
class Node {
public:
    explicit Node(const T &value) : value{value} {
        cout << " a| Node-ctor, value=" << value << endl;
    };
    ~Node() {
        cout << " b| Node-dtor, value=" << value << endl;
    };

    T value;

    shared_ptr<Node<T>> next{};
    weak_ptr<Node<T>> prev{};
};

template <typename T>
class List {
public:
    shared_ptr<Node<T>> root{nullptr};
    shared_ptr<Node<T>> tail{nullptr};

    List() { cout << " c| List-ctor, empty" << endl; };

    void add(const T& value) {
        auto n = std::make_shared<Node<T>>(value);

        if (!root) {                 // empty list
            root = tail = n;
            n->prev.reset();         // no previous
            return;
        }

        n->prev = tail;              // weak back-link (no cycle)
        tail->next = n;              // shared forward-link
        tail = std::move(n);
    }

    List& operator+=(const T& value) {
        add(value);
        return *this;
    }
};

template <typename T>
ostream& operator<<(ostream& os, const List<T>& list) {
    os << "[";

    auto cur = list.root;
    bool first = true;

    while (cur) {
        if (!first)
            os << ", ";
        first = false;

        os << cur->value;
        cur = cur->next;
    }

    return os << "]";
}

template <typename T>
ostream& print_reverse(ostream& os, const List<T>& list) {
    os << "[";

    auto cur = list.tail;
    bool first = true;

    while (cur) {
        if (!first)
            os << ", ";
        first = false;

        os << cur->value;
        cur = cur->prev.lock();             // move backwards via weak_ptr
    }

    return os << "]";
}

int main() {
    cout << endl << "--- " << __FILE__ << " ---" << endl << endl;

    List<int> list;

    list.add(1);
    list.add(2);
    list += 3;

    cout << " 1| forward-list: " << list << endl;
    cout << " 2| backward-list: "; print_reverse(cout,list) << endl;

    return EXIT_SUCCESS;
}
