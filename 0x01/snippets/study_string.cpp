// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * This code demonstrates string operations and methods:
 *   – string definition and concatenation
 *   – accessing characters with [] and at()
 *   – string size and empty checks
 *   – substring operations
 *   – find/rfind for pattern matching
 *   – replace, erase, insert and append operations
 *   – string::size_type and string::npos usage.
 */

#include <iostream>
#include <string>
#include <cstdlib>

using std::cout, std::endl, std::cin;
using std::string;

int main() {
    cout << "\n--- " << __FILE__ << " ---" << endl;

    string s{"Example"};                                    // Definition of a 'string'.
    cout << " 1| s='" << s << "'" << endl;

    cout << " 2| s+s='" << s+s << "' (op+)" << endl;        // Strings can be concatenated using '+'.
    cout << " 3| s[1]='" << s[1] << "' (op[])" << endl;     // Individual characters can be accessed; no bounds checking.
    s += "!";                                               // '+=' operator appends characters or text.
    cout << " 4| s='" << s << "' (op+=)" << endl;

    cout << " 5| s.size()=" << s.size() << endl;            // 'size' returns the length of the string, 0 is possible.
    cout << " 6| s.empty()=" << s.empty() << endl;          // 'empty' tests if the string is empty (size 0).
    cout << " 7| s.at(1)='" << s.at(1) << "'" << endl;      // 'at' reads a character at a position; with bounds checking.
    cout << " 8| s.substr(1,3)='" << s.substr(1,3) << "'" << endl;  // 'substr' reads a substring from a position for a given length.

    /*
     * By using a qualifier we can access objects or types in a class (or namespace) such as:
     * - string::size_type: The data type that represents positions/indices in a string.
     * - string::npos: A special constant value returned when no pattern is found in searches.
     */
    string::size_type pos;
    bool found;
    
    found = ((pos=s.find("amp"))!=string::npos);            // 'find' searches for a pattern and returns the position.
    cout << " 9| find(\"amp\") ok? " << found  << ", pos=" << pos << endl;
    found = ((pos=s.find("Reis"))!=string::npos);
    cout << "10| find(\"Reis\") ok? " << found << ", pos=" << pos << endl;

    found = ((pos=s.rfind("x"))!=string::npos);             // 'rfind' searches from the end.
    cout << "11| rfind(\"x\") ok? " << found << ", pos=" << pos << endl;

    string rep1{"Exam"};
    pos=s.find(rep1);
    if (pos!=string::npos)
        s.replace(pos,rep1.size(),"Sam");                   // 'replace' text in the string at a position for a given length with new text.
    cout << "12| s.replace(...), s='" << s << "'" << endl;

    string rep2{"!"};
    pos=s.find(rep2);
    if (pos!=string::npos)
        s.erase(pos,rep2.size());                           // 'erase' deletes text in the string at a position for a given length.
    cout << "13| s.erase(...), s='" << s << "'" << endl;

    s.insert(0,"XXL-");                                     // 'insert' inserts new text at a position.
    cout << "14| insert(0,\"XXL-\"), s='" << s << "'" << endl;

    s.append("s");                                          // 'append' adds text at the end.
    cout << "15| append(\"e\"), s='" << s << "'" << endl;

    return EXIT_SUCCESS;
}
