// (C) A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

#ifndef AOC_FIELD
#define AOC_FIELD

#include "aoc_uses.hpp"
#include "aoc_conversions.hpp"
#include "aoc_input.hpp"

namespace aoc {

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

        void resize(const index_t rows, const index_t cols) { rows_=rows; cols_=cols; data_.resize(rows_ * cols_); }

        [[nodiscard]] bool isValid(const RC rc) const { return rc.row >= 0 && rc.row < rows() && rc.col >= 0 && rc.col < cols(); }

        value_type& operator[](const index_t row, const index_t col) noexcept { return data_[linear_index(row, col)]; }
        const value_type& operator[](const index_t row, const index_t col) const noexcept { return data_[linear_index(row, col)]; }

        value_type& operator[](const RC& rc) noexcept { return (*this)[rc.row,rc.col]; }
        const value_type& operator[](const RC& rc) const noexcept { return (*this)[rc.row,rc.col]; }

        value_type* data() noexcept { return data_.data(); }
        [[nodiscard]] const value_type* data() const noexcept { return data_.data(); }

        // void transpose() {
        //     Field<T> tmp(cols_, rows_);
        //     for (index_t row = 0; row < rows_; ++row)
        //         for (index_t col = 0; col < cols_; ++col)
        //             tmp[col,row] = (*this)[row,col];
        //     //*this = tmp;
        //     std::swap(rows_, cols_);
        //     std::swap(data_,tmp.data_);
        // }

    private:
        [[nodiscard]] index_t linear_index(const index_t row, const index_t col) const noexcept { return col + row * cols_; }

        index_t rows_;
        index_t cols_;
        std::vector<T> data_;
    };

    template <typename T>
    void print(const Field<T> &field, const string &delim = "") {
        for (index_t row = 0; row < field.rows(); ++row) {
            for (index_t col = 0; col < field.cols(); ++col)
                std::cout << field[row,col] << delim;
            std::cout << '\n';
        }
    }

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
        static constexpr std::array offsets {
                       RC{-1, 0},
            RC{ 0, 1},            RC{ 0,-1},
                       RC{ 1, 0},
            };
    };

    // 4-point diagonals only (NW, NE, SW, SE)
    struct DiagonalsNeighborhood {
        static constexpr std::array offsets {
            RC{-1,-1},            RC{-1, 1},
            RC{ 1,-1},            RC{ 1, 1}
        };
    };

    // 8-point Moore neighborhood
    struct MooreNeighborhood {
        static constexpr std::array offsets {
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

    /*
     * Here the view-specific code starts... still under construction.
     * Try to figure out, what makes sense.
     */

    template <typename T>
    concept NumericButNotChar = (std::integral<T> || std::floating_point<T>) && !std::same_as<T, char>;

    template <NumericButNotChar T, std::ranges::input_range R>
    Field<T> to_field_numeric_impl(R&& lines) {
        if (lines.empty())
            throw std::runtime_error("no rows");

        index_t cols{0};
        const index_t rows = std::ranges::count_if(lines, [](std::string_view s) { return !s.empty(); });

        Field<T> field(0, 0);
        index_t dst_row = 0;
        for (const auto &line : lines) {
            if (line.empty()) continue;

            auto v = aoc::to_numbers<T>(line);
            if (dst_row==0) {
                if (v.empty())
                    throw std::runtime_error("no cols");
                cols = static_cast<index_t>(v.size());
                field.resize(rows, cols);
            } else if (cols != v.size()) {
                throw std::runtime_error("different cols");
            }
            std::copy_n(v.begin(), cols, field.data() + dst_row * cols);
            ++dst_row;
        }
        return field;
    }

    template <std::ranges::input_range R>
    Field<char> to_field_char_impl(R&& lines) {
        // guard: check format, count rows
        index_t rows{0};
        index_t cols{0};
        for (const auto &line : lines) {
            ++rows;
            cols = std::max(cols,static_cast<aoc::index_t>(line.size()));
        }
        if (rows==0 || cols==0)
            throw std::runtime_error("no data");

        Field<char> field(rows, cols);

        index_t dst_row = 0;
        for (const auto &line : lines) {
            if (line.empty()) continue;
            std::copy_n(line.begin(), line.size(), field.data() + dst_row * cols);
            if (line.size() < cols) {
                std::fill_n(field.data() + dst_row * cols + line.size(), cols-line.size(), ' ');
            }
            ++dst_row;
        }
        return field;
    }

    template <typename T, std::ranges::input_range R>
    Field<T> toField(R&& lines) {
        if constexpr (std::same_as<T, char>) {
            return to_field_char_impl(std::forward<R>(lines));
        } else if constexpr (NumericButNotChar<T>) {
            return to_field_numeric_impl<T>(std::forward<R>(lines));
        } else {
            static_assert(false,
                "aoc::toField<T>: no implementation for this T");
        }
    }

    template <typename T>
    concept FieldElement = std::same_as<T, char> || NumericButNotChar<T>;

    template <FieldElement T>
    struct ToFieldAdaptor {
        template <std::ranges::input_range R>
        auto operator()(R&& lines) const -> Field<T> {
            return toField<T>(std::forward<R>(lines));
        }

        template <std::ranges::input_range R>
        friend auto operator|(R&& lines, const ToFieldAdaptor& self) -> Field<T> {
            return self(std::forward<R>(lines));
        }
    };

    template <FieldElement T>
    inline constexpr ToFieldAdaptor<T> to_field{};

    template <typename T>
    struct ToStdFieldAdaptor {
        template <std::ranges::input_range R>
        auto operator()(R&& r) const {
            return std::forward<R>(r)
                | as_line_views
                | first_block_view
                | aoc::to_field<T>;
        }

        template <std::ranges::input_range R>
        friend auto operator|(R&& r, const ToStdFieldAdaptor& self) {
            return self(std::forward<R>(r));
        }
    };

    inline constexpr ToStdFieldAdaptor<char> to_std_field{};
    inline constexpr ToStdFieldAdaptor<int64_t> to_int_field{};
    inline constexpr ToStdFieldAdaptor<double> to_double_field{};
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

#endif // AOC_FIELD
