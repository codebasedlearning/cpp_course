// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * AoC Day 08 solution.
 */

#include "aoc.hpp"

namespace {
    constexpr std::array examples =  {
R"(
162,817,812
57,618,57
906,360,560
592,479,940
352,342,300
466,668,158
542,29,236
431,825,988
739,650,466
52,470,668
216,146,977
819,987,18
117,168,530
805,96,715
346,949,466
970,615,88
941,993,340
862,61,35
984,92,344
425,690,689
)",
    };
}

#include <vector>
#include <numeric>
#include <cstddef>
#include <algorithm>

struct Box {
    int64_t x, y, z;

    static Box of(const string_view line, const char delim = ',') {
        // assume 'x,y,z'
        const auto p1 = line.find(delim);
        const auto p2 = line.find(delim, p1 + 1);
        return {
            aoc::to_number<int64_t>(line.substr(0, p1)),
            aoc::to_number<int64_t>(line.substr(p1 + 1, p2 - (p1 + 1))),
            aoc::to_number<int64_t>(line.substr(p2 + 1))
        };
    }
};

struct BoxPair {
    size_t i{}, j{};
    int64_t dist{};

    static int64_t norm2(const Box& b1, const Box& b2) {
        const int64_t dx = b1.x - b2.x;
        const int64_t dy = b1.y - b2.y;
        const int64_t dz = b1.z - b2.z;
        return (dx*dx + dy*dy + dz*dz); // std::sqrt is not necessary for ordering
    }

    static BoxPair of(const size_t i, const Box& b1, const size_t j, const Box& b2) {
        return BoxPair{i,j,norm2(b1,b2)};
    }
};

// Compare two strategies: nodes vs dsu

// https://en.wikipedia.org/wiki/Disjoint-set_data_structure

struct DSU {
    std::vector<size_t> parent;             //  Galler-Fischer tree
    std::vector<size_t> sz;

    explicit DSU(const size_t n) : parent(n), sz(n, 1) {    // fill with 1
        std::iota(parent.begin(), parent.end(), 0);         // fill with 0 to n-1
    }

    size_t find(size_t x) {
        while (x != parent[x]) {
            parent[x] = parent[parent[x]];  // path halving
            x = parent[x];
        }
        return x;
    }

    // Union by size
    bool unite(size_t x, size_t y) {
        x = find(x);                        // roots
        y = find(y);
        if (x == y) return false;
        if (sz[x] < sz[y]) std::swap(x, y);
        parent[y] = x;
        sz[x] += sz[y];
        return true;
    }

    size_t size(const size_t x) { return sz[find(x)]; }
};

struct Nodes {
    std::unordered_set<size_t> nodes;

    static Nodes of(const size_t i, const size_t j) {
        return Nodes{std::unordered_set{i,j}};
    }
};

aoc::solutions solve(const size_t maxProcessedPart1, std::ranges::input_range auto&& lines, const bool useDSU) {
    auto boxes = lines
            | std::views::transform([](const string_view sv) { return Box::of(sv); })
            | std::ranges::to<std::vector>();

    std::vector<BoxPair> pairs;
    pairs.reserve(boxes.size()*(boxes.size()-1)/2);
    for (size_t i = 0; i < boxes.size(); ++i) {
        for (size_t j = i+1; j < boxes.size(); ++j) {
            pairs.emplace_back(BoxPair::of(i, boxes[i], j, boxes[j]));
        }
    }

    std::ranges::sort(pairs,[](const BoxPair& a, const BoxPair& b) { return (a.dist < b.dist); });

    int64_t sum1 = 1;
    int64_t sum2 = 0;

    BoxPair lastPairPart2;
    size_t processedPart1 = 0;

    if (useDSU) {
        DSU circuits(boxes.size());

        for (const auto &p : pairs) {
            lastPairPart2 = p;

            circuits.unite(p.i, p.j);

            ++processedPart1;
            if (processedPart1 == maxProcessedPart1) {
                std::vector<size_t> sizes;
                sizes.reserve(boxes.size());
                for (size_t i = 0; i < boxes.size(); ++i) {
                    if (circuits.find(i) == i) {          // root
                        sizes.push_back(circuits.sz[i]);  // component size
                    }
                }
                std::ranges::sort(sizes, std::greater{});

                sum1 = int64_t(sizes[0]) * int64_t(sizes[1]) * int64_t(sizes[2]);
                // keep going for part2
            }

            if (circuits.size(0) == boxes.size()) break;
        }
    } else {
        std::vector<Nodes> circuits;
        circuits.reserve(boxes.size());

        for (const auto &p : pairs) {
            lastPairPart2 = p;

            auto it1 = std::ranges::find_if(circuits, [&](const auto& c) { return c.nodes.contains(p.i); });
            auto it2 = std::ranges::find_if(circuits, [&](const auto& c) { return c.nodes.contains(p.j); });

            if (it1 == std::ranges::end(circuits) && it2 == std::ranges::end(circuits)) {
                circuits.emplace_back(Nodes::of(p.i,p.j));
                // never done for more than 2 boxes
            } else if (it1 != std::ranges::end(circuits) && it2 != std::ranges::end(circuits)) {
                if (&*it1 != &*it2) {
                    for (auto x : it2->nodes) it1->nodes.insert(x);
                    if (it1->nodes.size()==boxes.size()) break;
                    circuits.erase(it2);    // remember: vector erase invalidates iterators
                }
            } else if (it1 != std::ranges::end(circuits)) {
                it1->nodes.insert(p.j);
                if (it1->nodes.size()==boxes.size()) break;
            } else if (it2 != std::ranges::end(circuits)) {
                it2->nodes.insert(p.i);
                if (it2->nodes.size()==boxes.size()) break;
            }

            ++processedPart1;
            if (processedPart1==maxProcessedPart1) {
                std::ranges::sort(circuits,[](const Nodes& a, const Nodes& b) { return (a.nodes.size() > b.nodes.size()); });
                sum1 = circuits[0].nodes.size() * circuits[1].nodes.size() * circuits[2].nodes.size();
                // keep going for part2
            }
        }
    }

    auto &b1 = boxes[lastPairPart2.i];
    auto &b2 = boxes[lastPairPart2.j];
    sum2 = b1.x*b2.x;

    return {sum1,sum2};
}

int main() {
    println("\n--- {} ---\n", __FILE__);

    constexpr auto day = 8;
    constexpr auto example = -1;
    aoc::println(day, example);

    const auto input = (example >= 0) ? aoc::Input::of(examples[example]) : aoc::Input::of(day);
    auto lines = input | aoc::as_std_lines;
    constexpr size_t maxProcessedPart1 = (example==-1) ? 1000 : 10;

    // DSU: useDSU = true, Nodes: false
    auto [answer, ms] = aoc::measure([&] { return solve(maxProcessedPart1,lines, true); });
    aoc::println(answer, ms);

    // 84968 (40), 8663467782 (25272)
    if constexpr (example==-1) { assert(answer.part1==84968 && answer.part2==8663467782); } // nodes 26.64ms, dsu 23.16ms
    if constexpr (example==0) { assert(answer.part1==40 && answer.part2==25272); }

    return EXIT_SUCCESS;
}
