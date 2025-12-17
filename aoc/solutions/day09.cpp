// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * AoC Day 09 solution.
 */

#include "aoc.hpp"

namespace {
    constexpr std::array examples =  {
R"(
7,1
11,1
11,7
9,7
9,5
2,5
2,3
7,3
)",
    };
}

aoc::RC toRC(const string_view line) {
    // special version: col first
    const auto p = line.find(',');
    return {
        aoc::to_number<int64_t>(line.substr(p + 1)),
        aoc::to_number<int64_t>(line.substr(0, p))
    };
}

struct Rect {
    int64_t r1, c1, r2, c2;

    [[nodiscard]] int64_t height() const { return std::abs(r2 - r1) + 1; }
    [[nodiscard]] int64_t width() const { return std::abs(c2 - c1) + 1; }
    [[nodiscard]] int64_t area() const { return width() * height(); }
};

/*
 * Is rectangle fully inside? Note: Even if all 4 corners are inside, a rectangle edge
 * could still cross out of the polygon if the polygon boundary slices through the edge
 * somewhere in the middle.
 *
 * ProperCut function properCut_with_HRect checks whether a polygon vertical edge crosses
 * a horizontal rectangle edge at a point that is strictly interior to both segments.
 * Same, swapped, for properCut_HEdge_with_VRect.
 */

struct VEdge {
    int64_t x, y0, y1; // store y0<y1

    VEdge(const int64_t x, const int64_t y0, const int64_t y1)
        : x(x), y0(std::min(y0,y1)), y1(std::max(y0,y1)) { }

    [[nodiscard]] bool properCut_with_HRect(const int64_t yR, int64_t x0, int64_t x1) const {
        // drop due to normalization: if (x0 > x1) std::swap(x0, x1);
        return (x0 < x && x < x1) && (y0 < yR && yR < y1); // strictly interior on both
    }
};

struct HEdge {
    int64_t y, x0, x1; // store x0<x1

    HEdge(const int64_t y, const int64_t x0, const int64_t x1)
        : y(y), x0(std::min(x0,x1)), x1(std::max(x0,x1)) { }

    [[nodiscard]] bool properCut_with_VRect(const int64_t xR, int64_t y0, int64_t y1) const {
        // drop due to normalization: if (y0 > y1) std::swap(y0, y1);
        return (y0 < y && y < y1) && (x0 < xR && xR < x1); // strictly interior on both
    }
};

struct OrthoEdges {
    std::vector<VEdge> v;
    std::vector<HEdge> h;

    explicit OrthoEdges(const size_t n) { v.reserve(n); h.reserve(n); }

    // Checks if rc lies on any polygon edge (inclusive).
    [[nodiscard]] bool isOnBoundary(const aoc::RC &rc) const {
        static constexpr auto betweenInc = [](int64_t lo, int64_t hi, int64_t v) {
            // drop due to normalization: if (lo > hi) std::swap(lo, hi);
            return lo <= v && v <= hi;
        };

        if (std::ranges::any_of(h, [&](const auto &h) { return rc.row == h.y && betweenInc(h.x0, h.x1, rc.col); }))
            return true;
        if (std::ranges::any_of(v, [&](const auto &v) { return rc.col == v.x && betweenInc(v.y0, v.y1, rc.row); }))
            return true;
        return false;
    }

    /*
     * 'point in polygon' check (inclusive) for a simple orthogonal polygon using ray casting:
     *  - If rc is on boundary → inside.
     *  - Otherwise, cast a ray from rc to the +x direction and count how many times it crosses
     *    polygon vertical edges.
     *  - Use parity: odd = inside, even = outside.
     * The key detail is the half-open rule in y. This avoids double-counting when the ray hits
     * exactly at a vertex (one of the two incident vertical edges gets counted, not both).
     */
    [[nodiscard]] bool containsPoint(const aoc::RC &rc) const {
        if (isOnBoundary(rc)) return true;

        bool inside = false;
        for (const auto [x, y0, y1] : v) {
            if (y0 <= rc.row && rc.row < y1) {   // half-open rule
                if (x > rc.col) inside = !inside;
            }
        }
        return inside;
    }

    // cached version
    bool containsPointCached(const aoc::RC &rc, std::unordered_map<aoc::RC,bool> &cache) const {
        if (const auto it = cache.find(rc); it != cache.end()) return it->second;

        bool inside = containsPoint(rc);
        cache.emplace(rc, inside);
        return inside;
    }

    /*
     * rectangle check:
     *  – Normalize rectangle coords (rMin/rMax, cMin/cMax)
     *  - Construct the four corners A,B,C,D
     *  - Require all 4 corners inside-or-on-boundary
     *  - Require no proper cuts
     */
    bool containsRectCached(const Rect &rect, std::unordered_map<aoc::RC,bool> &cache) const {
        const int64_t rMin = std::min(rect.r1, rect.r2);
        const int64_t rMax = std::max(rect.r1, rect.r2);
        const int64_t cMin = std::min(rect.c1, rect.c2);
        const int64_t cMax = std::max(rect.c1, rect.c2);

        if (const aoc::RC A{rMin,cMin}; !containsPointCached(A, cache)) return false;
        if (const aoc::RC B{rMin,cMax}; !containsPointCached(B, cache)) return false;
        if (const aoc::RC C{rMax,cMax}; !containsPointCached(C, cache)) return false;
        if (const aoc::RC D{rMax,cMin}; !containsPointCached(D, cache)) return false;

        /*
         * Rect edges:
         *  - AB: horizontal at y=rMin, x in [cMin,cMax]
         *  - CD: horizontal at y=rMax, x in [cMin,cMax]
         *  - BC: vertical   at x=cMax, y in [rMin,rMax]
         *  - DA: vertical   at x=cMin, y in [rMin,rMax]
         */

        // Horizontal rect edges can only be properly cut by polygon vertical edges
        if (std::ranges::any_of(v, [&](const auto &ve) {
            return ve.properCut_with_HRect(rMin, cMin, cMax) || ve.properCut_with_HRect(rMax, cMin, cMax);
        })) return false;

        // Vertical rect edges can only be properly cut by polygon horizontal edges
        if (std::ranges::any_of(h, [&](const auto &he) {
            return he.properCut_with_VRect(cMax, rMin, rMax) || he.properCut_with_VRect(cMin, rMin, rMax);
        })) return false;

        return true;
    }

    /*
     * Takes the polygon vertices in order and converts each consecutive pair into either:
     *  - a horizontal edge: HEdge{ y, x0, x1 }
     *  - a vertical edge: VEdge{ x, y0, y1 }
     */
    static OrthoEdges of(const std::vector<aoc::RC>& poly) {
        const auto n = poly.size();
        OrthoEdges edges(n / 2);

        for (size_t i = 0; i < n; ++i) {
            const auto [arow, acol] = poly[i];
            const auto [brow, bcol] = poly[(i+1)%n];

            if (arow == brow && acol != bcol) {
                edges.h.emplace_back(arow, acol, bcol); // save normalized
            } else if (acol == bcol && arow != brow) {
                edges.v.emplace_back(acol, arow, brow);
            }
        }
        return edges;
    }
};

aoc::solutions solve(std::ranges::input_range auto&& lines) {
    auto poly = lines
            | std::views::transform([](const string_view sv) { return toRC(sv); })
            | std::ranges::to<std::vector>();

    auto edges = OrthoEdges::of(poly);

    std::unordered_map<aoc::RC, bool> pipCache;
    pipCache.reserve(poly.size() * poly.size() / 2);

    int64_t sum1 = 0;
    int64_t sum2 = 0;

    for (size_t i = 0; i < poly.size(); ++i) {
        for (size_t j = i+1; j < poly.size(); ++j) {
            const auto rc = Rect{poly[i].row, poly[i].col, poly[j].row, poly[j].col};
            const auto sz = rc.area();
            if (sz > sum1) sum1 = sz;

            if (edges.containsRectCached(rc, pipCache)) {
                if (sz > sum2) sum2 = sz;
            }
        }
    }

    return {sum1,sum2};
}

int main() {
    println("\n--- {} ---\n", __FILE__);

    constexpr auto day = 9;
    constexpr auto example = -1;
    aoc::println(day, example);

    const auto input = (example >= 0) ? aoc::Input::of(examples[example]) : aoc::Input::of(day);
    auto lines = input | aoc::as_std_lines;

    auto [answer, ms] = aoc::measure([&] { return solve(lines); });
    aoc::println(answer, ms);

    // 4725826296 (50), 1637556834 (24)
    if constexpr (example==-1) { assert(answer.part1==4725826296 && answer.part2==1637556834); } // 15.59ms
    if constexpr (example==0) { assert(answer.part1==50 && answer.part2==24); }

    return EXIT_SUCCESS;
}
