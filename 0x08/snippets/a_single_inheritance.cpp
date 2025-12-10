// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * This code demonstrates single inheritance through a hierarchy of
 * classes: widget -> button -> icon.
 * It shows the order of constructor/destructor calls and memory layout
 * of derived classes.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>

using std::cout, std::endl;
using std::string, std::string_view;
using std::unique_ptr, std::make_unique;

void inheritance_inits();

int main() {
    cout << endl << "--- " << __FILE__ << " ---" << endl << endl;

    inheritance_inits();

    return EXIT_SUCCESS;
}

/*
 * class or struct - same idea (struct: all public).
 */

struct widget {
    int id{1};
    widget() { cout << " a|   widget()" << endl; }
    ~widget() { cout << " b|   ~widget()" << endl; }
};

struct button : widget {
    int clicked{2};
    button() { cout << " c|   button(), id=" << id << endl; }
    ~button() { cout << " d|   ~button()" << endl; }
};

struct icon : button {
    int ressource{3};
    icon() { cout << " e|   icon(), id=" << id << ", clicked=" << clicked << endl; }
    ~icon() { cout << " f|   ~icon()" << endl; }
};

/*
 * The key point here is the order of the calls. Otherwise, this single inheritance
 * behaves as one is used to from other languages.
 */

void inheritance_inits() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    {
        cout << " 1| define widget" << endl;
        const widget w;
        cout << " 2| destroy widget (size=" << sizeof(widget) << ")" << endl;
    }

    {
        cout << " 3| define button" << endl;
        const button b;
        cout << " 4| destroy button (size=" << sizeof(button) << ")" << endl;
    }

    {
        cout << " 5| define icon" << endl;
        const icon i;
        cout << " 6| destroy icon (size=" << sizeof(icon) << ")" << endl;
    }
}
