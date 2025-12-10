// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * AoC Day 05 solution.
 */

#include "aoc.hpp"

namespace {
    constexpr std::array examples =  {
        R"(
3-5
10-14
16-20
12-18

1
5
8
11
17
32
)"
    };
}

struct Range {
    int64_t from;
    int64_t to;
    [[nodiscard]] int64_t length() const { return to - from + 1; }
    [[nodiscard]] bool contains(const int64_t n) const { return n >= from && n <= to; }

    static Range of(const string &line) {
        static const std::regex re(R"(^(\d+)-(\d+)$)"); // without spaces, positive only

        std::smatch match;
        if (!std::regex_match(line, match, re)) {
            throw std::runtime_error("bad format");
        }

        const auto from = aoc::to_number<int64_t>(match[1].str());
        const auto to   = aoc::to_number<int64_t>(match[2].str());
        return {from, to};
    }
};

std::vector<Range> normalizeRanges(std::vector<Range> &ranges) {
    if (ranges.empty())
        return {};

    // sort by from, then by to; needed in the loop
    std::ranges::sort(ranges,
                      [](const Range& a, const Range& b) {
                          if (a.from != b.from) return a.from < b.from;
                          return a.to < b.to;
                      });

    std::vector<Range> result;
    Range current = ranges[0];

    for (size_t i = 1; i < ranges.size(); ++i) {
        if (const Range& r = ranges[i]; r.from <= current.to) { // overlaps or contained -> extend current range if needed
            if (r.to > current.to)
                current.to = r.to;
        } else {                                                // no overlap -> push current, start new one
            result.push_back(current);
            current = r;
        }
    }
    result.push_back(current);                                  // final one
    return result;
}

aoc::solutions solve(const aoc::Lines &rangeLines, const aoc::Lines &idLines) {
    std::vector<Range> ranges;
    ranges.reserve(rangeLines.size());
    for (auto &line : rangeLines) {
        ranges.push_back(Range::of(line));
    }

    std::vector<int64_t> ids;
    ids.reserve(idLines.size());
    for (auto &line : idLines) {
        ids.push_back(aoc::to_number<int64_t>(line));
    }

    int sum1 = 0;
    for (auto id : ids) {
        sum1 += std::ranges::any_of(ranges,
                                    [&](const Range& r){ return r.contains(id); }) ? 1 : 0; // '?' not needed (bool cast)
        // short for:
        // for (auto &range : ranges) {
        //     if (range.contains(id)) {
        //         sum1++;
        //         break;
        //     }
        // }
    }

    // ranges overlap or are contained, so sum range length does not work;
    // also, brute force counting does not work due to the large numbers
    const auto newRanges = normalizeRanges(ranges);
    int64_t sum2 = 0;
    for (const auto &range : newRanges) {
        sum2 += range.length();
    }

    return {sum1,sum2};
}

int main() {
    println("\n--- {} ---\n", __FILE__);

    constexpr auto day = 5;
    constexpr auto example = -1;
    aoc::println(day, example);

    const auto input = (example >= 0) ? aoc::Input::of(examples[example]) : aoc::Input::of(day);
    auto blocks = input | aoc::as_block_views;

    auto it  = blocks.begin();
    auto rangeLines = (*it) | aoc::to_trimmed_lines;
    auto idLines = (*(++it)) | aoc::to_trimmed_lines;

    auto [answer, ms] = aoc::measure([&] { return solve(rangeLines,idLines); });
    aoc::println(answer, ms);

    // 529 (3), 344260049617193 (14)
    if constexpr (example==-1) { assert(answer.part1==529 && answer.part2==344260049617193); }

    return EXIT_SUCCESS;
}
