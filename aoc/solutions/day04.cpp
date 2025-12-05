// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * AoC Day 04 solution.
 */

#include "aoc.h"

namespace {
    constexpr array examples =  {
        R"(
..@@.@@@@.
@@@.@.@.@@
@@@@@.@.@@
@.@@@@..@.
@@.@@@@.@@
.@@@@@@@.@
.@.@.@.@@@
@.@@@.@@@@
.@@@@@@@@.
@.@.@@@.@.
)"
    };
}

solutions solve(const Lines &lines) {
    auto field = toField(lines);

    int64_t sum1{0};
    int64_t sum2{0};

    // collect all positions
    auto papers = std::ranges::to<unordered_set<RC>>(
        positions(field)
        | std::views::filter([&](const RC rc) { return field[rc] == '@'; })
    );

    // abort if too long
    for (size_t loop=0; loop<1000; ++loop) {
        auto neighbor_count = [&](const RC rc) {
            return std::ranges::count_if( halo(field, rc),
                [&](const RC cell) { return field[cell] == '@'; }
            );
        };

        // reduce papers
        auto toLift = std::ranges::to<std::unordered_set<RC>>(
            papers
            | std::views::filter([&](const RC rc) { return neighbor_count(rc) < 4; })
        );

        if (loop==0) { sum1 = toLift.size(); }
        sum2 += toLift.size();

        if (toLift.empty())
            break;

        for (const auto &rc : toLift) {
            papers.erase(rc);
            field[rc] = '.';
        }
    }
    return {sum1, sum2};
}

int main() {
    println("\n--- {} ---\n", __FILE__);

    constexpr auto day = 4;
    constexpr auto example = 0;

    const auto lines = (example > 0) ? toLines(examples[example - 1]) : toLines(day);
    print(day, example, lines.size());

    auto [answer, ms] = measure([&] { return solve(lines); });
    print(answer, ms);

    // 1578 (13), 10132 (43)
    if constexpr (example==0) { assert(answer.part1==1578 && answer.part2==10132); }

    return EXIT_SUCCESS;
}
