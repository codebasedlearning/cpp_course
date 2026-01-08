// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * Demonstrates smart pointer usage:
 *  – shared_ptr for shared ownership with reference counting.
 *  – weak_ptr to break circular references and avoid memory leaks.
 *  – Observer/Listener pattern implementation using weak_ptr.
 *  – Tree traversal with parent-child relationships.
 *  – Proper memory management and lifecycle control.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>
#include <memory>
#include <vector>

using std::cout, std::endl, std::ostream;
using std::string, std::string_view;
using std::shared_ptr, std::make_shared, std::weak_ptr, std::vector;

void using_shared_pointers();
void using_weak_pointers();
void observer_listener_example();

int main() {
    cout << endl << "--- " << __FILE__ << " ---" << endl << endl;

    using_shared_pointers();
    using_weak_pointers();
    observer_listener_example();

    return EXIT_SUCCESS;
}

struct Number {
    int n;

    explicit Number(const int n) : n(n) { cout << " a| -> ctor, n=" << n << ", this=" << this << endl; }
    // Number(const Number& num)
    ~Number() { cout << " b| -> dtor, n=" << n << ", this=" << this << endl; }

    friend ostream & operator<<(ostream& os, const Number& num) { return os << num.n; }
};

void using_shared_pointers() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    cout << " 1| define" << endl;

    shared_ptr<Number> p1 = make_shared<Number>(1);
    shared_ptr<Number> p2 = p1;

    cout << " 2| *p1=" << (*p1) << ", p1.get=" << p1.get() << ", p1.use_count=" << p1.use_count() << endl;
    cout << " 3| *p2=" << (*p2) << ", p2.get=" << p2.get() << ", p2.use_count=" << p2.use_count() << endl;

    cout << " 4| reset p1" << endl;
    p1.reset();
    cout << " 5| *p1=" << "-"   << ", p1.get=" << p1.get() << ", p1.use_count=" << p1.use_count() << endl;
    cout << " 6| *p2=" << (*p2) << ", p2.get=" << p2.get() << ", p2.use_count=" << p2.use_count() << endl;

    cout << " 7| reset p2" << endl;
    p2.reset();
    cout << " 8| *p1=" << "-"   << ", p1.get=" << p1.get() << ", p1.use_count=" << p1.use_count() << endl;
    cout << " 9| *p2=" << "-"   << ", p2.get=" << p2.get() << ", p2.use_count=" << p2.use_count() << endl;
}

/*
 * A generic traverse tree function, assuming some Node-structure.
 */
template <typename N>
void traverse(const shared_ptr<N> &node) {
     if (!node) return;
     cout << " (id:" << node->id << "," << node.get() << ",#" << node.use_count()
          << node->extra()
          << "|children:" << node->children.size() << ")";
     for (const auto &child : node->children) {
          traverse(child);
     }
}

void using_weak_pointers() {
     cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

     cout << " 1| alloc Nodes (A)" << endl;
     {
          struct Node {
               int id;
               vector<shared_ptr<Node>> children;

               explicit Node(const int id) : id(id) { cout << " a| -> ctor, id=" << id << ", this=" << this << endl; }
               ~Node() { cout << " b| -> dtor, id=" << id << ", this=" << this << endl; }

               void add(const shared_ptr<Node>& node) {
                    children.push_back(node);
               }

               // To be used in 'traverse'.
               string extra() const { return ""; }
          };

          // Create some Nodes with 'root' as the only local variable.
          auto root = make_shared<Node>(11);
          root->add(make_shared<Node>(12));
          root->children[0]->add(make_shared<Node>(13));

          cout << " 2| traverse:";
          traverse(root);
          cout << endl;
     }
     // Check if everything is gone.
     cout << " 3| done Nodes (A)" << endl << endl;

     cout << " 4| alloc Nodes (B)" << endl;
     {
          struct Node  {                    // Skip concepts of enable_shared_from_this and shared_from_this() here.
               int id;
               vector<shared_ptr<Node>> children;
               shared_ptr<Node> parent;     // This is new, a 'link' to the parent Node.

               explicit Node(const int id) : id(id) { cout << " a| -> ctor, id=" << id << ", this=" << this << endl; }
               ~Node() { cout << " b| -> dtor, id=" << id << ", this=" << this << endl; }

               void add(const shared_ptr<Node>& node, const shared_ptr<Node> &par) {
                    node->parent = par;     // Save parent link.
                    children.push_back(node);
               }

               // Now give some extra info on parent-Node.
               string extra() const {
                    void *vp = parent.get();
                    auto cnt = parent.use_count();
                    return std::format("|parent:{},#{}",vp,cnt);
               }
          };

          // As before.
          auto root = make_shared<Node>(11);
          root->add(make_shared<Node>(12), root);
          root->children[0]->add(make_shared<Node>(13), root->children[0]);

          cout << " 5| traverse:";
          traverse(root);
          cout << endl;
     }
     // Check if everything is gone.
     cout << " 6| done Nodes (B)" << endl << endl;

     cout << " 7| alloc Nodes (C)" << endl;
     {
          struct Node  {
               int id;
               vector<shared_ptr<Node>> children;
               weak_ptr<Node> parent;

               explicit Node(const int id) : id(id) { cout << " a| -> ctor, id=" << id << ", this=" << this << endl; }
               ~Node() { cout << " b| -> dtor, id=" << id << ", this=" << this << endl; }

               void add(const shared_ptr<Node>& node, const shared_ptr<Node>& par) {
                    node->parent = par;
                    children.push_back(node);
               }

               string extra() const {
                    void *vp = nullptr;
                    long cnt = -1;
                    if (auto p = parent.lock()) {  // Returns a shared_ptr with the object or nullptr; standard pattern.
                         vp = p.get();
                         cnt = p.use_count();
                    }
                    return std::format("|parent:{},#{}",vp,cnt);
               }
          };

          auto root = make_shared<Node>(11);
          root->add(make_shared<Node>(12), root);
          root->children[0]->add(make_shared<Node>(13), root->children[0]);

          cout << " 8| traverse:";
          traverse(root);
          cout << endl;

          /*
           * Use std::weak_ptr when:
           *  – something is owned elsewhere
           *  – you need to refer to it safely
           *  – but must not extend its lifetime.
           */
     }
     cout << " 9| done Nodes (C)" << endl << endl;
}

/*
 * Observer - Listener - example
 *  – publisher should not keep listeners alive
 *  – listeners should auto-unregister when destroyed
 */
void observer_listener_example() {
     cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

     struct Listener {
          virtual void on_event() = 0;
     };

     class Button {                         // EventSource
          vector<weak_ptr<Listener>> listeners;

     public:
          void notify() {
               for (auto it = listeners.begin(); it != listeners.end(); ) {
                    if (auto listener = it->lock()) {
                         listener->on_event();
                         ++it;
                    } else {
                         it = listeners.erase(it);  // listener is gone
                    }
               }
          }

          void subscribe(const shared_ptr<Listener> &listener) {
               listeners.push_back(listener);
          }
     };

     struct Print : Listener {
          void on_event() override { cout << " a| print" << endl; }
     };
     struct Read : Listener {
          void on_event() override { cout << " b| read" << endl; }
     };

     cout << " 1| notify (A)" << endl;
     Button button;
     button.subscribe(make_shared<Print>());
     button.subscribe(make_shared<Read>());
     button.notify();


     // Didactic break.


     cout << " 2| notify (B)" << endl;
     auto print = make_shared<Print>();
     auto read = make_shared<Read>();
     button.subscribe(print);
     button.subscribe(read);
     button.notify();
}
