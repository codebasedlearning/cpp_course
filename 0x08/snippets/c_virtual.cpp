// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * This code demonstrates virtual functions and polymorphism in C++, comparing it
 * with Java's behavior.
 * It discusses how to achieve dynamic dispatch using virtual functions, their memory implications
 * through vtables, and various examples of polymorphic behavior using pointers and references.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>
#include <memory>
#include <format>

using std::cout, std::endl;
using std::string, std::string_view;
using std::format;
using std::unique_ptr, std::make_unique;

void compare_with_java();
void compare_with_java_again();
void compare_sizes();
void test_yourself();

int main() {
    cout << endl << "--- " << __FILE__ << " ---" << endl << endl;

    compare_with_java();
    compare_with_java_again();
    compare_sizes();
    test_yourself();

    return EXIT_SUCCESS;
}

/*
 * Compare to Java, there is no general 'Object' base class. Here we introduce
 * a base class 'object' to create a similar situation for understanding.
 */

class object {
public:
    int n{};
    // Print the object’s address to identify the object instance.
    string to_string() const { return format("object  ({})",static_cast<const void*>(this)); }
};

class address : public object {
public:
    string to_string() const { return format("address ({})",static_cast<const void*>(this)); }
};

class mobile : public object {
public:
    string to_string() const { return format("mobile  ({})",static_cast<const void*>(this)); }
};

// To print all instances, we have to use the base class (ref) type.
void print_object(const object &o) {
    cout << " a| o: " << o.to_string() << endl;
}

void compare_with_java() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    const address a;
    cout << " 1| a: " << a.to_string() << endl;
    print_object(a);

    const mobile m;
    cout << " 2| m: " << m.to_string() << endl;
    print_object(m);

    // Where is the difference to Java?
}

/*
 * We want to achieve polymorphic behavior. To do this, we mark the functions that
 * are affected.
 *
 * Note: Unlike in Java, this behavior is not preset by default since it comes with
 * a cost - more on this later.
 */

class base {
public:
    int n{};
    // Here is the thing.
    virtual string to_string() const { return format("base ({})",static_cast<const void*>(this)); }
};

class number : public base {
public:
    // There is no need to repeat 'virtual'. Instead, we note 'override' (in fact also optional).
    string to_string() const override { return format("number ({})",static_cast<const void*>(this)); }
};

class scalar : public base {
public:
    string to_string() const override { return format("scalar ({})",static_cast<const void*>(this)); }
};

// Same situation as in 'print_object' before.
void print_base(const base &b) {
    cout << " a| b: " << b.to_string() << endl;
}

void compare_with_java_again() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    const number n;
    cout << " 1| n: " << n.to_string() << endl;
    print_base(n);

    const scalar s;
    cout << " 2| s: " << s.to_string() << endl;
    print_base(s);
}

/*
 * We talked about costs. Compare the size of the objects. Here you can see that all objects
 * only have one member of int type, but are different in size.
 * Almost all compilers implement polymorphic behavior using so-called vtables, which are tables
 * with function pointers that contain, among other things, the virtual functions of the current
 * class. So there is one per class.
 * And at the beginning of the object there is a pointer to this vtable. Together with the 'this'
 * pointers, the call can be resolved this way.
 * Note however, that this implementation approach is not prescribed.
 */

void compare_sizes() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    address a;
    number n;

    cout << " 1| sizeof a=" << sizeof(a) << ", sizeof n=" << sizeof(n) << endl;

    cout << " 2| address: &a=" << &a << ", &a.n=" << &a.n << endl;
    cout << " 3|  number: &n=" << &n << ", &n.n=" << &n.n << " -> gap" << endl;
}

class A {
public:
    void f()          { cout << " a|   A::f" << endl; }
    virtual void g()  { cout << " b|   A::g" << endl; }
};

class B : public A {
public:
    void f()          { cout << " c|   B::f" << endl; }
    void g() override { cout << " d|   B::g" << endl; }
};

/*
 * Test yourself: What is printed?
 */

void test_yourself() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    A a;
    B b;

    cout << " 1| a:" << endl;
    a.f();
    a.g();

    cout << " 2| b:" << endl;
    b.f();
    b.g();

    A *pa = new A(), *pb = new B();

    cout << " 3| pa:" << endl;
    pa->f();
    pa->g();

    cout << " 4| pb:" << endl;
    pb->f();
    pb->g();

    delete pa;
    delete pb;

    A &ra = a, &rb = b;

    cout << " 5| ra:" << endl;
    ra.f();
    ra.g();

    cout << " 6| rb:" << endl;
    rb.f();
    rb.g();
}
