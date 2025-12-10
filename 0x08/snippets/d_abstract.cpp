// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * This code demonstrates abstract classes, pure virtual functions, and virtual destructors.
 * It shows how to define interfaces and abstract classes in C++, and illustrates the
 * importance of virtual destructors in inheritance hierarchies. Also demonstrates that
 * pure virtual destructors still need a definition.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>
#include <vector>

using std::cout, std::endl, std::format;
using std::string, std::string_view;
using std::vector;

void there_is_no_interface();
void virtual_dtors();
void virtual_dtors_need_a_definition();

int main() {
    cout << endl << "--- " << __FILE__ << " ---" << endl << endl;

    there_is_no_interface();
    virtual_dtors();
    virtual_dtors_need_a_definition();

    return EXIT_SUCCESS;
}

/*
 * Note the 'pure virtual' function '=0'. This means:
 *  – The class is abstract, you cannot instantiate it.
 *  – The function must be overridden in any concrete derived class before it becomes instantiable.
 *  – The base class may optionally still provide a definition.
 *
 * virtual (not pure), and no definition:
 *  – In both cases, you have a declaration but no definition for a function that the program
 *  ends up needing. The difference is conceptual:
 *   – Pure virtual: expresses an interface contract; class becomes abstract.
 *   – Non-pure: expresses an interface with a default implementation that you forgot to actually write.
 */

class report {
    virtual void create_report() = 0;
};

class customer : public report {
public:
    void create_report() override {
        cout << " a| -> create_report()" << endl;
    }
};

void there_is_no_interface() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    customer c;

    cout << " 1| c:" << endl;
    c.create_report();

    // Not possible to create an instance because 'report' is abstract, it has 'pure' virtual functions.
    // report r;
}

/*
 * What is the difference between an interface and an abstract class?
 *
 * Abstract class: A class that contains at least one pure virtual function:
 *  – Cannot be instantiated
 *  – May have data members
 *  – May have non-virtual, virtual, and pure virtual functions
 *  – May have default implementations (even of pure virtuals!)
 *  – May have constructors, destructors, protected members, etc.
 * => It’s a normal C++ class with an enforced abstract method.
 *
 * Interface (C++ usage): A design pattern, not a language feature. An 'interface' in C++
 * is simply a class you intentionally restrict to behave like interfaces in other languages:
 *  – All member functions are pure virtual
 *  – No data members
 *  – No implementation (with rare exceptions)
 *  – Public virtual destructor
 *  – No state
 */

class object {
public:
    virtual string to_string() const { return "object::to_string"; }

    virtual                                 // comment out to see the problem
    ~object() { cout << format(" a| -> dtor object {}",static_cast<const void*>(this)) << endl; }
};

class cloneable {
public:
    virtual object* clone() = 0;
};

class address : public object, cloneable {  // Technically this is multiple inheritance.
public:
    string to_string() const override { return "address::to_string"; }

    // we omit 'override' by purpose
    ~address() { cout << " b| -> dtor::address" << endl; }

    object* clone() override { return new address(); }
};

class buffer : public object, cloneable {
public:
    string to_string() const override { return "buffer::to_string"; }

    buffer() : p(new int) { }

    ~buffer() {
        cout << " c| -> dtor::buffer" << endl;
        delete p;
    }

    object* clone() override { return new buffer(); }

private:
    int* p;
};

void virtual_dtors() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    address a;
    buffer b;

    cout << " 1| a:" << a.to_string() << " " << &a << endl;
    cout << " 2| b:" << b.to_string() << " " << &b << endl;

    cout << "-----" << endl;

    vector<object*> v;                      // create 4 objects: address, buffer, address, buffer
    v.push_back(a.clone());
    v.push_back(b.clone());
    v.push_back(a.clone());
    v.push_back(b.clone());

    for (object* o : v) {
        cout << " 3| v:" << o->to_string() << endl;
    }

    cout << "-----" << endl;

    for (object* o : v)
        delete o;
    v.clear();

    cout << "-----" << endl;
}

/*
 * This one is interesting. Even though ~base is pure, you must still provide
 * a definition.
 *
 * The program must eventually run base::~base() as part of the chain. So the
 * destructor is always called – hence must have a body (or a linker error follows).
 * So for destructors, the rule is:
 *  – Pure virtual destructor still needs a definition.
 */

struct base {
    virtual ~base() = 0;
    virtual void f() = 0;
};

base::~base() {}                            // comment out

struct derived : base {
    ~derived() {}
    void f() {}
};

void virtual_dtors_need_a_definition() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    derived d;
}
