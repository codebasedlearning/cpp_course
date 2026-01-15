// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * Demonstrates template specialization with multiple scenarios:
 *  – General template class for pairs with types
 *  – Partial specializations
 *  – Type trait specialization example
 *  – Vector template with dimension specialization
 *  – C++20 concepts for compile-time constraints
 *  – Template Meta-Programming.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>
#include <limits>
#include <type_traits>
#include <concepts>

using std::cout, std::endl, std::ostream;
using std::string, std::string_view;

void specialized_templates();
void specialized_class_info();
void specialized_vector();
void using_type_infos();
void outlook_concepts();
void template_meta_programming();

int main() {
    cout << endl << "--- " << __FILE__ << " ---" << endl << endl;

    specialized_templates();
    specialized_class_info();
    specialized_vector();
    using_type_infos();
    outlook_concepts();
    template_meta_programming();

    return EXIT_SUCCESS;
}


/*
 * A general template class pair with data types T1 and T2.
 */
template <typename T1, typename T2>
struct pair_special {
    T1 key;
    T2 value;

    pair_special(T1 t1, T2 t2) : key(t1), value(t2) {}

    friend ostream& operator<<(ostream &os, const pair_special &p) {
        os << "[" << p.key << ":" << p.value << "] <T1,T2>";
        return os;
    }
};

/*
 * A specialization, i.e. for the case that the first parameter is an int, the compiler 
 * takes this class.
 * 
 * For the template parameters, only the "free" types are available, or, if everything
 * is specified, none (template <>) is left.
 */
template <typename T2>
struct pair_special<int,T2> {
    long key;
    T2 value;

    friend ostream& operator<<(ostream& os, const pair_special& p) {
        os << "[" << p.key << ":" << p.value << "] <int,T2>";
        return os;
    }
};

/*
 * Another specialization for the case that both data types are match (T1=T2).
 */
template <typename T1>
struct pair_special<T1,T1> {
    T1 key;
    T1 value;

    friend ostream& operator<<(ostream& os, const pair_special& p) {
        os << "[" << p.key << ":" << p.value << "] <T1,T1>";
        return os;
    }
};

/*
 * Another specialisation for the case that both data types are of type int.
 */
template <>
struct pair_special<int,int> {
    long key;
    int value;

    friend ostream& operator<<(ostream& os, const pair_special& p) {
        os << "[" << p.key << ":" << p.value << "] <int,int>";
        return os;
    }
};

/*
 * Another specialization for the case that both data types are of the type bool.
 */
template <>
struct pair_special<bool,bool> {
    int n;

    pair_special(bool b1, bool b2) : n( ((b1)?1:0) + ((b2)?2:0) ) {}

    friend ostream& operator<<(ostream& os, const pair_special& p) {
        os << "[" << (p.n&1) << ":" << (p.n>>1) << "] <bool,bool>";
        return os;
    }
};

void specialized_templates() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    pair_special<short,int> ps1{1u,2};
    cout << " 1| ps1=" << ps1 << endl;

    // The data types can also be derived automatically. The editor helps to choose between the specializations.
    pair_special ps2{3u,4};
    cout << " 2| ps2=" << ps2 << endl;

    pair_special<int,double> ps3{2,3.4};
    cout << " 3| ps3=" << ps3 << endl;

    pair_special<float,float> ps4{5.1f,6.2f};
    cout << " 4| ps4=" << ps4 << endl;

    pair_special ps5{23,42};
    cout << " 5| ps5=" << ps5 << endl;

    pair_special<bool,bool> ps6{true,false};
    cout << " 6| ps6=" << ps6 << endl;
}

/*
 * Templates for some type-info, cf. std::numeric_limits.
 */
template <typename T>
struct type_special {
    static constexpr bool is_specialized = false;
    static constexpr size_t size() noexcept { return sizeof(T); }
};

template <>
struct type_special<bool> {
    static constexpr bool is_specialized = true;
    static constexpr double size() noexcept { return 1.0/8.0;; }
};

void specialized_class_info() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    cout << " 1| int::min=" << std::numeric_limits<int>::min() << endl;
    cout << " 2| int::max=" << std::numeric_limits<int>::max() << endl;
    cout << " 3| double::eps=" << std::numeric_limits<double>::epsilon() << endl;

    cout << " 4| int::size=" << type_special<int>::size() << endl;
    cout << " 5| double::size=" << type_special<double>::size() << endl;
    cout << " 6| bool::size=" << type_special<bool>::size() << endl;
}

/*
 * A simple (incomplete) vector template with specialization for dim=1.
 */
template <typename T, int DIM>
struct vector_special {
    static constexpr size_t dim = DIM;
    T data[dim];

    T operator[](int i) const { return data[i]; }
    T& operator[](int i) { return data[i]; }

    template <typename S>
    vector_special& operator=(const vector_special<S,DIM> & v) {
        for (size_t i=0; i<dim; ++i)
            data[i] = (T)(v.data[i]);
        return *this;
    }
};

template <typename T>
struct vector_special<T,1> {
    static constexpr size_t dim = 1;
    T data;

    T operator[](int) const { return data; }
    T& operator[](int) { return data; }
};

/*
 * Template for a 3D vector specialization – a sort of generic typedef.
 */
template<class T>
using vector_special3d = vector_special<T,3>;

void specialized_vector() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    vector_special<int,3> v3{1,2,3};
    vector_special<int,1> v1{4};

    cout << " 1| size(v3)=" << sizeof(v3) << ", v3[0]=" << v3[0] << endl;
    cout << " 2| size(v1)=" << sizeof(v1) << ", v1[0]=" << v1[0] << endl;

    vector_special<double,3> d3{};

    d3 = v3;                                // Why does it work?
    cout << " 3| size(d3)=" << sizeof(d3) << ", d3[0]=" << d3[0] << endl;

    // v3 = v1;

    vector_special3d<char> c3{'a','b','c'};
    cout << " 4| size(c3)=" << sizeof(c3) << ", c3[0]='" << c3[0] << "'" << endl;
}


/*
 * We want to specialize a collection class for pointer types - only the idea.
 */

template <typename T>
struct is_T_pointer {
    static constexpr bool value = false;    // or static const bool value
};

template <typename T>
struct is_T_pointer<T*> {
    static constexpr bool value = true;
};

template <typename T>
inline constexpr bool is_T_pointer_v = is_T_pointer<T>::value;

template <typename T, bool isptr>
struct the_collection {
    friend ostream& operator<<(ostream& os, const the_collection&) {
        os << "non-pointer-collection";
        return os;
    }
};

template <typename T>
struct the_collection<T,true> {
    friend ostream& operator<<(ostream& os, const the_collection&) {
        os << "pointer-collection";
        return os;
    }
};

template<typename T>
using collection = the_collection<T,is_T_pointer_v<T>>;                 // or: is_T_pointer<T>::value

template <typename T>
struct only_integral {
    static_assert(std::is_integral<T>::value && std::is_unsigned_v<T>); // or is_integral_v
};

/*
 * 'static_assert' is a compile-time check. If the condition inside the parentheses
 * is false, the code will fail to compile with an error message.
 * It doesn't cost anything at runtime.
 */
void using_type_infos() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    cout << " 1| int=ptr ? " << is_T_pointer<int>::value << endl;
    cout << " 2| int=ptr ? " << is_T_pointer_v<int> << endl;
    cout << " 3| int*=ptr ? " << is_T_pointer<int*>::value << endl;
    cout << " 4| int*=ptr ? " << is_T_pointer_v<int*> << endl << endl;

    collection<double> c1;
    collection<double*> c2;
    cout << " 5| type c1 ? " << c1 << endl;
    cout << " 6| type c2 ? " << c2 << endl;

    only_integral<unsigned int> i1;
    only_integral<unsigned long> i2;
    // only_integral<float> i3;
    // only_integral<int> i4;
    // only_integral<ostream> i5;
}


/*
 * A generic function that refuses to compile if you try to use it with a type T that 
 * is "smaller" than a standard int.
 */
template <typename T>
T calc_hash_value_v1() {
    static_assert(type_special<T>::size() >= sizeof(int));
    // [...]
    return T{};
}

/*
 * Version 2 with C++20 Concepts. It allows you to define requirements that a type must meet 
 * before it can be used with a template.
 * 
 * concept AtLeastIntSized: This defines a named requirement.
 * 
 * Why use this?
 *  – Better Error Messages than cryptic template instantiation errors.
 *  – Overloading: One can provide different versions of calc_hash_value_v2 for different concepts.
 */
template <typename T>
concept AtLeastIntSized = (type_special<T>::size() >= sizeof(int));

template <typename T>
requires AtLeastIntSized<T>                 // can also be an expression with more than one condition
T calc_hash_value_v2() {
    // [...]
    return T{};
}

template <AtLeastIntSized T>                // syntactic sugar for the 'requires' form
T calc_hash_value_v3() {
    // [...]
    return T{};
}

/*
 * This is indeed a function template as before.
 * Using 'auto' in a function parameter list is a feature called 'Abbreviated Function Templates'.
 */
void calc_hash_value_v4(AtLeastIntSized auto x) {
    // [...]
}

void outlook_concepts() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    const auto h1 = calc_hash_value_v1<int>();
    cout << " 1| h1=" << h1 << endl;
    const auto h2 = calc_hash_value_v1<long>();
    cout << " 2| h2=" << h2 << endl;

    //const auto h3 = calc_hash_value_v1<int8_t>();
    //const auto h3 = calc_hash_value_v2<int8_t>();
    //const auto h3 = calc_hash_value_v3<int8_t>();
    //cout << " 3| h3=" << h3 << endl;

    calc_hash_value_v4(4);
    // calc_hash_value_v4(int8_t(0));
}


/*
 * Template Meta-programming.
 */

template <int N>
struct fib {
    static constexpr int value=fib<N-1>::value + fib<N-2>::value;
};

template <>
struct fib<1> {
    static constexpr int value=1;           // or static const int value;
};

template <>
struct fib<0> {
    static constexpr int value=0;
};

void template_meta_programming() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    cout << " 1| fib={1,1,2,3,5,8,13,21,...}" << endl;

    cout << " 2| fib(1)=" << fib<1>::value << endl;
    cout << " 3| fib(5)=" << fib<5>::value << endl;
    cout << " 4| fib(8)=" << fib<8>::value << endl;
}
