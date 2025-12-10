// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * AoC Day 01 solution.
 */

#include "aoc.hpp"

namespace {
    constexpr std::array examples =  {
R"(
L68
L30
R48
L5
R60
L55
L1
L99
R14
L82
)",
    };

    constexpr int64_t ringSize = 100;
    constexpr int64_t startPos = 50;
}

struct DirectionSteps {
    enum class Turn { Left, Right };

    Turn turn;
    int64_t steps;

    static DirectionSteps of(const string_view term) {
        // a little bit overengineered, I wanted to have a reg-ex with groups (as template)
        // or use from_chars
        // static const std::regex re(R"(^([LR])(\d+)$)");
        //
        // std::smatch m;
        // auto s = string(term);
        // if (!std::regex_match(s, m, re))
        //     throw std::runtime_error(format("format does not match, term='{}'", term));
        // const Turn turn = m[1].str()=="L" ? Turn::Left : Turn::Right;
        // return { turn, aoc::to_number<int64_t>(m[2].str()) };

        if (term.size() < 2)
            throw std::runtime_error(format("term too short: '{}'", term));
        const char dir = term.front();
        if (dir != 'L' && dir != 'R')
            throw std::runtime_error(format("invalid direction: '{}'", term));

        const auto first = term.data() + 1;
        const auto last  = term.data() + term.size();
        const auto turn = (dir == 'L') ? Turn::Left : Turn::Right;
        const auto steps = aoc::to_number<int64_t>(string_view{first, last});
        return { turn, steps };
    }
};

aoc::solutions solve(std::ranges::input_range auto&& lines) {
    auto dirSteps = lines
        | std::views::transform(DirectionSteps::of); // <=> [](const auto &s){ return DirectionSteps::of(s); }

    int64_t pos = startPos, at0 = 0, cross0 = 0;

    for (const auto &[turn, steps] : dirSteps) {
        const auto [rounds, val] = std::lldiv(steps, ringSize); // -> quot, rem

        if (turn==DirectionSteps::Turn::Left) {
            if (0 < pos && pos < val) // leaving the edges is intended.
                ++cross0;
            pos = (pos - val + ringSize) % ringSize;
        } else {
            if (pos + val > ringSize)
                ++cross0;
            pos = (pos + val) % ringSize;
        }
        if (pos == 0)
            ++at0;
        cross0 += rounds;
    }

    return {at0, at0 + cross0};
}

int main() {
    println("\n--- {} ---\n", __FILE__);

    constexpr auto day = 1;
    constexpr auto example = -1;
    aoc::println(day, example);

    const auto input = (example >= 0) ? aoc::Input::of(examples[example]) : aoc::Input::of(day);
    auto lines = input | aoc::as_std_lines;

    auto [answer, ms] = aoc::measure([&] { return solve(lines); });
    aoc::println(answer, ms);

    // 1055 (3), 6386 (6)
    if constexpr (example==-1) { assert(answer.part1==1055 && answer.part2==6386); } // best 0.06ms
    if constexpr (example==0) { assert(answer.part1==3 && answer.part2==6); }

    return EXIT_SUCCESS;
}
