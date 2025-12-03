// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * AoC Day 03 solution.
 */

#include "prep.cpp"

constexpr array examples =  {
    R"(
987654321111111
811111111111119
234234234234278
818181911112111
)"
};

/*
 * Basically a 'pick the lexicographically largest subsequence of length digits'.
 *
 * Btw. in non-optimized mode 'const string& line' needs far more time, but with
 * e.g. '-O3' (see CMakeList) string& and string_view have similar execution speed.
 */

int64_t calcJoltage(const string_view line, const size_t digits) {
    size_t picked{0};
    int64_t result{0};
    for (size_t j=1; j<=digits; ++j) {
        const auto first = line.begin() + picked;
        const auto last  = line.begin() + (line.size() - (digits - j));
        const auto it = std::ranges::max_element(first, last);
        picked = std::distance(line.begin(), it);

        // The hand-woven-loop below needs about twice the time than the std-max-version above (on my computer)...wow!
        // for (size_t i = picked; i < line.size()-(digits-j); ++i) // except the remaining digits
        //    if (line[i] > line[picked]) picked=i;
        result = result * 10 + (line[picked]-'0');                  // instead of string-ops
        ++picked;
    }
    return result;
}

void solve(const lines_t &lines) {
    int64_t sum1{0};
    int64_t sum2{0};
    for (const auto &line : lines) {
        sum1 += calcJoltage(line, 2);
        sum2 += calcJoltage(line, 12);
    }
    println("-> part 1: {} (2-Joltage)", sum1);
    println("-> part 2: {} (12-Joltage)", sum2);
}

int main() {
    println("\n--- {} ---", __FILE__);

    constexpr auto day = 3;
    constexpr auto example = 0;

    const auto blocks = (example > 0) ? exampleInput(examples[example - 1]) : puzzleInput(day);
    const auto &lines = blocks[0];

    print("{}", stats(day, example, lines.size()));

    // 17144 (357), 170371185255900 (3121910778619)
    auto ms = measure([&] {
        solve(lines);
    });
    println("[{:.2f} ms]", ms);

    return EXIT_SUCCESS;
}
