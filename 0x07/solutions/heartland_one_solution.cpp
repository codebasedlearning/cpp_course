// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * Heart Land solution.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>
#include <array>

using std::cout, std::endl, std::ostream;
using std::string, std::string_view;
using std::runtime_error;
using std::array;

template <typename T, size_t DIM>
class fastvector {
    using value_type = T;

    static constexpr size_t dim = DIM;
    array<T, dim> vector;

public:
    fastvector& operator=(const value_type &val) {
        for (size_t i{0}; i < dim; ++i) {
            vector.at(i) = val;
        }
        return *this;
    }

    fastvector& operator-() {
        for (size_t i{0}; i < dim; ++i) {
            vector.at(i) *= static_cast<value_type>(-1);
        }
        return *this;
    }

    const value_type& operator[](size_t index) const { return vector.at(index); }

    value_type& operator[](size_t index) { return vector.at(index); }

    friend ostream& operator<<(ostream &os, const fastvector &fvec) {
        string delim;

        os << "<";
        for (size_t i = 0; i < dim; ++i) {
            os << delim << fvec.vector.at(i);
            delim = ", ";
        }
        os << ">";
        return os;
    }
};

template <typename T, size_t DIM>
fastvector<T, DIM> operator+(const fastvector<T, DIM> &fvec1,
                             const fastvector<T, DIM> &fvec2) {
    fastvector<T, DIM> res{};

    for (size_t i = 0; i < DIM; ++i) {
        res[i] = fvec1[i] + fvec2[i];
    }

    return res;
}

template <typename T, size_t DIM>
fastvector<T, DIM> operator-(const fastvector<T, DIM> &fvec1,
                             const fastvector<T, DIM> &fvec2) {
    fastvector<T, DIM> diff{};

    for (size_t i = 0; i < DIM; ++i) {
        diff[i] = fvec1[i] - fvec2[i];
    }

    return diff;
}

template <typename T, size_t DIM>
fastvector<T, DIM> operator*(const fastvector<T, DIM> &fvec, const T &scalar) {
    fastvector<T, DIM> res{fvec};
    for (size_t i = 0; i < DIM; ++i) {
        res[i] *= scalar;
    }

    return res;
}

template <typename T, size_t DIM>
fastvector<T, DIM> operator*(const T &scalar, const fastvector<T, DIM> &fvec) {
    fastvector<T, DIM> res{fvec};
    for (size_t i = 0; i < DIM; ++i) {
        res[i] *= scalar;
    }

    return res;
}

int main() {
    cout << "\n--- " << __FILE__ << " ---" << endl;

    fastvector<int, 4> fvec1{};
    fastvector<int, 4> fvec2{};
    fastvector<int, 4> fvec3{};

    fvec1 = 1;
    cout << " 1| fvec1 = 1: " << fvec1 << endl;

    fvec2 = 3;
    cout << " 2| fvec2 = 3: "
              << "<" << fvec2[0] << ", " << fvec2[1] << ", " << fvec2[2] << ", "
              << fvec2[3] << ">" << endl;

    fvec3 = fvec1 + fvec2;
    cout << " 3| fvec3 = fvec1 + fvec2: " << fvec3 << endl;

    fvec3 = fvec3 - fvec1;
    cout << " 4| fvec3 = fvec3 - fvec1: " << fvec3 << endl;

    fvec3 = fvec3 * 2;
    cout << " 5| fvec3 = fvec3 * 2: " << fvec3 << endl;

    fvec3 = 2 * fvec3;
    cout << " 6| fvec3 = 2 * fvec3: " << fvec3 << endl;

    -fvec3;
    cout << " 7| -fvec3: " << fvec3 << endl;

    return EXIT_SUCCESS;
}
