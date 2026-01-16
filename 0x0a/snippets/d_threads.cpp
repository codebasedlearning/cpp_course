// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * This file demonstrates basic thread creation and management
 *  – Creating and starting threads with lambda functions and function pointers
 *  – Thread timing and identification using custom timestamp utility
 *  – Managing multiple threads and joining them to wait for completion
 *  – Passing arguments to threads, including references using std::ref
 *  – Examples include simple worker threads, timed downloads, and simulations
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>
#include <functional>
#include <thread>
#include <chrono>
#include <iomanip>
#include <array>
#include <unordered_map>
#include <format>

using std::cout, std::endl, std::ostream;
using std::string, std::string_view, std::format;
using std::thread, std::this_thread::sleep_for;
using std::chrono::milliseconds;
using namespace std::chrono_literals;
using std::array;

void start_first_thread();
void start_thread_with_timing();
void start_multiple_threads();
void start_array_of_threads();
void using_ref();

int main() {
    cout << endl << "--- " << __FILE__ << " ---" << endl << endl;

    start_first_thread();
    start_thread_with_timing();
    start_multiple_threads();
    start_array_of_threads();
    using_ref();

    return EXIT_SUCCESS;
}

void do_something_important(milliseconds ms) {
    sleep_for(ms);
}

void start_first_thread() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    cout << " 1| start thread" << endl;

    thread([]{
        cout << " a| worker-thread started, work for 200ms, id=" << std::this_thread::get_id() << endl;
        do_something_important(200ms);
        cout << " b| worker-thread done." << endl;
    }).join();

    do_something_important(300ms);

    cout << " 2| main-thread done" << endl;
}

inline string ts(bool reset = false) {
    static auto tm_start = std::chrono::system_clock::now();
    static std::array thread_names = {"Main","Kirk","Leia","Luke","Solo"}; // assume not more than 4 threads
    static std::unordered_map<std::thread::id,int> tm_ids;
    static int tm_id = 0;

    if (reset) tm_start = std::chrono::system_clock::now();
    auto thread_id = std::this_thread::get_id();

    // first is the iterator to the element, 0 is the default value if inserted
    auto [it, inserted] = tm_ids.try_emplace(thread_id, tm_id + 1);
    if (inserted) ++tm_id;
    const auto id = it->second;

    std::chrono::duration<double> elapsed = std::chrono::system_clock::now() - tm_start;
    auto id_str = id-1<thread_names.size() ? thread_names[id-1] : format("{}", thread_id);
    auto short_id = id_str.size() > 4 ? id_str.substr(id_str.size() - 4) : id_str;

    return format("{:6.3f} [{}]", elapsed.count(), short_id);
}

void work() {
    cout << " a| " << ts() << " | worker-thread started, work for 200ms, id=" << std::this_thread::get_id() << endl;
    do_something_important(200ms);
    cout << " b| " << ts() << " | worker-thread done." << endl;
}

void start_thread_with_timing() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    cout << " 1| " << ts() << " | start thread" << endl;

    // call it with a worker function
    auto t = thread(work);
    cout << "  | " << ts() << " | thread-id=" << t.get_id() << endl;
    do_something_important(300ms);

    t.join();

    cout << " 2| " << ts() << " | main-thread done" << endl;
}

void download(milliseconds ms) {
    cout << " a| " << ts() << " | download started, load for " << ms << endl;
    do_something_important(ms);
    cout << " b| " << ts() << " | download done." << endl;
}

void start_multiple_threads() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    ts(true); // reset
    cout << " 1| " << ts() << " | start Kirk" << endl;

    auto kirk = thread(download, 200ms);
    do_something_important(50ms);

    cout << " 2| " << ts() << " | start Leia" << endl;
    auto leia = thread(download, 300ms);
    do_something_important(50ms);

    cout << " 3| " << ts() << " | start Luke" << endl;
    auto luke = thread(download, 200ms);
    do_something_important(50ms);

    kirk.join();
    leia.join();
    luke.join();

    cout << " 2| " << ts() << " | main-thread done" << endl;
}

void start_array_of_threads() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    ts(true); // reset
    cout << " 1| " << ts() << " | start worker threads at 100ms intervals" << endl;

    array<thread,4> threads;
    for (size_t i=0; i<threads.size(); ++i) {
        threads[i] = thread(download,milliseconds(i*100+500));
        do_something_important(100ms);
    }

    cout << " 2| " << ts() << " | wait for threads (join)" << endl;
    for (auto & t : threads)
        t.join();
}

void simulation(milliseconds ms, int init, int& result) {
    cout << " a| " << ts() << " | simulation started, runs about " << ms << endl;
    do_something_important(ms);
    result = init * 2;
    cout << " b| " << ts() << " | simulation done." << endl;
}

void using_ref() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    ts(true); // reset
    cout << " 1| " << ts() << " | start threads with args" << endl;

    int result1, result2;
    auto t1 = thread(simulation, 100ms, 10, std::ref(result1));
    auto t2 = thread(simulation, 200ms, 20, std::ref(result2));

    t1.join();
    t2.join();

    cout << " 2| " << ts() << " | result1=" << result1 << ", result2=" << result2 << endl;
}
