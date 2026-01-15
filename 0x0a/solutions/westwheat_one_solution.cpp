// (C) 2025 A.Voß, a.voss@fh-aachen.de, cpp@codebasedlearning.dev

/*
 * Westwheat solution.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>
#include <iomanip>
#include <mutex>
#include <vector>
#include <array>
#include <thread>

using std::cout, std::endl, std::ostream;
using std::string, std::string_view;
using std::vector, std::array;
using std::thread, std::mutex, std::lock_guard;

constexpr int n{3};
vector<int> data;

void work_v1() {
    for (int i=0; i<n; ++i)
        data.push_back(i);
}

mutex mutex_data;

void work_v2() {
    for (int i=0; i<n; ++i) {
        std::lock_guard<mutex> lk(mutex_data);
        data.push_back(i);
    }
}

int main() {
    cout << endl << "--- " << __FILE__ << " ---" << endl << endl;

    array worker = { work_v1, work_v2 };
    constexpr int variant = 0;

    cout << " 1| start threads" << endl;

    thread t1(worker[variant]);
    thread t2(worker[variant]);

    cout << " 2| join, wait for threads" << endl;
    t1.join();
    t2.join();
    cout << " 3| all done" << endl;

    return EXIT_SUCCESS;
}
