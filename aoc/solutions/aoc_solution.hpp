// (C) A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

#ifndef AOC_SOLUTION
#define AOC_SOLUTION

#include "aoc_uses.hpp"

namespace aoc {

    inline void println(int day, int example) {
        auto data = (example==-1) ? "input" : format("example {}", example);
        auto info = format("day {} | {}", day, data);
        std::println("{}\n{}", info, string(info.size(), '='));
    }

    struct solutions {
        int64_t part1;
        int64_t part2;
    };

    template <typename F>
    auto measure(F&& f) {
        using R = std::invoke_result_t<F&>; // actual return type of f()

        const auto start = std::chrono::high_resolution_clock::now();
        if constexpr (std::is_void_v<R>) {
            std::forward<F>(f)();               // call for void
            auto end = std::chrono::high_resolution_clock::now();
            double ms = std::chrono::duration<double, std::milli>(end - start).count();
            return std::pair {std::monostate{}, ms};
        } else {
            R result = std::forward<F>(f)();    // call with result
            auto end = std::chrono::high_resolution_clock::now();
            double ms = std::chrono::duration<double, std::milli>(end - start).count();
            return std::pair<R, double>{std::move(result), ms};
        }
    }

    inline void println(const solutions &answer, double ms) {
        std::println("-> {:.2f} ms", ms);
        std::println("-> part 1: {}", answer.part1);
        std::println("-> part 2: {}", answer.part2);
    }

}

#endif // AOC_SOLUTION
