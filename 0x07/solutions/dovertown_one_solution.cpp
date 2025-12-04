// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * Dover Town solution.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>
#include <memory>
#include <vector>

using std::cout, std::endl, std::ostream;
using std::string, std::string_view;
using std::vector;
using std::runtime_error;

class states {
    vector<string> values;
    size_t current{0};

public:
    states() = default;
    ~states() = default;

    states& operator+=(const string &state) {
        values.push_back(state);
        return *this;
    }

    states& operator=(size_t index) {
        if (index >= values.size()) {
            throw runtime_error("index too big");
        }
        current = index;
        return *this;
    }

    states& operator++() {
        if (values.empty()) {
            throw runtime_error("no states");
        }

        if (current == (values.size() - 1)) {
            current = 0;
        } else {
            ++current;
        }

        return *this;
    }

    states& operator--() {
        if (values.empty()) {
            throw runtime_error("no states");
        }

        if (current == 0) {
            current = values.size() - 1;
        } else {
            --current;
        }

        return *this;
    }

    size_t operator()() const { return current; }

    string& operator[](const size_t index) {
        if (index >= values.size()) {
            throw runtime_error("index too big");
        }
        return values[index];
    }

    void clear() {
        values.clear();
        current = 0;
    }

    friend ostream &operator<<(ostream &os, const states &stat) {
        string delim;

        os << "[";
        for (auto const &x : stat.values) {
            os << delim << x;
            delim = ", ";
        }
        os << "]";
        return os;
    }
};

int main() {
    cout << "\n--- " << __FILE__ << " ---" << endl;

    states stat;

    cout << " 1| states: " << stat << endl;

    stat += "unknown";
    cout << " 2| states: " << stat << endl;

    stat += "connected";
    stat += "disconnected";
    cout << " 3| states: " << stat << endl;

    cout << " 4| current: " << stat[stat()] << ", " << stat << endl;

    stat = 1;
    cout << " 5| current: " << stat[stat()] << ", " << stat << endl;

    ++stat;
    cout << " 6| current: " << stat[stat()] << ", " << stat << endl;

    ++stat;
    cout << " 7| current: " << stat[stat()] << ", " << stat << endl;

    --stat;
    cout << " 8| current: " << stat[stat()] << ", " << stat << endl;

    stat.clear();
    cout << " 9| states: " << stat << endl;

    return EXIT_SUCCESS;
}
