// Ihr Name: A. Voß
// Matr.nr.: 1234567 a.voss@fh-aachen.de, info@codebasedlearning.dev

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <stdexcept>
#include <cstdlib>

using std::cout, std::endl, std::ostream;
using std::string;
using std::unordered_map;
using std::vector;
using std::runtime_error;

// a) 3P:
//  - je korrektem Typ 1P
// auch möglich: typedef unsigned int index_type;
using index_type = unsigned int;
using value_type = string;
using vector_type = vector<value_type>;

// b) 2P:
//  - global 0.5P,
//  - korrekter Typ 0.5P,
//  - korrekter Name 0.5P,
//  - korrekte Init. 0.5P
index_type next_id{1};

// c) 2P:
// - korrekter Rückgabetyp+keine Params 0.5P,
// - korrekter Name 0.5P,
// - korrekter Rückgabewert 0.5P,
// - nur ein Befehl mit Inkrement 0.5P
index_type make_id() { return next_id++; }

// l) 2P (viele Vorlagen)
//  - Signatur stimmt, incl. const ref. 1P
//  - Ausgabe und loop mit korrektem Komma und Größe stimmen 1P
// Loop über Index bei vector auch ok
ostream& operator<<(ostream& os, const vector_type& v) {
    bool first{true};

    os << "[";
    for (const auto &x : v) {
        if (first)
            first=false;
        else
            os << ",";
        os << "'" << x << "'";
    }
    os << "]";
    return os;
}

// d) 5P:
//  - Klasse `multi_set` 1P
//  - private Member 1P
//  - `map` korrekt in Namen und Typ: 1P
//  - `max_id` korrekt in Namen und Typ: 1P
//  - Defaultwert für max_id 1P
class multi_set {
    unordered_map<index_type,vector_type> map;
    index_type max_id{0};

public:
    // e) 4P:
    //  - ctor vorhanden 1P
    //  - member init-list 1P
    //  - explicit 2P
    // const nicht gefordert
    explicit multi_set(const index_type max_id) : max_id{max_id} {}

    // f) 16P
    //  - id mit korrektem Typ vorhanden 1P
    //  - const Ref. mit korrektem Typ verwendet 3P
    //  - Exception mit korrekter Bedingung, korrektem Typ und sinnvoller Meldung geworfen 3P
    //  - Param. Liste korrekt kopiert, dabei range-based for und auto& oder Iteratoren verwendet 4P
    //  - neuer oder veränderter Vektor geholt und eingefügt 4P
    //  - Rückgabe korrekt 1P
    // temp. Obj. beim Holen geduldet, dann Einfügen notwendig
    index_type add(index_type id, const vector_type& data ) {
        if (id>max_id)
            throw runtime_error("id too large");

        auto &set = map[id];
        // Bonus 2P: set.reserve(set.size() + data.size());
        for (auto& v:data)
            set.push_back(v);
        // oder: set.insert(set.end(), data.begin(), data.end());
        // nicht notwendig bei auto&: map[id]=set;
        return id;
    }

    // g) 2P
    //  - Funktion mit korrektem Typ (siehe f) ) verwendet 1P
    //  - `make_id()` verwendet 1P
    index_type add(const vector_type& list) { return add(make_id(),list); }

    // i) 10P:
    //  - Param. korrekt 1P
    //  - const verwendet 1P
    //  - find mit Iterator verwendet 3P
    //  - Rückgabe (end(),.second) korrekt 5P
    //  - [[nodiscard]] optional
    //  - return map[id]; funktioniert wg. const nicht
    [[nodiscard]] vector_type get(index_type id) const {
        const auto it{map.find(id)};
        return (it!=map.end()) ? it->second : vector_type{}; // or it->second
    }

    // k) 2P:
    //  - Rückgabe korrekt 1P
    //  - const verwendet 1P
    [[nodiscard]] size_t size() const { return map.size(); }

    // m) 4P:
    //  - Signatur stimmt, incl. const ref. 1P
    //  - Ausgabe korrekt (gleich Logik) 3P
    friend ostream& operator<<(ostream& os, const multi_set& s) {
        bool first{true};

        os << "(" << s.map.size() << "){";
        for (const auto &kv : s.map) {          // or structural bindings: const auto &[fst, snd]
            if (first)
                first=false;
            else
                os << ",";
            os << "" << kv.first << "->" << kv.second << "";
        }
        os << "}";
        return os;
    }
};

int main() {
    cout << "\n--- " << __FILE__ << " ---" << endl;

    // h) 4P Testcode:
    //  - Instanzen angelegt 1P
    //  - beide Varianten `add` verwendet 1P
    //  - darunter einmal mit existierendem und mit neuem Vektor 1P
    //  - Exception gefangen 1P
    const index_type max_id{200};
    multi_set set(max_id);
    index_type id1, id1a, id2;

    cout << " 1| empty set=" << set << endl;

    id1 = set.add({"Hello"});
    cout << " 2| new id1: " << id1 << ", set=" << set << endl;

    id1a = set.add(id1,{"World","!"});
    cout << " 3| old id1? " << id1a << ", set=" << set << endl;

    id2 = set.add({"a","b"});
    cout << " 4| new id2: " << id2 << ", set=" << set << endl;

    try {
        set.add(max_id+1,{"oops"});
    }
    catch (const runtime_error& e) {
        cout << " 5| add(max_id+1) failed: " << e.what() << endl;
    }

    // j) 2P Testcode:
    //  - Abfrage existierende id, unbekannte id 2P
    cout << " 6| get(id1): " << set.get(id1) << endl;
    cout << " 7| get(id2): " << set.get(id2) << endl;
    cout << " 8| get(1000): " << set.get(1000) << endl;

    // n) 2P Bonus:
    //  - Die Funktion gibt eine Referenz auf eine lokale Variable zurück (dangling reference),
    //    die nach Funktionsende zerstört ist (undefiniertes Verhalten).

    return EXIT_SUCCESS;
}
