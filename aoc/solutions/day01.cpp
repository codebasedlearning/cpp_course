// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * AoC Day 01 solution.
 */

#include "aoc.hpp"

/*
 * Anonymous namespace (or 'unnamed namespace').
 * Contents are only visible within this .cpp file (similar to 'static').
 * Works also for types and functions.
 */
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

    constexpr int ringSize = 100;
    constexpr int startPos = 50;
}

struct DirectionSteps {
    bool isLeft;
    int steps;

    static DirectionSteps of(const std::string_view &term) {
        // a little bit overengineered, I wanted to have a reg-ex with groups (as template)
        // or use from_chars
        static const std::regex re(R"(^([A-Za-z]+)(\d+)$)");

        std::smatch m;
        auto s = string(term);
        if (!std::regex_match(s, m, re) || (m[1].str()!="L" && m[1].str()!="R"))
            throw std::runtime_error(format("format does not match, term='{}'", term));
        return { m[1].str()=="L", std::stoi(m[2].str()) };
    }
};

aoc::solutions solve(std::ranges::input_range auto&& lines) {
    auto dirSteps = lines
        | std::views::transform([](const auto &s){ return DirectionSteps::of(s); });

    auto pos = startPos, at0 = 0, cross0 = 0;

    for (const auto &[isLeft, steps] : dirSteps) {
        const auto [rounds, val] = std::div(steps, ringSize); // -> quot, rem

        if (isLeft) {
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
    if constexpr (example==-1) { assert(answer.part1==1055 && answer.part2==6386); }
    if constexpr (example==0) { assert(answer.part1==3 && answer.part2==6); }

    return EXIT_SUCCESS;
}
