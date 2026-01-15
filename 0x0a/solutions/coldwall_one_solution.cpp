// (C) 2025 A.Voß, a.voss@fh-aachen.de, cpp@codebasedlearning.dev

/*
 * Coldwall solution.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>
#include <iomanip>
#include <memory>
#include <vector>
#include <array>
#include <thread>
#include <chrono>
#include <mutex>
#include <algorithm>

using std::cout, std::endl, std::ostream;
using std::string, std::string_view;
using std::vector, std::array;
using std::thread, std::chrono::milliseconds;

using sum_t = long long;

void work(sum_t start, sum_t end, sum_t &sum) {
    sum_t temp = 0;
    for (sum_t i = start; i <= end; ++i) {
        temp += i;
    }
    // lock_guard<std::mutex> lock(mutex_sum);
    sum += temp;
}

// assume n % num_threads == 0
sum_t calc_sum(sum_t n, size_t num_threads) {
    sum_t part = n / num_threads;

    vector<thread> threads;
    threads.resize(num_threads);
    vector<sum_t> sums;
    sums.resize(num_threads);

    for (size_t i=0; i<num_threads; ++i) {
        threads[i] = thread(work, i * part +1, (i + 1) * part, std::ref(sums[i]));
    }

    for (auto & t : threads) {
        t.join();
    }

    sum_t results = 0;
    for (const auto s : sums) {
        results += s;
    }
    return results;
}

int main() {
    cout << endl << "--- " << __FILE__ << " ---" << endl << endl;

    auto tm_start = std::chrono::high_resolution_clock::now();

    auto sum = calc_sum(10000000, 10);

    std::chrono::duration<double> elapsed = std::chrono::high_resolution_clock::now() - tm_start;

    cout << " 1| sum=" << sum << ", elapsed:" << elapsed.count() << endl;

    return EXIT_SUCCESS;
}
