// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * This code demonstrates multiple inheritance and the diamond problem in C++.
 * It shows:
 *  – Regular multiple inheritance with two separate base class instances.
 *  – Virtual inheritance to solve the diamond problem with a shared base.
 * Both examples show constructor/destructor ordering and memory layout.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>

using std::cout, std::endl;
using std::string, std::string_view;

void multiple_inheritance();
void multiple_inheritance_diamond();

int main() {
    cout << endl << "--- " << __FILE__ << " ---" << endl << endl;

    multiple_inheritance();
    multiple_inheritance_diamond();

    return EXIT_SUCCESS;
}

struct B {                                  // base
    int id;

    B(int id) : id(id) { cout << " a| ->  B(" << id << ")" << endl; }
    ~B()               { cout << " b| -> ~B(" << id << ")" << endl; }
};

struct D1a : public B {                     // derived
    D1a(int id) : B(id) { cout << " c| --->  D1a(" << id << ")" << endl; }
    ~D1a()              { cout << " d| ---> ~D1b(" << id << ")" << endl; }
};

struct D1b : public B {                     // derived
    D1b(int id) : B(id) { cout << " e| --->  D1b(" << id << ")" << endl; }
    ~D1b()              { cout << " f| ---> ~D1b(" << id << ")" << endl; }
};

struct M1 : public D1a, public D1b {        // multiple inheritance
    M1(int id) : D1a(id+1), D1b(id+2) { cout << " g| ----->  M1(" << D1a::id << "," << D1b::id << ")" << endl; }
    ~M1()                             { cout << " h| -----> ~M1(" << D1a::id << "," << D1b::id << ")" << endl; }
};

void multiple_inheritance() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    cout << " 1| d1a:" << endl;
    D1a d1a(1);
    cout << " 2| d1b:" << endl;
    D1b d1b(2);
    cout << " 3| m1:" << endl;
    M1 m1(3);

    cout << "-----" << endl;

    cout << " 4| sizeof   B=" << sizeof(B) << endl;
    cout << " 5| sizeof D1A=" << sizeof(D1a) << ", sizeof D1b=" << sizeof(D1b) << endl;
    cout << " 6| sizeof  M1=" << sizeof(M1) << endl;

    cout << " 7| m1.D1a::id=" << m1.D1a::id << ", m1.D1b::id=" << m1.D1b::id << endl;

    cout << "-----" << endl;
}

struct D2a : virtual public B {             // virtually derived
    D2a(int id) : B(id) { cout << " c| --->  D2a(" << id << ")" << endl; }
    ~D2a()              { cout << " d| ---> ~D2b(" << id << ")" << endl; }
};

struct D2b : virtual public B {             // virtually derived
    D2b(int id) : B(id) { cout << " e| --->  D2b(" << id << ")" << endl; }
    ~D2b()              { cout << " f| ---> ~D2b(" << id << ")" << endl; }
};

struct M2 : public D2a, public D2b {        // multiple inheritance
    M2(int id) : B(id), D2a(id+1), D2b(id+2) { cout << " g| ----->  M2(" << D2a::id << "," << D2b::id << ")" << endl; }
    ~M2()                             { cout << " h| -----> ~M2(" << D2a::id << "," << D2b::id << ")" << endl; }
};

void multiple_inheritance_diamond() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    cout << " 1| d2a:" << endl;
    D2a d2a(1);
    cout << " 2| d2b:" << endl;
    D2b d2b(2);
    cout << " 3| m2:" << endl;
    M2 m2(3);

    cout << "-----" << endl;

    cout << " 4| sizeof   B=" << sizeof(B) << endl;
    cout << " 5| sizeof D2A=" << sizeof(D2a) << ", sizeof D2b=" << sizeof(D2b) << endl;
    cout << " 6| sizeof  M2=" << sizeof(M2) << endl;

    cout << " 7| m2.D2a::id=" << m2.D2a::id << ", m2.D2b::id=" << m2.D2b::id << endl;

    cout << "-----" << endl;
}
