// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

#include "aoc.h"

namespace aoc {
    void print(int day, int example, size_t size1, size_t size2) {
        auto sizes = (size2==0) ? format("size {}", size1) : format("sizes {} / {}", size1, size2);
        auto info = format("day {} | example {} | {}", day, example, sizes);
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

    Lines toLines(const int day) { return toBlocks(day)[0]; }

    Lines toLines(const string &example) { return toBlocks(example)[0]; }

    Field<char> toField(const Lines &lines) {
        // guard: check format
        size_t rows{0};
        size_t cols{0};
        for (const auto &line : lines) {
            if (line.empty()) continue;
            ++rows;
            if (cols == 0)
                cols = line.size();
            else if (cols != line.size())
                throw runtime_error("inconsistent cols");
        }
        if (rows==0 || cols==0)
            throw runtime_error("no data");

        Field<char> field(rows, cols);

        size_t dst_row = 0;
        for (const auto &line : lines) {
            if (line.empty()) continue;
            std::copy_n(line.begin(), cols, field.data() + dst_row * cols);
            ++dst_row;
        }
        return field;
    }

}
