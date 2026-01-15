// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * This file demonstrates mutex usage for thread synchronization.
 *  – Race conditions: Occurs when multiple threads access shared data without synchronization (work_v1).
 *  – std::mutex: Provides mutual exclusion to protect critical sections using lock/unlock (work_v2).
 *  – std::lock_guard: RAII-style lock management that automatically releases the mutex (work_v3).
 *  – Example shows three variants of concurrent sum modification to illustrate safe vs unsafe threading.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>
#include <functional>
#include <thread>
#include <array>
#include <mutex>

using std::cout, std::endl, std::ostream;
using std::string, std::string_view, std::format;
using std::thread, std::this_thread::sleep_for;
using std::array;
using std::thread, std::mutex, std::lock_guard;
using std::function;

void start_races();

int main() {
    cout << endl << "--- " << __FILE__ << " ---" << endl << endl;

    start_races();

    return EXIT_SUCCESS;
}

mutex mutex_sum;
using sum_t = long long;

void work_v1(sum_t inc, sum_t n, sum_t& sum);
void work_v2(sum_t inc, sum_t n, sum_t& sum);
void work_v3(sum_t inc, sum_t n, sum_t& sum);

void start_races() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    cout << " 1| start threads" << endl;

    array worker = { work_v1, work_v2, work_v3 };
    constexpr int variant = 0;

    constexpr sum_t n = 1000;
    sum_t sum{0};
    thread t1(worker[variant], +1, n, std::ref(sum));
    thread t2(worker[variant], -1, n, std::ref(sum));

    cout << " 2| join, wait for threads" << endl;
    t1.join();
    t2.join();
    cout << " 3| all done, sum=" << sum << endl;
}

void work_v1(sum_t inc, sum_t n, sum_t& sum) {
    cout << " a| start thread" << endl;
    for (sum_t i=0; i<n; ++i) {
        sum += inc;
    }
    cout << " b| thread done" << endl;
}

void work_v2(sum_t inc, sum_t n, sum_t& sum) {
    cout << " a| start thread" << endl;
    for (sum_t i=0; i<n; ++i) {
        mutex_sum.lock();
        sum += inc;
        mutex_sum.unlock();
    }
    cout << " b| thread done" << endl;
}

void work_v3(sum_t inc, sum_t n, sum_t& sum) {
    cout << " a| start thread" << endl;
    for (sum_t i=0; i<n; ++i) {
        lock_guard<mutex> lk(mutex_sum);
        sum += inc;
    }
    cout << " b| thread done" << endl;
}
