// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

#ifndef AOC_COMPLETE
#define AOC_COMPLETE

#include <string>
#include <string_view>
#include <charconv>
#include <format>
#include <iostream>
#include <iomanip>
#include <print>
#include <sstream>
#include <fstream>
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
#include <type_traits>
#include <utility>
#include <variant>
#include <functional>
#include <cstdlib>
#include <cassert>

using std::string, std::string_view, std::format, std::from_chars;
using std::cout, std::endl, std::setw, std::stringstream;
using std::print, std::println;
using std::vector, std::array, std::unordered_map, std::unordered_set;
using std::unique_ptr, std::make_unique;
using std::runtime_error;
using std::size_t;

//string stats(int day, int example, int size);
namespace aoc {

    // solution management

    struct solutions {
        int64_t part1;
        int64_t part2;
    };

    void print(int day, int example, size_t size);
    void print(const solutions &answer, double ms);

    template <typename F>
    auto measure(F&& f) {
        using R = std::invoke_result_t<F&>;     // actual return type of f()

        auto start = std::chrono::high_resolution_clock::now();
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

    // input management

    using Lines = vector<string>;
    using Blocks = vector<Lines>;

    Blocks toBlocks(int day);
    Blocks toBlocks(const string &example);
    Lines toLines(int day);
    Lines toLines(const string &example);

    // string or conversion helper

    string strip(string_view s);

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

    // 2D-stuff - still under construction

    struct RC {
        int row;
        int col;
    };

    class Field {
    public:
        using value_type = char;
        using container_type = vector<vector<value_type>>;

        container_type data;

        static Field of(const Lines &lines) {
            Field grid;
            grid.data.reserve(lines.size());

            for (const auto& line : lines) {
                if (auto s = strip(line); !s.empty())
                    grid.data.emplace_back(s.begin(), s.end());
            }
            return grid;
        }

        [[nodiscard]] int rows() const { return static_cast<int>(data.size()); }
        [[nodiscard]] int cols() const { return data.empty() ? 0 : static_cast<int>(data[0].size()); }

        value_type operator[](const size_t r, const size_t c) const { return data[r][c]; }
        value_type& operator[](const size_t r, const size_t c) { return data[r][c]; }

        value_type operator[](const RC& rc) const { return data[rc.row][rc.col]; }
        value_type& operator[](const RC& rc) { return data[rc.row][rc.col]; }
        
        void print() const {
            for (const auto& row : this->data) {
                for (char c : row) cout << c;
                cout << '\n';
            }
        }
    };

}

using aoc::solutions;
using aoc::print, aoc::measure;
using aoc::Blocks, aoc::Lines, aoc::toBlocks, aoc::toLines;
using aoc::toNumber, aoc::toString;

using aoc::RC, aoc::Field;

#endif // AOC_COMPLETE
