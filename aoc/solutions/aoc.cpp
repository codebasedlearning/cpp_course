// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

#include "aoc.h"

namespace aoc {
    void print(int day, int example, size_t size) {
        auto info = format("day {} | example {} | size {}", day, example, size);
        println("{}",format("{}\n{}", info, string(info.size(), '=')));
    }

    void print(const solutions &answer, double ms) {
        println("-> {:.2f} ms", ms);
        println("-> part 1: {}", answer.part1);
        println("-> part 2: {}", answer.part2);
    }

    string strip(string_view s) {
        const auto ws = [](const unsigned char c){ return std::isspace(c); };
        auto trimmed = s
            | std::views::drop_while(ws)
            | std::views::reverse
            | std::views::drop_while(ws)
            | std::views::reverse;
        return {trimmed.begin(), trimmed.end()};
    }

    Blocks toBlocks(std::istream &is) {
        Blocks blocks;
        Lines lines;
        string line;

        while (getline(is, line)) {
            if (auto s = strip(line); s.empty()) {
                if (!lines.empty()) {
                    blocks.emplace_back(std::move(lines));
                    lines.clear();
                }
            } else {
                lines.emplace_back(std::move(s));
            }
        }

        if (!lines.empty())
            blocks.emplace_back(std::move(lines));

        return blocks;
    }

    Blocks toBlocks(int day) {
        std::ifstream in(format("../../aoc/data/input_day{:02}.txt", day));
        return toBlocks(in);
    }

    Blocks toBlocks(const string &example) {
        std::istringstream in(example);
        return toBlocks(in);
    }

    Lines toLines(int day) { return toBlocks(day)[0]; }

    Lines toLines(const string &example) { return toBlocks(example)[0]; }




}
