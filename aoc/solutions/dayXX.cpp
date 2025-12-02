// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * AoC Day xx solution.
 */

#include "prep.cpp"

constexpr array examples =  {
    R"(
123
)"
};

void solve(const lines_t &lines) {
    println("-> part 1: {}", 0);
    println("-> part 2: {}", 0);
}

int main() {
    println("\n--- {} ---", __FILE__);

    constexpr auto day = 0;
    constexpr auto example = 1;

    const auto blocks = (example > 0) ? exampleInput(examples[example - 1]) : puzzleInput(day);
    const auto &lines = blocks[0];

    print("{}", stats(day, example, lines.size()));

    // sol-part1 (example-part1), sol-part2 (example-part2)
    auto ms = measure([&] {
        solve(lines);
    });
    println("[{:.2f} ms]", ms);

    return EXIT_SUCCESS;
}
