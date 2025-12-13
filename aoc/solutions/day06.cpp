// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * AoC Day 06 solution.
 */

#include "aoc.hpp"

namespace {
    constexpr std::array examples =  {
R"(
123 328  51 64
 45 64  387 23
  6 98  215 314
*   +   *   +
)"
    };
}

struct transpose_fn {
    auto operator()(const aoc::Field<char>& field) const -> std::vector<std::string> {
        std::vector lines(field.cols(), string(field.rows(), ' '));
        for (aoc::index_t row = 0; row < field.rows(); ++row)
            for (aoc::index_t col = 0; col < field.cols(); ++col)
                lines[col][row] = field[row,col];
        return lines;
    }

    friend auto operator|(const aoc::Field<char>& f, transpose_fn fn) -> std::vector<std::string> {
        return fn(f);
    }
};
inline constexpr transpose_fn to_transposed{};

using BinOp = int64_t(*)(int64_t, int64_t);
constexpr int64_t add(int64_t a, int64_t b) { return a + b; }
constexpr int64_t mul(int64_t a, int64_t b) { return a * b; }

struct Op {
    int64_t start;
    BinOp binOp;

    static Op of(const char term) {
        if (term == '+') return {0, &add};
        if (term == '*') return {1, &mul};
        throw std::runtime_error("bad op"); // for future-me
    }
};

aoc::solutions solve(std::ranges::input_range auto&& mathLines, const string_view opLine) {
    auto numbers = mathLines | aoc::to_field<int64_t>;

    auto ops = opLine
        | std::views::filter([](const char c){ return c == '+' || c == '*'; })
        | std::views::transform([](const char c) { return Op::of(c); })
        | std::ranges::to<std::vector>();

    int64_t sum1 = 0;
    for (aoc::index_t col=0; col<numbers.cols(); ++col) {
        const auto& op = ops[col];
        sum1 += std::ranges::fold_left( std::views::iota(0, numbers.rows()), int64_t{op.start},
                [&](int64_t acc, auto r) { return op.binOp(acc,numbers[r, col]); }
        );
    }

    // converting to field seems not optimal, but it also normalizes the lines
    auto colNumbers = mathLines | aoc::to_field<char> | to_transposed;
    colNumbers.push_back(""); // row continues across ops; each op consumes one column block, this forces the final op

    int64_t sum2 = 0;
    size_t row = 0;
    for (auto &op: ops) {
        int64_t res = op.start;
        while (row < colNumbers.size()) {
            auto line = aoc::trim(colNumbers[row]);
            row++;
            if (line.empty()) {
                sum2 += res;
                break;
            }
            res = op.binOp(res, aoc::to_number<int64_t>(line));
        }
    }

    return {sum1,sum2};
}

// fun with operator|
struct split_last_fn {
    template <std::ranges::forward_range R>
    auto operator()(R&& r) const {
        auto first = std::ranges::begin(r);
        auto last = std::ranges::end(r);
        if (first == last) throw std::runtime_error("split_last: empty range");

        auto prev = first;
        auto it = first;
        ++it;
        for (; it != last; ++it, ++prev) {}

        using V = std::ranges::range_value_t<R>; // *prev can dangle in principle
        return std::pair{ std::ranges::subrange{first, prev}, V(*prev) };
    }

    template <std::ranges::forward_range R>
    friend auto operator|(R&& r, split_last_fn fn) {
        return fn(std::forward<R>(r));
    }
};
inline constexpr split_last_fn split_last_line{};

int main() {
    println("\n--- {} ---\n", __FILE__);

    constexpr auto day = 6;
    constexpr auto example = -1;
    aoc::println(day, example);

    const auto input = (example >= 0) ? aoc::Input::of(examples[example]) : aoc::Input::of(day);
    auto [lines, operations] = input | aoc::as_std_lines | split_last_line;

    auto [answer, ms] = aoc::measure([&] { return solve(lines, operations); });
    aoc::println(answer, ms);

    // 5346286649122 (4277556), 10389131401929 (3263827)
    if constexpr (example==-1) { assert(answer.part1==5346286649122 && answer.part2==10389131401929); } // 0.43
    if constexpr (example==0) { assert(answer.part1==4277556 && answer.part2==3263827); }

    return EXIT_SUCCESS;
}
