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
#include <cstddef>
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

    void print(int day, int example, size_t size1, size_t size2=0);
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

    // 2D-stuff-still under construction

    struct RC {
        int row;
        int col;
    };

    template <typename T>
    class Field {
    public:
        using value_type = T;

        Field() : rows_(0), cols_(0) {}
        Field(const size_t rows, const size_t cols) : rows_(rows), cols_(cols), data_(rows * cols) {}

        [[nodiscard]] size_t rows() const noexcept { return rows_; }
        [[nodiscard]] size_t cols() const noexcept { return cols_; }

        [[nodiscard]] bool isValid(const RC rc) const { return rc.row >= 0 && rc.row < rows() && rc.col >= 0 && rc.col < cols(); }

        value_type& operator[](const size_t row, const size_t col) noexcept { return data_[linear_index(row, col)]; }
        const value_type& operator[](const size_t row, const size_t col) const noexcept { return data_[linear_index(row, col)]; }

        value_type& operator[](const RC& rc) noexcept { return (*this)[rc.row,rc.col]; }
        const value_type& operator[](const RC& rc) const noexcept { return (*this)[rc.row,rc.col]; }

        value_type* data() noexcept { return data_.data(); }
        [[nodiscard]] const value_type* data() const noexcept { return data_.data(); }

    private:
        [[nodiscard]] size_t linear_index(const size_t row, const size_t col) const noexcept { return col + row * cols_; }

        size_t rows_;
        size_t cols_;
        vector<T> data_;
    };

    template <typename T>
    void print(const Field<T> &field) {
        for (size_t row = 0; row < field.rows(); ++row) {
            for (size_t col = 0; col < field.cols(); ++col)
                cout << field[row,col];
            cout << '\n';
        }
    }

    Field<char> toField(const Lines &lines);

}

using aoc::solutions;
using aoc::print, aoc::measure;
using aoc::Blocks, aoc::Lines, aoc::toBlocks, aoc::toLines;
using aoc::toNumber, aoc::toString;
using aoc::toField;

using aoc::RC, aoc::Field;

#endif // AOC_COMPLETE
