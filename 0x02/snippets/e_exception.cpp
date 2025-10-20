// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * This snippet demonstrates exception handling in C++:
 *   – Catching any exception using ...
 *   – Catching specific exception types
 *   – Using standard exceptions like runtime_error
 *   – Rethrowing exceptions.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>

using std::cout, std::endl;
using std::string, std::string_view;
using std::runtime_error;

int readFile();

void catch_all() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    cout << " 1| throw double 12.34" << endl;
    try {
        // In C++ technically any possible type can be thrown using throw, though it is not recommended.
        throw 12.34;
    } catch (...) {
        // The catch block can either catch specific types or catch all remaining types using '...'.
        cout << " 2|   catch ..." << endl;
    }
}

void catch_numbers() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    cout << " 1| throw int 23" << endl;
    try {
        throw 23;
    } catch (double d) {                                    // sometimes suggested: const double&
        cout << " 2|   catch double, d: " << d << endl;
    } catch (int n) {
        cout << " 3|   catch int, n: " << n << endl;
    } catch (...) {
        cout << " 4|   catch ..." << endl;
    }
}

void catch_runtime() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    cout << " 1| rethrow in readFile" << endl;
    try {
        readFile();
        // [...]
    } catch (const runtime_error &e) {
        cout << " 2|   catch runtime_error, e: '" << e.what() << "'" << endl;
    } catch (...) {
        cout << " 3|   catch ..." << endl;
    }
}

int main() {
    cout << "\n--- " << __FILE__ << " ---" << endl;

    catch_all();
    catch_numbers();
    catch_runtime();

    return EXIT_SUCCESS;
}

// Dummy-Funktion
int readFile() {
    try {
        cout << " a|   throw runtime_error" << endl;
        // There are some predefined exceptions that can be used, e.g.
        // invalid_argument, out_of_range, domain_error, overflow_error, underflow_error
        throw runtime_error{"file not found"};
    } catch (...) {
        cout << " b|   catch ..." << endl;
        // Note here that the exception is caught and then rethrown.
        throw;
    }
    return 0;
}
