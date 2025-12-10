// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * AoC Day xx solution.
 */

#include "aoc.hpp"

namespace {
    constexpr std::array examples =  {
R"(
L68
)",
    };
}

aoc::solutions solve(std::ranges::input_range auto&& lines) {

    aoc::print(lines | aoc::to_field<char>);
    return {1,2};
}


int main() {
    println("\n--- {} ---\n", __FILE__);

    constexpr auto day = 0;
    constexpr auto example = 0;
    aoc::println(day, example);

    const auto input = (example >= 0) ? aoc::Input::of(examples[example]) : aoc::Input::of(day);
    auto lines = input | aoc::as_std_lines;

    auto [answer, ms] = aoc::measure([&] { return solve(lines); });
    aoc::println(answer, ms);

    // 1 (1), 2 (2)
    if constexpr (example==-1) { assert(answer.part1==1 && answer.part2==2); }
    if constexpr (example==0) { assert(answer.part1==1 && answer.part2==2); }

    return EXIT_SUCCESS;
}
