// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * AoC Day 02 solution.
 */

#include "aoc.hpp"

namespace {
    constexpr std::array examples =  {
R"(
11-22,95-115,998-1012,1188511880-1188511890,222220-222224,
1698522-1698528,446443-446449,38593856-38593862,565653-565659,
824824821-824824827,2121212118-2121212124
)"
    };
}

struct IdPair {
    int64_t id1;    // Maybe it is a little bit over the top-but many AoC-tasks require really long numbers.
    int64_t id2;

    static IdPair of(const string_view term) {
        const auto pos = term.find('-');
        if (pos == string_view::npos)
            throw std::runtime_error(format("format does not match, term='{}'", term));

        const auto id1 = aoc::to_number<int64_t>(term.substr(0, pos));
        const auto id2 = aoc::to_number<int64_t>(term.substr(pos + 1));
        return {id1, id2};
    }
};

std::vector<IdPair> to_idPairs(std::ranges::input_range auto&& lines) {
    auto idPairs =
        lines
        | std::views::transform([](auto&& line) {
              return std::views::split(line, ',')
                   | std::views::transform([](auto&& chunk) { return string_view{chunk}; })
                   | std::views::filter([](const string_view sv) { return !sv.empty(); });
          })
        | std::views::join
        | std::views::transform(IdPair::of);

    return std::ranges::to<std::vector<IdPair>>(idPairs);

    // same as

    // for (auto const &line : lines) {
    //     auto chunks =
    //         std::views::split(line, ',')
    //         | std::views::transform([](auto&& rng) { return string_view{rng}; })
    //         | std::views::filter([](const string_view sv){ return !sv.empty(); })
    //         | std::views::transform(IdPair::of);
    //
    //     for (auto&& idp : chunks)
    //         result.emplace_back(idp);
    // }

    // for (const auto &line : lines) {
    //     for (auto&& chunk : std::views::split(line, ',')) {
    //         if (auto sv = string_view{chunk}; !sv.empty())
    //             result.emplace_back(IdPair::of(sv));
    //     }
    // }
}

using DivSet = std::unordered_set<size_t>;

const DivSet& quotients(size_t n) {
    static std::unordered_map<size_t, DivSet> cache{ {1,DivSet()} };

    if (n <= 1) n=1;
    if (const auto it = cache.find(n); it != cache.end())
        return it->second;

    DivSet result{1};
    const auto limit = static_cast<size_t>(std::sqrt(static_cast<double>(n)));
    for (size_t d = 2; d <= limit; ++d) {
        if (n % d == 0) {
            result.emplace(d);
            result.emplace(n / d);
        }
    }

    auto [it, _] = cache.emplace(n, std::move(result));
    return it->second;
}

bool checkInvalidIdPart1(const string_view sv) {
    const size_t n = sv.size();
    if (n % 2 != 0)
        return false;   // odd length cannot match

    const size_t h = n / 2;
    return sv.substr(0, h) == sv.substr(h, h);
}

bool checkInvalidIdPart2(const string_view sv) {
    const size_t n = sv.size();

    return std::ranges::any_of(quotients(n), [&](size_t q) {
        return std::ranges::all_of(
            std::views::iota(q, n), // a sequence of numbers q..<n
            [&](const size_t i) { return sv[i] == sv[i % q]; }
        );
    });
}

aoc::solutions solve(std::ranges::input_range auto&& lines) {
    auto idPairs = to_idPairs(lines);

    int64_t sum1 = 0;
    int64_t sum2 = 0;
    for (const auto [id1, id2] : idPairs) {
        for (auto id = id1; id <= id2; ++id) {
            auto s = aoc::to_string(id);
            const string_view sv{s};
            if (checkInvalidIdPart1(sv))
                sum1 += id;
            if (checkInvalidIdPart2(sv))
                sum2 += id;
        }
    }

    return {sum1, sum2};
}

int main() {
    println("\n--- {} ---\n", __FILE__);

    constexpr auto day = 2;
    constexpr auto example = -1;
    aoc::println(day, example);

    const auto input = (example >= 0) ? aoc::Input::of(examples[example]) : aoc::Input::of(day);
    auto lines = input | aoc::as_std_lines;

    auto [answer, ms] = aoc::measure([&] { return solve(lines); });
    aoc::println(answer, ms);

    // 24157613387 (1227775554), 33832678380 (4174379265)
    if constexpr (example==-1) { assert(answer.part1==24157613387 && answer.part2==33832678380); } // best 64ms
    if constexpr (example==0) { assert(answer.part1==1227775554 && answer.part2==4174379265); }

    return EXIT_SUCCESS;
}
