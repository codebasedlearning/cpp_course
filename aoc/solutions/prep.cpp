// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * An unsorted set of helper types and functions.
 */

#include <string>
#include <string_view>
#include <charconv>
#include <format>
#include <iostream>
#include <iomanip>
#include <print>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <ranges>
#include <memory>
#include <vector>
#include <array>
#include <unordered_map>
#include <unordered_set>
#include <regex>
#include <stdexcept>
#include <chrono>

using std::string, std::string_view, std::format, std::from_chars;
using std::cout, std::endl, std::setw, std::stringstream, std::print, std::println;
using std::vector, std::array, std::unordered_map, std::unordered_set;
using std::unique_ptr, std::make_unique;
using std::runtime_error;
using std::size_t;

string strip(string_view s) {
    const auto ws = [](const unsigned char c){ return std::isspace(c); };
    auto trimmed = s
        | std::views::drop_while(ws)
        | std::views::reverse
        | std::views::drop_while(ws)
        | std::views::reverse;
    return {trimmed.begin(), trimmed.end()};
}

string stats(int day, int example, int size) {
    auto info = format("day {} | example {} | size {}", day, example, size);
    return format("{}\n{}\n", info, string(info.size(), '='));
}

using lines_t = vector<string>;
using blocks_t = vector<lines_t>;

blocks_t toBlocks(std::istream &is) {
    blocks_t blocks;
    lines_t lines;
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

blocks_t puzzleInput(int day) {
    std::ifstream in(format("../../aoc/data/input_day{:02}.txt", day));
    return toBlocks(in);
}

blocks_t exampleInput(const string &example) {
    std::istringstream in(example);
    return toBlocks(in);
}

template<typename T>
T toNumber(const string_view sv) {
    T value{};
    if (auto [p, ec] = from_chars(sv.data(), sv.data() + sv.size(), value); ec != std::errc() || p != sv.end())
        throw runtime_error(format("Invalid number: {}", sv));
    return value;
}

template<typename T>
string toString(const T x) {
    return format("{}", x);
}

template<typename Func>
double measure(Func func) {
    const auto start = std::chrono::high_resolution_clock::now();
    func();
    const auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double, std::milli>(end - start).count();
}

/*
 * Please use the original data from AoC. In the solution examples,
 * they are expected in the directory 'data' in the format 'input_dayxx.txt'.
 */
