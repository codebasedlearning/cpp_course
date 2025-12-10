// (C) A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

#ifndef AOC_CONVERSIONS
#define AOC_CONVERSIONS

#include "aoc_uses.hpp"

namespace aoc {

    // like the adapters

    template<typename T>
    T to_number(const string_view sv) {
        T value{};
        if (auto [p, ec] = std::from_chars(sv.data(), sv.data() + sv.size(), value); ec != std::errc() || p != sv.end())
            throw std::runtime_error(format("Invalid number: {}", sv));
        return value;
    }

    // template <class T>
    // T to_number(const std::string& s) {
    //     return to_number<T>(std::string_view{s});
    // }

    template<typename T>
    string to_string(const T x) {
        return format("{}", x);
    }

    template<typename T>
    std::vector<T> to_numbers(const string_view line) {
        std::istringstream iss{string(line)};
        std::vector<T> values;
        T x;
        while (iss >> x) {   // operator>> automatically skips whitespace
            values.push_back(x);
        }
        return values;
    }

}
#endif // AOC_CONVERSIONS
