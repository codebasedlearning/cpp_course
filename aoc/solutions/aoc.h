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
#include <iterator>
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
#include <utility>
#include <cassert>


using std::string, std::string_view, std::format, std::from_chars;
using std::cout, std::endl, std::setw, std::stringstream;
using std::print, std::println;
using std::vector, std::array, std::unordered_map, std::unordered_set;
using std::unique_ptr, std::make_unique;
using std::runtime_error;
using std::size_t;

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

    using index_t = int64_t; // should be signed

    struct RC {
        index_t row{};
        index_t col{};

        bool operator==(const RC&) const noexcept = default;

        RC& operator+=(const RC rhs) noexcept { row += rhs.row; col += rhs.col; return *this; }
        RC& operator-=(const RC rhs) noexcept { row -= rhs.row; col -= rhs.col; return *this; }
        friend RC operator+(RC lhs, const RC rhs) noexcept { return lhs+=rhs; }
    };

    template <typename T>
    class Field {
    public:
        using value_type = T;

        Field() : rows_(0), cols_(0) {}
        Field(const index_t rows, const index_t cols) : rows_(rows), cols_(cols), data_(rows * cols) {}

        [[nodiscard]] index_t rows() const noexcept { return rows_; }
        [[nodiscard]] index_t cols() const noexcept { return cols_; }

        [[nodiscard]] bool isValid(const RC rc) const { return rc.row >= 0 && rc.row < rows() && rc.col >= 0 && rc.col < cols(); }

        value_type& operator[](const index_t row, const index_t col) noexcept { return data_[linear_index(row, col)]; }
        const value_type& operator[](const index_t row, const index_t col) const noexcept { return data_[linear_index(row, col)]; }

        value_type& operator[](const RC& rc) noexcept { return (*this)[rc.row,rc.col]; }
        const value_type& operator[](const RC& rc) const noexcept { return (*this)[rc.row,rc.col]; }

        value_type* data() noexcept { return data_.data(); }
        [[nodiscard]] const value_type* data() const noexcept { return data_.data(); }

    private:
        [[nodiscard]] index_t linear_index(const index_t row, const index_t col) const noexcept { return col + row * cols_; }

        index_t rows_;
        index_t cols_;
        vector<T> data_;
    };

    template <typename T>
    void print(const Field<T> &field) {
        for (index_t row = 0; row < field.rows(); ++row) {
            for (index_t col = 0; col < field.cols(); ++col)
                cout << field[row,col];
            cout << '\n';
        }
    }

    Field<char> toField(const Lines &lines);

    // 2D-stuff for algorithms

    template <typename T>
    class Positions {
        index_t rows_;
        index_t cols_;

    public:
        explicit Positions(const Field<T>& f) : rows_(f.rows()), cols_(f.cols()) {}

        class iterator {
            index_t idx_ = 0;
            index_t cols_ = 0;

        public:
            using iterator_concept  = std::forward_iterator_tag;
            using iterator_category = std::forward_iterator_tag;
            using difference_type   = std::ptrdiff_t;
            using value_type        = RC;
            using reference         = RC;

            iterator() = default;

            iterator(const index_t idx, const index_t cols) : idx_(idx), cols_(cols) {}

            RC operator*() const noexcept { return RC{ idx_ / cols_, idx_ % cols_ }; }

            iterator& operator++() {
                ++idx_;
                return *this;
            }

            iterator operator++(int) {
                auto tmp = *this;
                ++(*this);
                return tmp;
            }

            bool operator==(const iterator& other) const noexcept { return idx_ == other.idx_; }
            bool operator!=(const iterator& other) const noexcept { return !(*this == other); }
        };

        [[nodiscard]] iterator begin() const noexcept { return iterator(0, cols_); }
        [[nodiscard]] iterator end()   const noexcept { return iterator(rows_ * cols_, cols_); }
    };

    template <typename T>
    Positions<T> positions(const Field<T>& f) {
        return Positions<T>(f);
    }

    template <typename T, typename Neighborhood>
    class Halo {
        const Field<T>& field_;
        const RC center_;

    public:
        Halo(const Field<T>& field, const RC center) : field_(field), center_(center) {}

        // To use the iterator with ranges-algorithms, it must fulfill the range-requirements.
        class iterator {
            static constexpr auto &offsets = Neighborhood::offsets;

            const Field<T>* field_{};
            RC center_{};
            size_t idx_{};

            void untilValid() {
                while (idx_ < offsets.size() && !field_->isValid(center_ + offsets[idx_])) {
                    ++idx_;
                }
            }

        public:
            using iterator_concept  = std::input_iterator_tag;
            using iterator_category = std::input_iterator_tag;
            using difference_type   = std::ptrdiff_t;
            using value_type        = RC;
            using reference         = RC;

            iterator() = default;

            iterator(const Field<T>& field, const RC center, const size_t idx)
                : field_(&field), center_(center), idx_(idx) { untilValid(); }

            RC operator*() const { return center_ + offsets[idx_]; }

            iterator& operator++() {
                if (idx_ < offsets.size()) { ++idx_; untilValid(); }
                return *this;
            }

            iterator operator++(int) {
                auto tmp = *this;
                ++(*this);
                return tmp;
            }

            bool operator==(const iterator& other) const { return idx_ == other.idx_; } // skip the pointer test
            bool operator!=(const iterator& other) const { return !(*this == other); }
        };

        [[nodiscard]] iterator begin() const { return iterator(field_, center_, 0); }
        [[nodiscard]] iterator end() const { return iterator(field_, center_, Neighborhood::offsets.size()); }
    };

    // 4-point von Neumann neighborhood (N, S, W, E)
    struct VonNeumannNeighborhood {
        static constexpr array offsets {
                       RC{-1, 0},
            RC{ 0, 1},            RC{ 0,-1},
                       RC{ 1, 0},
            };
    };

    // 4-point diagonals only (NW, NE, SW, SE)
    struct DiagonalsNeighborhood {
        static constexpr array offsets {
            RC{-1,-1},            RC{-1, 1},
            RC{ 1,-1},            RC{ 1, 1}
        };
    };

    // 8-point Moore neighborhood
    struct MooreNeighborhood {
        static constexpr array offsets {
            RC{-1,-1}, RC{-1, 0}, RC{-1, 1},
            RC{ 0,-1},            RC{ 0, 1},
            RC{ 1,-1}, RC{ 1, 0}, RC{ 1, 1}
        };
    };

    template <typename T>
    auto halo_plus(const Field<T>& f, RC center) {
        return Halo<T, VonNeumannNeighborhood>(f, center);
    }

    template <typename T>
    auto halo_cross(const Field<T>& f, RC center) {
        return Halo<T, DiagonalsNeighborhood>(f, center);
    }

    template <typename T>
    auto halo(const Field<T>& f, RC center) {
        return Halo<T, MooreNeighborhood>(f, center);
    }

}

namespace std {
    template<>
    struct hash<aoc::RC> {
        size_t operator()(const aoc::RC& rc) const noexcept {
            const size_t h1 = std::hash<aoc::index_t>{}(rc.row);
            const size_t h2 = std::hash<aoc::index_t>{}(rc.col);
            return h1 ^ (h2 + 0x9e3779b97f4a7c15ull + (h1 << 6) + (h1 >> 2)); // Knuth 64-bit golden ratio constant.
        }
    };
}

using aoc::solutions;
using aoc::print, aoc::measure;
using aoc::Blocks, aoc::Lines, aoc::toBlocks, aoc::toLines;
using aoc::toNumber, aoc::toString;
using aoc::index_t, aoc::RC, aoc::Field;
using aoc::toField;

#endif // AOC_COMPLETE
