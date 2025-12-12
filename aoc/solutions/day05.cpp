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

    static Range of(const string_view line) {
        // slow:
        //      static const std::regex re(R"(^(\d+)-(\d+)$)"); // without spaces, positive only
        //      std::smatch match;
        const auto pos = line.find('-');
        if (pos == std::string_view::npos)
            throw std::runtime_error("bad format");

        return {
            aoc::to_number<int64_t>(line.substr(0, pos)),
            aoc::to_number<int64_t>(line.substr(pos + 1))
        };
    }
};

std::vector<Range> normalizeRanges(std::ranges::input_range auto&& ranges) {
    if (ranges.empty())
        return {};

    // sorting is in-place, so we need  manifestation
    auto sortedRanges = std::ranges::to<std::vector<Range>>(ranges);
    // sort by from, then by to; needed in the loop
    std::ranges::sort(sortedRanges,
                      [](const Range& a, const Range& b) { return (a.from != b.from) ? a.from < b.from : a.to < b.to; });

    std::vector<Range> normRanges;
    normRanges.reserve(sortedRanges.size());

    Range current = sortedRanges[0];
    for (size_t i = 1; i < sortedRanges.size(); ++i) {
        if (const Range& r = sortedRanges[i]; r.from <= current.to) { // overlaps or contained -> extend current range if needed
            if (r.to > current.to)
                current.to = r.to;
        } else {                            // no overlap -> push current, start new one
            normRanges.push_back(current);
            current = r;
        }
    }
    normRanges.push_back(current);          // final one
    return normRanges;
}

// fun with operator|
struct normalize_ranges_fn {
    template <std::ranges::input_range R>
    auto operator()(R&& r) const -> std::vector<Range> {
        return normalizeRanges(std::forward<R>(r));
    }

    // Enables: r | normalize
    template <std::ranges::input_range R>
    friend auto operator|(R&& r, const normalize_ranges_fn& fn) -> std::vector<Range> {
        return fn(std::forward<R>(r));
    }
};
inline constexpr normalize_ranges_fn normalize{};

aoc::solutions solve(std::ranges::input_range auto&& rangeLines, std::ranges::input_range auto&& idLines) {
    auto ranges = rangeLines
        | std::views::transform([](const auto &s){ return Range::of(s); })
        | normalize;

    auto ids = idLines
        | std::views::transform([](const auto &s){ return aoc::to_number<int64_t>(s); });

    // here is still a little potential as both can be sorted before
    int64_t sum1 = 0;
    for (auto id : ids) {
        sum1 += std::ranges::any_of(ranges,
                                    [&](const Range& r){ return r.contains(id); }) ? 1 : 0; // '?' not needed (bool cast)
    }

    // classical
    //      int64_t sum2 = 0;
    //      for (const auto &range : ranges) { sum2 += range.length(); }
    //
    // ChatGPT :-) Why not std::ranges::accumulate?
    //      -> Because it doesn’t exist. Yes, everyone expects it. No, it’s not there. Yes, this hurts us all.

    // manual fold it
    auto sum2 = std::ranges::fold_left(ranges, int64_t{0},
        [](int64_t acc, const auto& range) { return acc + range.length(); }
    );

    // with std op it would be
    //      auto sum2 = std::ranges::fold_left(
    //          ranges | std::views::transform(&Range::length),
    //          int64_t{0}, std::plus{}
    //      );
    return {sum1,sum2};
}

int main() {
    println("\n--- {} ---\n", __FILE__);

    constexpr auto day = 5;
    constexpr auto example = -1;
    aoc::println(day, example);

    const auto input = (example >= 0) ? aoc::Input::of(examples[example]) : aoc::Input::of(day);
    auto blocks = input | aoc::as_block_views;
    auto rangeLines = *blocks.begin();
    auto idLines = *(++blocks.begin());

    auto [answer, ms] = aoc::measure([&] { return solve(rangeLines,idLines); });
    aoc::println(answer, ms);

    // 529 (3), 344260049617193 (14)
    if constexpr (example==-1) { assert(answer.part1==529 && answer.part2==344260049617193); } // 0.06ms

    return EXIT_SUCCESS;
}
