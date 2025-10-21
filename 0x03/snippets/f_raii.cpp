// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * This snippet demonstrates RAII (Resource Acquisition Is Initialization) in C++:
 *   – Resource acquisition during construction
 *   – Automatic cleanup in destructor
 *   – Exception safety with RAII
 *   – Using scope to manage resources.
 *
 * RAII (Resource Acquisition Is Initialization) ties resource lifetime to object lifetime.
 * A resource (file, lock, transaction, memory, etc.) is acquired in a constructor and
 * reliably released in the destructor. This guarantees cleanup on all paths (including
 * exceptions) and enables safe, exception-proof code by managing ownership through scope.
 *
 * Use existing RAII types (string, vector, unique_ptr, lock_guard) or write small wrappers
 * for external resources.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>
#include <thread>
#include <chrono>

using std::cout, std::endl, std::cin;
using std::string, std::string_view;
using std::thread;
using std::chrono::milliseconds, std::chrono::steady_clock, std::chrono::duration_cast;
using std::runtime_error;

// Scope timer: prints elapsed time on destruction.
class ScopeTimer {
    const string label_;
    steady_clock::time_point start_;

public:
    explicit ScopeTimer(const string &label): label_{label}, start_{steady_clock::now()} {}

    ~ScopeTimer() {
        const auto duration = duration_cast<milliseconds>(steady_clock::now() - start_);
        cout << " a|   duration '" << label_ << "':" << duration.count() << " ms" << endl;
    }

    // Non-copyable; copying timers rarely makes sense.
    ScopeTimer(const ScopeTimer&) = delete;
    ScopeTimer& operator=(const ScopeTimer&) = delete;
};

void read_file() {
    cout << " b|   read file... ";
    std::this_thread::sleep_for(milliseconds(200));  // sleep 0.2 s
    cout << "done" << endl;
}

void shrink_data() {
    cout << " c|   shrink... ";
    std::this_thread::sleep_for(milliseconds(300));  // sleep 0.3 s
    cout << "error" << endl;
    throw runtime_error("invalid data in line 1234");
}

void understand_raii() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    cout << " 1| gather data" << endl;
    {
        ScopeTimer t{"read file"};          // Prints elapsed time at scope end.
        read_file();
    }

    cout << " 2| process data" << endl;
    try {
        ScopeTimer t{"shrink"};
        shrink_data();                      // Prints duration even in case of errors.
    }
    catch (const runtime_error &e) {
        cout << " 3| error: " << e.what() << endl;
    }

    cout << " 4| end of function" << endl;
}

int main() {
    cout << "\n--- " << __FILE__ << " ---" << endl;

    understand_raii();

    return EXIT_SUCCESS;
}
