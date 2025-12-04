// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * AoC Day xx solution.
 */

#include "aoc.h"

namespace {
    constexpr array examples =  {
        R"(
123
)"
    };
}

solutions solve(const Lines &lines) {
    return {1,2};
}

int main() {
    println("\n--- {} ---\n", __FILE__);

    constexpr auto day = 0;
    constexpr auto example = 1;

    // const auto blocks = (example > 0) ? toBlocks(examples[example - 1]) : toBlocks(day);
    // const auto &lines = blocks[0];

    const auto lines = (example > 0) ? toLines(examples[example - 1]) : toLines(day);
    print(day, example, lines.size());

    auto [answer, ms] = measure([&] { return solve(lines); });
    print(answer, ms);

    // 1 (0), 2 (0)
    if constexpr (example==0) { assert(answer.part1==1 && answer.part2==2); }

    return EXIT_SUCCESS;
}
