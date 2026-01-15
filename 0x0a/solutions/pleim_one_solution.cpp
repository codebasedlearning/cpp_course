// (C) 2025 A.Voß, a.voss@fh-aachen.de, cpp@codebasedlearning.dev

/*
 * Pleim solution.
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>
#include <functional>
#include <iomanip>
#include <vector>

using std::cout, std::endl, std::ostream;
using std::string, std::string_view;
using std::vector;
using std::function;

int main() {
    cout << endl << "--- " << __FILE__ << " ---" << endl << endl;

    constexpr int n = 4;
    vector<int> vec(n + 1);

    function<int(int, int)> binomial = [&binomial](int n, int k) -> int {
        return  (k == 0 || k == n) ? 1 : (binomial(n - 1, k - 1) + binomial(n - 1, k));
    };

    int cnt{0};
    std::ranges::generate(vec, [&]() -> int { return binomial(n, cnt++); });

    cout  << " 1| n=" << n << ", vec=[";
    std::ranges::for_each(vec, [](int i) { cout << " " << i; });
    cout << " ]" << endl;

    return EXIT_SUCCESS;
}
