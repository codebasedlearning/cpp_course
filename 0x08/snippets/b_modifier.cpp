// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * This code demonstrates access modifiers (private, protected, public) in classes
 * and their impact on inheritance. It shows how different inheritance types
 * (public, protected, private) affect member accessibility.
 *
 * One must distinguish who wants to access the members of a class:
 *  – a "user", i.e. someone working with an instance (always needs public)
 *  – a derived class.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>
#include <format>

using std::cout, std::endl;
using std::string, std::string_view;
using std::format;

void use_modifier();

int main() {
    cout << endl << "--- " << __FILE__ << " ---" << endl << endl;

    use_modifier();

    return EXIT_SUCCESS;
}

class widget {
private:
    int priv = 1;
protected:
    int prot = 2;
public:
    int pub = 3;

    // internal ok: pub,prot,priv | nok: -
    // external ok: pub | nok: prot,priv
    string info() { return format("'pub={}, prot={}, priv={}'", pub, prot, priv); }
};

/*
 * public inheritance ('public widget') means all public members in 'widget'
 * remain public for 'button' users.
 */

class button : public widget {
public:
    // internal ok: pub,prot | nok: priv
    // external ok: pub | nok: prot,priv
    string info() { return format("'pub={}, prot={}'", pub, prot); }
};

/*
 * protected inheritance ('protected widget') means that public members in 'widget'
 * become 'protected' in 'text'.
 */

class text: protected widget {
public:
    // internal ok: pub,prot | nok: priv
    // external ok: - | nok: pub,prot,priv
    string info() { return format("'pub={}, prot={}'", pub, prot); }
};

class headline: public text {
public:
    // internal ok: pub,prot | nok: priv
    // external ok: - | nok: pub,prot,priv
    string info() { return format("'pub={}, prot={}'", pub, prot); }
};

/*
 * private inheritance ('private widget') means that public and protected members
 * in 'widget' become private in 'checkbox'.
 */

class checkbox: private widget {
public:
    // internal ok: pub,prot | nok: priv
    // external ok: - | nok: pub,prot,priv
    string info() { return format("'pub={}, prot={}'", pub, prot); }
};

class iconbox: public checkbox {
public:
    // internal ok: - | nok: pub,prot,priv
    // external ok: - | nok: pub,prot,priv
    string info() { return format("'-'"); }
};


void use_modifier() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    widget w;
    cout << " 1| widget pub="  << w.pub << ", info=" << w.info() << endl;

    button b;
    cout << " 2| button pub="  << b.pub << ", info=" << b.info() << endl;

    text t;
    cout << " 3| text          info=" << t.info() << endl;
    headline h;
    cout << " 4| headline      info=" << h.info() << endl;

    checkbox c;
    cout << " 5| checkbox      info=" << c.info() << endl;
    iconbox i;
    cout << " 6| iconbox       info=" << i.info() << endl;
}
