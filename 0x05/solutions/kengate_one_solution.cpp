// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * Kengate solution.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>

using std::cout, std::endl, std::ostream;
using std::string, std::string_view;

bool divmod(const int n, const int p, int *pdiv, int *pmod) {
    if (p!=0) {
        *pdiv = n / p;
        *pmod = n % p;
        return true;
    } else {
        *pdiv = *pmod = 0;
        return false;
    }
}

int main() {
    cout << "\n--- " << __FILE__ << " ---" << endl;

    int n,p,d,m;
    bool ok;

    n=17; p=5; ok = divmod(n,p,&d,&m);
    cout << " 1| " << n << "/" << p << " -> d=" << d << ", m=" << m
         << ", ok=" << ok << ", check: " << d*p+m << endl;

    n=23; p=0; ok = divmod(n,p,&d,&m);
    cout << " 2| " << n << "/" << p << " -> d=" << d << ", m=" << m
         << ", ok=" << ok << endl;

    return EXIT_SUCCESS;
}
