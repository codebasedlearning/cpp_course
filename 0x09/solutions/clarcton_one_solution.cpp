// (C) 2025 A.Voß, a.voss@fh-aachen.de, cpp@codebasedlearning.dev

/*
 * Clarcton solution.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>
#include <iomanip>
#include <sstream>
#include <map>

using std::cout, std::endl, std::ostream;
using std::string, std::string_view;

int main() {
    cout << endl << "--- " << __FILE__ << " ---" << endl << endl;

    std::stringstream input(
R"(
  api_key = 123456
  user = John
)");
    std::map<std::string, std::string> result;
    std::string line;

    auto trim = [](std::string& s) {
        auto not_space = [](unsigned char c) { return !std::isspace(c); };
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), not_space));
        s.erase(std::find_if(s.rbegin(), s.rend(), not_space).base(), s.end());
    };

    while (std::getline(input, line)) {
        auto eq = line.find('=');
        if (eq == std::string::npos) continue;
        auto k = line.substr(0, eq);
        auto v = line.substr(eq + 1);
        trim(k); trim(v);
        result[k] = v;
    }

    cout << " 1| size=" << result.size() << endl;
    cout << " 2|";
    for (const auto& kv : result)
        cout << " (" << kv.first << "," << kv.second << ")";
    cout << endl;

    return EXIT_SUCCESS;
}
