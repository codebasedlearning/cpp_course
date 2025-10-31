// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * This file demonstrates standard container examples like
 *  – pairs and tuples (as heterogeneous containers),
 *  – array/vector/deque/list (as contiguous or linked storage),
 *  – set/map (as ordered associative containers), and
 *  – unordered_set/unordered_map (as hash-based containers).
 */

#include <iostream>
#include <string>
#include <cstdlib>
#include <utility>
#include <sstream>
#include <tuple>
#include <array>
#include <vector>
#include <set>
#include <map>
#include <deque>
#include <list>
#include <unordered_set>
#include <unordered_map>

using std::cout, std::endl, std::ostream, std::ostringstream;
using std::string, std::string_view;
using std::pair, std::make_pair, std::tuple, std::make_tuple;
using std::array, std::vector, std::deque, std::list;
using std::set, std::map, std::unordered_set, std::unordered_map;
using namespace std::string_literals;

void using_pairs_and_tuples();
void using_containers();

int main() {
    cout << "\n--- " << __FILE__ << " ---" << endl;

    using_pairs_and_tuples();
    using_containers();

    return EXIT_SUCCESS;
}

/*
 * The C++ Standard defines a "container" as a type that models the Container concept
 * (like vector). These must have begin() and end(), support iteration etc.
 * pair (and tuple) don’t do that, but in a wider, abstract sense, we can call them
 * containers of heterogeneous elements.
 */
void using_pairs_and_tuples() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    const pair<int, double> p1{1, 1.1};
    cout << " 1| p1=(" << p1.first << "," << p1.second << ")" << endl;

    // Pre-C++17 you couldn’t deduce class template arguments from constructors
    // (no Class Template Argument Deduction, CTAD), so factory helpers solved that:
    auto p2 = make_pair(2, 2.2);
    cout << " 2| p2=(" << p2.first << "," << p2.second << ")" << endl;

    auto [fst, snd] = make_pair(3, 3.3);    // structured bindings
    cout << " 3| (fst,snd)=(" << fst << "," << snd << ")" << endl;

    // The interesting part is the member access. Remember that each 'coefficient' has a different
    // type, so a simple loop is not a viable option.
    const tuple<int, double, char> t1 = tuple{1, 1.1, 'A'};
    cout << " 1| t1=(" << get<0>(t1) << "," << get<1>(t1) << "," << get<2>(t1) << ")" << endl;

    const auto t2 = make_tuple(2, 2.2, 'B');
    cout << " 2| t2=(" << get<0>(t2) << "," << get<1>(t2) << "," << get<2>(t2) << ")" << endl;
}

// for printing the pairs
template <typename K, typename V>
ostream& operator<<(ostream &os, const pair<K,V> &x) {
    return os << "(" << x.first << "," << x.second << ")";
}

template <typename T>
string join(const T &container) {
    ostringstream os;
    bool first = true;
    for (const auto &x : container) {
        if (!first) os << ',';
        os << x;
        first = false;
    }
    return os.str();
}

void using_containers() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    // fixed-size contiguous array, random-access.
    const array<int,3> a{2, 3, 5};                 
    cout << " 1| a=[" << join(a) << "]" << endl;

    // dynamic array, random-access, contiguous, fast push_back, O(1) indexing.
    vector<int> v{1, 2, 3};
    v.push_back(4);
    cout << " 2| v=[" << join(v) << "]" << endl;

    // double-ended queue, segmented dynamic array, random-access, efficient push_front/back.
    deque<int> d{1, 2, 3};
    d.push_front(0);
    d.push_back(4);
    cout << " 3| d=[" << join(d) << "]" << endl;

    // doubly linked list, bidirectional iteration, no random access.
    list<int> l{6, 7, 8};
    l.push_front(5);
    l.push_back(9);
    cout << " 4| l=[" << join(l) << "]" << endl;

    // set/map: ordered associative (tree), unique keys, logarithmic find/insert/erase.
    set<int> s{3, 2, 1};
    s.insert(2);
    s.insert(4);
    s.insert(0);
    cout << " 5| s={" << join(s) << "}" << endl;

    map<int, string> m{ {1,"One"}, {2, "Two"} };
    // or: map m{ pair{1,"One"s}, pair{2, "Two"s} };
    m[3] = "Three";
    cout << " 6| m={" << join(m) << "}" << endl;

    // we skip multiset/multimap: ordered with duplicates.

    // unordered_set/unordered_map: hash-based, average O(1) find/insert/erase.
    unordered_set<int> us{3, 2, 1};
    us.insert(2);
    us.insert(4);
    us.insert(0);
    cout << " 7| us={" << join(us) << "}" << endl;

    // or: unordered_map<int, string> um{ {1,"One"}, {2, "Two"} };
    unordered_map um{ pair{1,"One"s}, pair{2, "Two"s} };
    um[3] = "Three";
    cout << " 8| um={" << join(um) << "}" << endl;
}
