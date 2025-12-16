// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * AoC Day 07 solution.
 */

#include "aoc.hpp"

namespace {
    constexpr std::array examples =  {
R"(
.......S.......
...............
.......^.......
...............
......^.^......
...............
.....^.^.^.....
...............
....^.^...^....
...............
...^.^...^.^...
...............
..^...^.....^..
...............
.^.^.^.^.^...^.
...............
)"
    };
}

aoc::solutions solve(std::ranges::input_range auto&& lines) {
    auto field = lines | aoc::to_field<char>;

    int64_t sum1 = 0;
    int64_t sum2 = 0;

    aoc::index_t startPos=-1;
    for (aoc::index_t col=0; col<field.cols(); ++col)
        if (field[0,col]=='S') { startPos=col; break; }
    if (startPos==-1)
        throw std::runtime_error("no starting position found");

    auto beams = std::unordered_map<aoc::index_t,int64_t>{ {startPos,1} };

    for (aoc::index_t row=1; row<field.rows(); ++row) {
        for (aoc::index_t col=0; col<field.cols(); ++col) {
            if (field[row,col]!='^') continue;
            auto it = beams.find(col);
            if (it == beams.end()) continue;

            ++sum1;

            const auto overlays = it->second;
            beams.erase(it);

            if (col-1>=0) { beams[col-1] += overlays; }
            if (col+1<field.cols()) { beams[col+1] += overlays; }
        }
    }

    for (const auto overlays: beams | std::views::values) { // auto [pos,overlays] : beams
        sum2 += overlays;
    }

    return {sum1,sum2};
}

int main() {
    println("\n--- {} ---\n", __FILE__);

    constexpr auto day = 7;
    constexpr auto example = -1;
    aoc::println(day, example);

    const auto input = (example >= 0) ? aoc::Input::of(examples[example]) : aoc::Input::of(day);
    auto lines = input | aoc::as_std_lines;

    auto [answer, ms] = aoc::measure([&] { return solve(lines); });
    aoc::println(answer, ms);

    // 1581 (21), 73007003089792 (40)
    if constexpr (example==-1) { assert(answer.part1==1581 && answer.part2==73007003089792); } // 0.09ms
    if constexpr (example==0) { assert(answer.part1==21 && answer.part2==40); }

    return EXIT_SUCCESS;
}
