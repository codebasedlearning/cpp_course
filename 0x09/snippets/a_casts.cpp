// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * Demonstrates type casting mechanisms:
 *  – Implicit conversions and narrowing
 *  – C-style casts vs static_cast
 *  – Explicit constructors and conversion operators
 *  – dynamic_cast for polymorphic types
 *  – reinterpret_cast for low-level pointer manipulation
 *  – const_cast for removing const qualifiers
 *
 * In general: There are countless cases of type change, so we can only discuss a few here.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>

using std::cout, std::endl;
using std::string, std::string_view;

void check_conversion();
void check_conversion_AB();
void check_dynamic();
void check_reinterpret_cast();
void check_const_cast();

int main() {
    cout << endl << "--- " << __FILE__ << " ---" << endl << endl;

    check_conversion();
    check_conversion_AB();
    check_dynamic();
    check_reinterpret_cast();
    check_const_cast();

    return EXIT_SUCCESS;
}

void check_conversion() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    {
        int n{23};
        long l = n;                         // ok?
        cout << " 1| l=" << l << endl;

        /*
         * Didactic break
         *
         * The integer fits into the long without any loss of precision - so no problem. See
         * Implicit type conversion:
         *      https://en.cppreference.com/w/cpp/language/implicit_conversion
         */
    }

    {
        int n{-5};
        unsigned long l = n;                // ok?
        // unsigned long m{n};              // ok?
        cout << " 2| l=" << l << endl;

        /*
         * Didactic break
         *
         * -5 in two-complement hexadecimal reads 0xFFFFFFFFFFFFFFFFFB, and that is 18446744073709551611
         * as a sign-less long. So be careful when switching between signed and unsigned numbers,
         * otherwise 'narrowing conversion'.
         */
    }

    {
        long l{123};
        int n = l;                          // ok?
        // int n{l};
        cout << " 3| n=" << n << endl;

        /*
         * Didactic break
         *
         * Here the type with the higher precision is converted to a data type with lower precision,
         * i.e. there may be data loss (narrowing conversion). Depending on the compiler and settings,
         * this may give a warning.
         *
         * With the general initialisation, the narrowing conversion results in an error, thus this
         * is not considered a problem, but a desired feature to make this implicit conversion is noticed.
         *
         * There is a further rule that the narrowing conversion applies only to non-const expressions.
         * In other words, for constant expressions, the conversion can be done directly, and then the
         * compiler will see if it fits or not.
         */
    }

    {
        long n;
        n = 3.14;                           // warning 1
        n = (long)3.14;                     // warning 2
        n = static_cast<long>(3.14);        // ok
        cout << " 4| n=" << n <<  endl;

        /*
         * So-called C-style expression, cf. example before. Here it is tried to transform
         * the expression according to a rule set:
         *      https://en.cppreference.com/w/cpp/language/explicit_cast
         *
         * The compiler is allowed to try this here, because the explicit cast '(type)'
         * tells the compiler that no implicit and possibly unconscious conversion is
         * taking place, but that it is the explicit wish of the programmer to do so
         * -> personal responsibility.
         *
         * But static_cast has limits, what does not fit does not work.
         *       https://en.cppreference.com/w/cpp/language/static_cast
         */
    }
}

void check_conversion_AB() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    struct A {
        int n;
        A(int n) : n{n} {}
    };

    {
        A a1(1);
        A a2 = 2;
        a2 = 2;                             // What happens here?
        A a3{3};

        /*
         * Didactic break
         *
         * The compiler tries to convert the type as best it can, using all sorts of conversions.
         * If you want to limit this automatic behaviour, 'explicit' can be used to prevent it.
         */
    }

    struct B {
        int n;
        explicit B(int n) : n{n} {}         // 'explicit'!

        operator A() const { return A{n}; } // use 'explicit'
    };

    {
        B b1(1);
        // B b2 = 2;
        // b2 = 2;                          // What happens now?
        B b3{3};

        A ab = b1;                          // It is not limited to primitive types.

        cout << " 1| ab.n=" << ab.n <<  endl;
    }
}

void check_dynamic() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    struct A {
        int n{23};
    };

    struct B: A {
        int m;
        explicit B(const int m) : m{m} {}
    };

    {
        A a{};
        B b{42};
        cout << " 1| b.n=" << b.n <<  ", b.m=" << b.m << endl;

        A &ar = b;                          // ok?
        // B &br = a;                       // why not?
        // B &br = ar;                      // why not?

        B &br = static_cast<B&>(a);         // ok?
        cout << " 2| br.n=" << br.n <<  ", br.m=" << br.m << endl;

        B &ba = static_cast<B&>(ar);        // ok?
        cout << " 3| ba.n=" << ba.n <<  ", ba.m=" << ba.m << endl;

        /*
         * Didactic break
         *
         * Base-to-derived conversions (downcasts) using static_cast make no runtime checks
         * to ensure that the dynamic type of the pointed/referred object is Derived, and
         * may only be used safely if this precondition is guaranteed by other means.
         */
    }

    struct C {
        virtual ~C() = default;
    };

    struct D: C {
        void f() {}
    };

    {
        C *pc = new C;
        D *p = dynamic_cast<D*>(pc);
        cout << " 4| p=" << p << endl;    // no exception, just nullptr
        delete pc;

        C* pd = new D;
        if (D *dd = dynamic_cast<D*>(pd)) {
            cout << " 5| dd=" << dd << endl;
            dd->f();
        }
        delete pd;

        /*
         * Here a dynamic_cast is the first choice and will result in a nullptr if is not
         * possible at runtime. The program can only determine this at runtime, if information
         * about the type of the pointer is available and this is only possible if there are
         * virtual functions in the class - otherwise is just a pointer.
         *      https://en.cppreference.com/w/cpp/language/dynamic_cast
         *
         * Note, this also holds for references.
         */
    }
}

void check_reinterpret_cast() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    struct X {
        int x;
    };

    struct Y {                              // same structure as X
        int y;
        void f() {}
    };

    {
        X x{};
        auto py = reinterpret_cast<Y*>(&x);
        py->y = 13;
        cout << " 1| x.x=" << x.x << ", py->y=" << py->y << endl;

        auto y = reinterpret_cast<Y&>(x);
        y.y = 42;
        cout << " 2| x.x=" << x.x << ", y.y=" << y.y << endl;

        /*
         * Technically, a pointer is just a pointer, and here we use the address of x as
         * a pointer to an Y element, hoping that Y's memory layout is identical to X's
         * - this is not legal and UB, even if it seems to work.
         *
         * Apart from that, any change to X and/or Y can lead to (more) incorrect code,
         * even if our assumption about the layout is correct
         *       https://en.cppreference.com/w/cpp/language/reinterpret_cast
         *
         * Both casts "work" only in the sense that they compile. In terms of the C++ object
         * model, both are undefined behavior (UB) as soon as you access y. The pointer case
         * doesn't actually work more legally than the reference case — it just tends to fail
         * less obviously.
         *
         * If you want a safe "bit-cast" we have std::bit_cast from C++20 — but only for
         * trivially copyable types, and you still get a new object, not aliasing.
         */
    }

    {
        int n{0x12345678};                  // assume sizeof(int) == 4
        auto *p = reinterpret_cast<unsigned char*>(&n);

        if (*p == 0x78)                     // checks byte order
            cout << " 3| little-endian" << endl;
        else
            cout << " 4| big-endian" << endl;

        /*
         * Special rule: An object may always be accessed via char, unsigned char,
         * or std::byte.
         */
    }
}

void check_const_cast() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    int n{23};
    const int &rn = n;
    const_cast<int&>(rn) = 24;
    cout << " 1| n=" << n << endl;

    const int m{42};
    const int &rm = m;
    const_cast<int&>(rm) = 43;
    cout << " 2| m=" << m << endl;

    /*
     * const_cast takes the 'const' away and allows to change const expressions. Note,
     * however, that n is not a constant (!), so this works and is well defined.
     *
     * m, on the other hand, is (perhaps) also changed, but output still gives 42, because
     * the compiler assumes that m does not change and in this case, casting away const and
     * writing through it is undefined behavior.
     *
     * So be careful when removing const, this is usually more of a code smell and may lead
     * to wrong results - not to mention that e.g. a const-& in a signature assures the caller
     * that the instance remains unchanged
     *      https://en.cppreference.com/w/cpp/language/const_cast
     */
}
