// Ihr Name: A. Voß
// Matr.nr.: 1234567 a.voss@fh-aachen.de, info@codebasedlearning.dev

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <stdexcept>
#include <cstdlib>
#include <sstream>
#include <string_view>

using std::cout, std::endl, std::ostream;
using std::string;
using std::unordered_map;
using std::vector;
using std::runtime_error;

// A1

class config {
    // A1.a) 1P:
    // - Attribut mit korrektem Typ und Namen
    string file_name_;

public:
    // A1.a) 1P:
    // - Default-ctor
    // alternativ 'config() {}' ist auch in Ordnung und gibt keinen Abzug
    config() = default;

    // A1.b) 3P:
    // - Setter-Funktionalität 1P
    // - const ref& für string Parameter 1P
    // - config& als Rückgabe 1P
    config& file_name(const string &s) {
        file_name_ = s;
        return *this;
    }

    // A1.b) 2P:
    // - Getter-Funktionalität 1P
    // - const in Signatur 1P
    // [[nodiscard]] ist nicht verlangt
    [[nodiscard]] const string& file_name() const { return file_name_; }

    // A1.b) 3P:
    // - Ausgabeoperator-Funktionalität 1P
    // - const ref& für config Parameter 1P
    // - 'friend' in der Klasse genutzt 1P
    friend ostream& operator<<(ostream &os, const config &cfg) {
        os << cfg.file_name();
        return os;
    }
};

// A2

// A2.a) 2P:
// - Typdefinition 2P
// alternativ 'typedef vector<int> vector_t;' ist auch in Ordnung und gibt keinen Abzug
using vector_t = vector<int>;

// A2.b) 4P:
// - Basisklasse mit rein virtuellen Funktionen input,process,output 2P
// - IPO& als Rückgabe 1P
// - virtueller Destruktor 1P
// alternativ 'struct' statt 'class' ist auch in Ordnung und gibt keinen Abzug (Interface-Idee)
class IPO {
public:
    virtual IPO& input() = 0;
    virtual IPO& process() = 0;
    virtual IPO& output() = 0;

    virtual ~IPO() = default;
};

// A2.c) 1P:
// - IHK öffentlich abgeleitet 1P
class IHK : public IPO {
    // A2.d) 1P:
    // - privates Attribut cfg_
    config cfg_;

public:
    // A2.d) 1P:
    // - ctor mit const& config 1P
    // 'explicit' ist nicht verlangt
    explicit IHK(const config & config) : cfg_(config) {}

protected:
    // A2.e) 3P:
    // - protected verwendet 1P
    // - Attribute input_data_ vom Typ vector_t 1P
    // - Attribute output_data_ vom Typ vector_t 1P
    vector_t input_data_;
    vector_t output_data_;

public:

    // A2.f) 4P:
    // - korrektes Überführen der Zahlen in den Vektor input_data_ 4P
    IPO& input() override {
        input_data_.clear();
        std::stringstream data{string("1 3 10 2 2")};

        int x;
        while (data >> x) {
            input_data_.push_back(x);
        }
        return *this;
    }
    // A2.g) 2P:
    // - quadrieren der Werte zu output_data_ 2P
    IPO & process() override {
        output_data_.clear();
        output_data_.reserve(input_data_.size());
        for (const auto x : input_data_)
            output_data_.push_back(x*x);
        return *this;
    }

    // A2.h) 2P:
    // - Ausgabe in der Form `[y0,y1,…,y_size-1]` 2P
    IPO & output() override {
        std::string_view sv{};
        cout << "[";
        for (const auto &x : output_data_) {
            cout << sv << x; sv = ",";
        }
        cout << "]" << endl;
        return *this;
    }
};

// A3

// A3.a) 1P:
// - Klasse clever_ptr angelegt 1P
class clever_ptr {

    // A3.a) 2P:
    // - raw ptr p mit korrektem Typ angelegt und initialisiert 2P
    int *p_{nullptr};

public:
    // A3.b) 2P:
    // - Member-Initializer-List verwendet 1P
    // - new verwendet und initialisiert 1P
    // explicit ist nicht verlangt
    explicit clever_ptr(const int n): p_(new int(n)) {}

    // A3.b) 1P:
    // - Destruktor gibt Speicher frei 1P
    ~clever_ptr() { delete p_; }

    // A3.c) 1P:
    // - copy-ctor gelöscht 1P
    clever_ptr(const clever_ptr &) = delete;

    // A3.d) 2P:
    // - korrekte Rückgabe mit int& 2P
    // [[nodiscard]] ist nicht verlangt
    [[nodiscard]] const int& get() const { return *p_; }

    // A3.e) 1P
    // - korrekte Implementierung 1P
    // [[nodiscard]] ist nicht verlangt
    [[nodiscard]] const int& operator*() const { return get(); }
};

int main() {
    cout << "\n--- " << __FILE__ << " ---" << endl;

    // A1, Ausgabe: "cfg={'data.txt'}, filename='data.txt'"
    const auto name = "data.txt";
    const auto cfg = config().file_name(name);
    cout << "cfg={'" << cfg << "'}, filename='" << cfg.file_name() << "'" << endl;

    // A2, Ausgabe: "[1,9,100,4,4]"
    IHK(config().file_name("file")).input().process().output();

    // A3, Ausgabe: "cp.get()=42, *cp=42"
    const auto cp = clever_ptr(42);
    cout << "cp.get()=" << cp.get() << ", *cp=" << *cp << endl;

    return EXIT_SUCCESS;
}
