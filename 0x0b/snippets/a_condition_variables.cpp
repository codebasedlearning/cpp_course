// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * This file demonstrates condition variables for thread synchronization.
 *  – Condition variables: Enable threads to wait for specific conditions before proceeding.
 *  – unique_lock: Required for condition variables; allows locking/unlocking during wait.
 *  – Pattern: Worker thread waits for signal from main thread before processing data.
 *  – while(!done) loop: Protects against spurious wakeups by rechecking the condition.
 *  – Timing: Delays demonstrate race conditions if done flag is not used with cv.wait().
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <mutex>

using std::cout, std::endl, std::ostream;
using std::string, std::string_view, std::format;
using std::thread, std::this_thread::sleep_for;
using std::chrono::milliseconds;
using namespace std::chrono_literals;
using std::lock_guard, std::unique_lock;
using std::condition_variable;
using std::mutex;

void use_condition_vars();

int main() {
    cout << endl << "--- " << __FILE__ << " ---" << endl << endl;

    use_condition_vars();

    return EXIT_SUCCESS;
}

/*
 * The general idea is as follows. There is a worker that processes data in the
 * background. But only when the data has been loaded in the main thread.
 * For this, the thread receives a signal that the data is now ready. Both main
 * and the thread can still do smaller work beforehand. The interesting part is
 * the timing between main and worker. With
 *      while(!done)
 * it always works. However, if you comment out this line in the worker, you can
 * force a problem, e.g., with
 *      delay_main = 0ms;
 *      delay_worker = 100ms;
 * Otherwise, the delays control who gets the mutex first.
 */
auto delay_main = 10ms;
auto delay_worker = 10ms;

void process_data(const milliseconds ms) { sleep_for(ms); }     // dummy

condition_variable cv;                                          // For simplicity all global.
mutex mx;
volatile bool done = false;

void worker() {
    cout << " a| thread started, wait for mutex" << endl;

    process_data(delay_worker);

    unique_lock<mutex> lk(mx);              // see below
    cout << " b| mutex OK, wait for signal" << endl;

    while(!done)                            // see below
        cv.wait(lk);
    cout << " c| got signal, process image" << endl;

    process_data(10ms);
    cout << " d| thread done" << endl;

    /*
     * A unique_lock can be locked and unlocked. A lock_guard will be locked
     * only once on construction and unlocked on destruction.
     * Here we need to unlock in wait.
     *
     * The while loop is started only if the signal has not yet been sent.
     * The loop is necessary because the wait is sometimes left "by mistake"
     * and then immediately must be back into the waiting state (spurious wakeup).
     */
}

void use_condition_vars() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    cout << " 1| start thread" << endl;
    thread t1(worker);

    process_data(delay_main);
    {
        lock_guard<mutex> lk(mx);

        cout << " 2| process data" << endl;
        process_data(10ms);

        cout << " 3| signal" << endl;
        done = true;
        cv.notify_one();
    }

    cout << " 4| join" << endl;
    t1.join();
}
