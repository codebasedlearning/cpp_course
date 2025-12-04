// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * This file demonstrates the use of friend declarations in C++.
 *  – Friends allow specific functions or classes to access private members of a class.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>

using std::cout, std::endl, std::ostream;
using std::string, std::string_view;

void use_friends();

int main() {
    cout << endl << "--- " << __FILE__ << " ---" << endl << endl;

    use_friends();

    return EXIT_SUCCESS;
}

/*
 * 'friend'
 *    – lets one specific function or class access another class’s private and protected members.
 *      Without a friend declaration, only the class itself and its members can access them.
 *    – 'friend' can be used when two types must cooperate closely internally, e.g., containers
 *      and their nodes, iterators, helper functions, or serialization code.
 *
 * Important: you can't declare yourself as a friend, you are chosen (or not).
 */

class node {                                // assume Node is used by more than one class
    int payload;
    node* next;

    explicit node(int value) : payload{value}, next{nullptr} {
        // cout << " a| -> ctor(int), payload=" << payload << endl;
    }

    ~node() {
        // cout << " b| -> dtor(), payload=" << payload << endl;
    }

    friend class LinkedList;                // the whole class is a friend
};

class LinkedList {
    node *head{nullptr};

    LinkedList() = default;                 // private, so only the factory constructs instances, see below
    LinkedList(const LinkedList&) = delete; // no copy

public:
    ~LinkedList() {
        while (head != nullptr) {
            delete std::exchange(head, head->next); // Replaces first with second and returns the old first value.
        }
    }

    void push_front(const int value) {
        const auto n = new node(value);     // LinkedList can create nodes and
        n->next = head;                     // access node::next
        head = n;
    }

    friend ostream& operator<<(ostream& os, const LinkedList& list) {
        os << "[ ";
        for (const node *n = list.head; n != nullptr; n = n->next) {
            os << n->payload << " ";        // LinkedList can access node::payload
        }
        return os << "]";
    }

    friend LinkedList make_list();          // this factory function is a friend
};

LinkedList make_list() { return {}; }       // same as LinkedList()

void use_friends() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    auto list = make_list();

    list.push_front(3);
    list.push_front(2);
    list.push_front(1);

    cout << " 1| list=" << list << endl;
}
