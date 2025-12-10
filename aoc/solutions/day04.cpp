// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * AoC Day 04 solution.
 */

#include "aoc.hpp"

namespace {
    constexpr std::array examples =  {
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

aoc::solutions solve(std::ranges::input_range auto&& lines) {
    auto field = lines | aoc::to_field<char>;

    int64_t sum1{0};
    int64_t sum2{0};

    // collect all positions
    auto papers = std::ranges::to<std::unordered_set<aoc::RC>>(
        positions(field)
        | std::views::filter([&](const aoc::RC rc) { return field[rc] == '@'; })
    );

    // abort if too long
    for (size_t loop=0; loop<1000; ++loop) {
        auto neighbor_count = [&](const aoc::RC rc) {
            return std::ranges::count_if( halo(field, rc),
                [&](const aoc::RC cell) { return field[cell] == '@'; }
            );
        };

        // reduce papers
        auto toLift = std::ranges::to<std::unordered_set<aoc::RC>>(
            papers
            | std::views::filter([&](const aoc::RC rc) { return neighbor_count(rc) < 4; })
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
    constexpr auto example = -1;
    aoc::println(day, example);

    const auto input = (example >= 0) ? aoc::Input::of(examples[example]) : aoc::Input::of(day);
    auto lines = input | aoc::as_std_lines;
//    auto field = input | aoc::as_std_lines | toField;

    auto [answer, ms] = aoc::measure([&] { return solve(lines); });
    aoc::println(answer, ms);

    // 1578 (13), 10132 (43)
    if constexpr (example==-1) { assert(answer.part1==1578 && answer.part2==10132); }

    return EXIT_SUCCESS;
}
