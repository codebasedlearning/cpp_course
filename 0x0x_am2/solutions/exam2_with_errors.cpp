// Ihr Name: A. Voß
// Matr.nr.: 1234567 a.voss@fh-aachen.de, info@codebasedlearning.dev

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <stdexcept>
#include <cstdlib>
#include <sstream>

using std::cout, std::endl, std::ostream;
using std::string;
using std::unordered_map;
using std::vector;
using std::runtime_error;

// A1

class config {
    string file_name;       ///!!!

public:
    config() {}

    config file_name(const string s) { ///!!!
        //file_name_ = s;  ///!!!
        return *this;
    }

    const string& file_name() { return file_name_; } ///!!!

    friend ostream& operator<<(ostream &os, const config &cfg) {
        // os << cfg.file_name();  ///!!!
        return os;
    }
};

// A2

typedef vector<long> vector_t;    ///!!!

class IPO {
public:
    virtual IPO& input() = 0;
    virtual IPO& process() = 0; ///!!!

    ///!!!
};

class IHK : protected IPO { ///!!!
    config cfg_;

public:
    explicit IHK(const config & config) : cfg_(config) {}

protected:
    vector_t input_data_; ///!!!

public:
    IPO& input() override {
        std::stringstream data{string("11 3 10 2 22")}; ///!!!
        string_view number;  ///!!!
        do {
            data >> number;
            input_data_.push_back(stoi(number));
        } while (!data.eof());
        return *this;
    }

    IPO & process() override {
        for (const auto &x : input_data_)
            output_data_.push_back(x*2);  ///!!!
        return *this;
    }

    ///!!!
};

// A3

class clever_ptr {
    int-ptr *p;  ///!!!

///!!!
    explicit clever_ptr(const int n): p(int(n)) {}  ///!!!

    ~clever_ptr() { delete [] p; }  ///!!!

    clever_ptr(const clever_ptr &) = default;  ///!!!

    [[nodiscard]] int& get() const { return *p; }

    ///!!!
};

int main() {
    cout << "\n--- " << __FILE__ << " ---" << endl;


    return EXIT_SUCCESS;
}
