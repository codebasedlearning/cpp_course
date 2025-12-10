// (C) A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

#ifndef AOC_INPUT
#define AOC_INPUT

#include "aoc_uses.hpp"

namespace aoc {

    using Lines = std::vector<string>;

    class Input {
        using storage_type = string;
        storage_type text_;

    public:
        using value_type     = char;
        using size_type      = size_t;
        using iterator       = storage_type::const_iterator;
        using const_iterator = storage_type::const_iterator;

        Input() = default;

        explicit Input(storage_type s) : text_(std::move(s)) {}

        // construct from iterator range if you ever need it
        template <std::input_iterator It, std::sentinel_for<It> Sent>
        Input(It first, Sent last) : text_(first, last) {}

        [[nodiscard]] const_iterator begin() const noexcept { return text_.begin(); }
        [[nodiscard]] const_iterator end()   const noexcept { return text_.end();   }
        [[nodiscard]] bool empty()  const noexcept          { return text_.empty(); }
        [[nodiscard]] size_type size() const noexcept       { return text_.size();  }

        //[[nodiscard]] storage_type data() const noexcept { return text_; }
        //const value_type& operator[](size_type i) const { return text_[i]; }

        [[nodiscard]] string_view view() const noexcept { return string_view(text_); }

        // factories

        static Input of(const string& example) { return Input(example); }

        static Input of(int day) {
            std::ifstream in(format("../../aoc/data/input_day{:02}.txt", day));
            if (!in) throw std::runtime_error("cannot open file");

            std::ostringstream ss;
            ss << in.rdbuf();
            return Input(ss.str());
        }
    };

    // input adapter

    constexpr string_view trim(const string_view sv) noexcept {
        auto is_space = [](const unsigned char c) { return std::isspace(c) != 0; };

        size_t first = 0;
        while (first < sv.size() && is_space(static_cast<unsigned char>(sv[first]))) {
            ++first;
        }

        size_t last = sv.size();
        while (last > first && is_space(static_cast<unsigned char>(sv[last - 1]))) {
            --last;
        }

        return sv.substr(first, last - first);
    }

    /*
     * One note here: converting them into string_view makes it more convenient
     * in some cases but limits the usage (split returns a range on chars, which is
     * more flexible, i.e. for a transpose view).
     */

    inline constexpr auto as_line_views =
        std::views::split('\n')
      | std::views::transform([](auto&& sub) -> string_view {
            auto first = sub.begin();
            auto last  = sub.end();
            if (first == last) { return {}; }

            auto ptr = std::to_address(first);
            auto len = static_cast<size_t>(std::ranges::distance(first, last));
            return {ptr, len};
        });

    inline constexpr auto as_block_views =
        as_line_views
      | std::views::split(std::array{string_view{}})
      | std::views::filter([](auto&& block) { return !std::ranges::empty(block); });

    inline constexpr auto first_block_view =
        std::views::drop_while([](auto const& s) { return s.empty(); })
      | std::views::take_while([](auto const& s) { return !s.empty(); });

    inline constexpr auto to_trimmed_lines =
        std::views::transform([](auto&& e) { return trim(string_view(e)); })
      | std::views::filter([](string_view sv) { return !sv.empty(); })
    //| std::views::transform([](string_view sv) { return string(sv); })
      | std::ranges::to<Lines>();

    inline constexpr auto as_std_lines = as_line_views | first_block_view;

}

#endif // AOC_INPUT
