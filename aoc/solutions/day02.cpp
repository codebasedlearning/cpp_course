// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * AoC Day 02 solution.
 */

#include "aoc.h"

namespace {
    constexpr array examples =  {
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
        const auto pos = term.find("-");
        if (pos == string_view::npos)
            throw runtime_error(format("format does not match, term='{}'", term));

        const auto id1 = toNumber<int64_t>(term.substr(0, pos));
        const auto id2 = toNumber<int64_t>(term.substr(pos + 1));
        return {id1, id2};
    }
};

vector<IdPair> parseLines(const Lines &lines) {
    vector<IdPair> result;

    for (const auto &line : lines) {
        for (auto chunk : std::views::split(line, ',')) {
            if (auto sv = string_view{chunk}; !sv.empty())
                result.emplace_back(IdPair::of(sv));
        }
    }
    return result;
}

using DivList = unordered_set<size_t>;
const DivList& quotients(size_t n) {
    static unordered_map<size_t, DivList> cache{ {1,DivList()} };

    if (n <= 1) n=1;
    if (const auto it = cache.find(n); it != cache.end())
        return it->second;

    DivList result{1};
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

bool checkInvalidIdPart1(const int64_t x) {
    const auto s = toString(x);
    const size_t n = s.size();
    if (n % 2 != 0)
        return false;   // odd length cannot match

    const size_t h = n / 2;
    return string_view{s}.substr(0, h) == string_view{s}.substr(h, h);
}

bool checkInvalidIdPart2(const int64_t x) {
    const auto s = toString(x);
    const size_t n = s.size();

    return std::ranges::any_of(quotients(n), [&](size_t q) {
        return std::ranges::all_of(
            std::views::iota(q, n), // a sequence of numbers q..<n
            [&](const size_t i) { return s[i] == s[i % q]; }
        );
    });

    /* this is basically:
        for (const auto q : quotients(n)) {
            bool matches = true;
            for (size_t i = q; i < n && matches; ++i)
                matches = (s[i] == s[i % q]);
            if (matches) return true;
        }
        return false;
    */
}

solutions solve(const Lines &lines) {
    auto idPairs = parseLines(lines);

    int64_t sum1 = 0;
    int64_t sum2 = 0;
    for (const auto [id1, id2] : idPairs) {
        for (auto id = id1; id <= id2; ++id) {
            if (checkInvalidIdPart1(id))
                sum1 += id;
            if (checkInvalidIdPart2(id))
                sum2 += id;
        }
    }

    return {sum1, sum2};
}

int main() {
    println("\n--- {} ---\n", __FILE__);

    constexpr auto day = 2;
    constexpr auto example = 0;

    const auto lines = (example > 0) ? toLines(examples[example - 1]) : toLines(day);
    print(day, example, lines.size());

    auto [answer, ms] = measure([&] { return solve(lines); });
    print(answer, ms);

    // 24157613387 (1227775554), 33832678380 (4174379265)
    if constexpr (example==0) { assert(answer.part1==24157613387 && answer.part2==33832678380); }
    if constexpr (example==1) { assert(answer.part1==1227775554 && answer.part2==4174379265); }

    return EXIT_SUCCESS;
}
