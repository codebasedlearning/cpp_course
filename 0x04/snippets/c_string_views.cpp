// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * This code demonstrates the use of string_view, a non-owning view over character sequences.
 * It provides an efficient way to work with strings without copying data, but comes with 
 * lifetime considerations since it doesn't own the memory it references.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>

using std::cout, std::endl, std::cin;
using std::string, std::string_view;
using namespace std::string_literals;
using namespace std::string_view_literals;

void using_string_literal();
void using_string_views();
void lifetime_issues();

void print(string_view sv);
string_view extract_this(const string &s);

int main() {
    cout << "\n--- " << __FILE__ << " ---" << endl;

    using_string_literal();
    using_string_views();
    lifetime_issues();

    return EXIT_SUCCESS;
}

/*
 * Sometimes the literals 's' and 'sv' come handy.
 */
void using_string_literal() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    auto text = "This is a text (but no string).";  // const char* (C-string)
    cout << " 1| text='" << text << "'" << endl;

    // using namespaces needed for operator""s and operator""sv:

    auto str = "This is a string literal."s;        // string
    cout << " 2| str ='" << str << "'" << endl;

    auto sv = "This is a string view literal."sv;   // string_view
    cout << " 2| sv  ='" << sv << "'" << endl;
}

/*
 * 'string_view' is a non-owning view over a sequence of characters — typically a string literal,
 * a string, or any contiguous character array.
 * It behaves like a string in many ways (you can call .size(), .substr(), .find(), etc.), but it
 * does not own the memory it points to. It’s basically a pointer + length pair.
 */
void using_string_views() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    cout << " 1| "; print("simple c-string");                   // const char*
    cout << " 2| "; print(string("simple string"));             // temp. string — OK: lives to end of call
    cout << " 3| "; print(string_view("simple string_view"));

    // cout << " 2| "; print("simple string"s);
    // cout << " 3| "; print("simple string_view"sv);

    const string s{"This is a long sentence!"};
    cout << " 4| substr='" << s.substr(10, 4) << "' (with copy)" << endl;
    cout << " 5| or     '" << string_view(s).substr(10, 4) << "' (w.o. copy)" << endl;
}

/*
 * 'print_sv' is inexpensive because the string_view adapts to multiple source types with no copy.
 * No need for reference semantics — it’s already a small, trivially copyable value type.
 */
void print(string_view sv) {
    cout << "length=" << sv.size() << " | content='" << sv << "'" << endl;
}

/*
 * Because it doesn’t own the memory, you must not outlive the original string.
 */
void lifetime_issues() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    const string s{"This is a long sentence!"};
    cout << " 1| s='" << s << "'" << endl;

    // A "it seems to work, until it doesn’t" C++ moments. Where is the problem?
    string_view word;
    {
        const string t{s};                    // t is a copy of s.
        word = string_view(t).substr(0, t.find(' '));
        cout << " a|   word='" << word << "'" << endl;
    }
    cout << " 2| word='" << word << "'" << endl;

    // Same problem.
    word = extract_this(s);
    cout << " 3| word='" << word << "'" << endl;
}

string_view extract_this(const string &s) {
    const auto t{s};
    const string_view word = string_view(t).substr(0, t.find(' '));
    cout << " b|   word='" << word << "'" << endl;
    return word;
}
