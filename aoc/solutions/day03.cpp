// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * AoC Day 03 solution.
 */

#include "aoc.hpp"

namespace {
    constexpr std::array examples =  {
R"(
987654321111111
811111111111119
234234234234278
818181911112111
)"
    };
}

/*
 * Basically a 'pick the lexicographically largest subsequence of length digits'.
 *
 * Btw. in non-optimized mode 'const string& line' needs far more time, but with
 * e.g. '-O3' (see CMakeList) string& and string_view have similar execution speed.
 */

constexpr int64_t calcJoltage(const string_view line, const size_t digits) {
    size_t pos{0};          // just for readability, one can solve this with first and it only
    int64_t result{0};      // instead of collecting chars
    for (size_t j=1; j<=digits; ++j) {
        const auto first = line.begin() + pos;
        const auto last  = line.begin() + (line.size() - (digits - j)); // except the remaining digits
        const auto it = std::ranges::max_element(first, last);

        // The hand-woven-loop below needs about twice the time than the std-max-version above (on my computer)...wow!
        // for (size_t i = pos; i < line.size()-(digits-j); ++i)
        //    if (line[i] > line[pos]) pos=i;
        result = result * 10 + (*it-'0');               // this is: line[pos]
        pos = std::distance(line.begin(), it) + 1;
    }
    return result;
}

aoc::solutions solve(std::ranges::input_range auto&& lines) {
    int64_t sum1{0};
    int64_t sum2{0};
    for (const auto &line : lines) {
        sum1 += calcJoltage(line, 2);
        sum2 += calcJoltage(line, 12);
    }
    return {sum1, sum2};
}

int main() {
    println("\n--- {} ---\n", __FILE__);

    constexpr auto day = 3;
    constexpr auto example = -1;
    aoc::println(day, example);

    const auto input = (example >= 0) ? aoc::Input::of(examples[example]) : aoc::Input::of(day);
    auto lines = input | aoc::as_std_lines;

    auto [answer, ms] = aoc::measure([&] { return solve(lines); });
    aoc::println(answer, ms);

    // 17144 (357), 170371185255900 (3121910778619)
    if constexpr (example==-1) { assert(answer.part1==17144 && answer.part2==170371185255900); } // 0.05ms
    if constexpr (example==0) { assert(answer.part1==357 && answer.part2==3121910778619); }

    return EXIT_SUCCESS;
}
