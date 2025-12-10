// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * Union Beach solution.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>
#include <memory>
#include <unordered_map>
#include <iomanip>

using std::cout, std::endl, std::ostream;
using std::string, std::string_view;
using std::unique_ptr, std::make_unique, std::make_pair;
using std::unordered_map;

class matrix {
public:
    matrix(size_t dim) : dim(dim) {}
    virtual ~matrix() {}

    virtual double at(size_t line, size_t col) const = 0;
    virtual double& at(size_t line, size_t col) = 0;
    
    virtual void make_zero() = 0;
    virtual void make_unit() {
        make_zero();
        for (size_t i=0; i<dim; ++i) {
            at(i,i)=1.0;
        }
    }

    const size_t dim;
};

class full_matrix : public matrix {
public:
    full_matrix(size_t dim) : matrix(dim), data(make_unique<double[]>(dim*dim)) {}

    virtual double at(size_t line, size_t col) const { return *(data.get()+line*dim+col); }
    virtual double& at(size_t line, size_t col) { return *(data.get()+line*dim+col); }

    virtual void make_zero() {
        double *p{data.get()},*p0{p+dim*dim};
        while (p!=p0) {
            *(p++) = 0;
        }
    }

protected:
    unique_ptr<double[]> data;
};

class sparse_matrix : public matrix {
public:
    sparse_matrix(size_t dim) : matrix(dim) {}
    
    virtual double at(size_t line, size_t col) const {
        auto it = data.find(line*dim+col);
        return (it!=data.end()) ? it->second : 0.0;
    }

    virtual double& at(size_t line, size_t col) {
        auto rc = data.emplace(make_pair(line*dim+col,0));
        return rc.first->second;
    }

    virtual void make_zero() {
        data.clear();
    }

protected:
    unordered_map<size_t,double> data;
};

ostream& operator<<(ostream& os, const matrix& M) {
        os << "[";
        for (size_t l=0; l<M.dim; ++l) {
            if (l>0) os << ",";
            os << "[";
            for (size_t c=0; c<M.dim; ++c) {
                if (c>0) os << ",";
                os << M.at(l,c);
            }
            os << "]";
        }
    return os;
}

int main() {
    cout << endl << "--- " << __FILE__ << " ---" << endl << endl;

    full_matrix M(3); 

    M.make_zero();
    cout << " 1| M: " << M << endl;
    
    M.make_unit();
    cout << " 2| M: " << M << endl;

    cout << "-----" << endl;

    sparse_matrix S(3);
    
    S.make_zero();
    cout << " 3| S: " << S << endl;

    S.make_unit();
    cout << " 4| S: " << S << endl;
   
    return EXIT_SUCCESS;
}

/*

Template solution start:

template <typename T>
class matrix {
public:
    typedef T value_type;

    matrix(size_t dim) : dim(dim) {}
    virtual ~matrix() {}

    virtual value_type at(size_t line, size_t col) const = 0;
    virtual value_type& at(size_t line, size_t col) = 0;
    [...]

template <typename T>
class full_matrix : public matrix<T> {
public:
    typedef matrix<T> matrix_type;
    typedef typename matrix<T>::value_type value_type;

    full_matrix(size_t dim) : matrix_type(dim), data(make_unique<value_type[]>(dim*dim)) {}
    [...]

*/
