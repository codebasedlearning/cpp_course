// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * This code demonstrates how to use for-loops with continue/break and goto labels.
 * It includes examples of loop control using 'continue' to skip iterations and 'break'
 * to exit early, as well as goto statements with labels for flow control.
 *
 * Labels sometimes appear in existing code. We do not use them. Not at all, under
 * any circumstances. Discuss why not and where the problem lies.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>

using std::cout, std::endl, std::cin;
using std::string, std::string_view;

void for_with_continue_and_break() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    cout << " 1| for (5..10):" << endl;
    for (int i=-10; i<=20; ++i)
    {
        if (i<5)
            continue;                       // 'continue' leads to the next loop iteration, not just in 'for'.
        cout << " 2|   i=" << i << endl;
        if (i>=10)
            break;                          // 'break' terminates the current loop, not just in 'for'.
    }
}

void loop_with_labels() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    cout << " 1| goto (5..10):" << endl;
    int i=5;
    label:                                  // A label named 'label' is defined. This can be jumped to using 'goto'.
        cout << " 2|   i=" << i << endl;
    if ( i++<10)
        goto label;                         // Jump to the label.

    // What is the problem with this construct and why is it not commonly used? See the discussion above.
}

int main() {
    cout << "\n--- " << __FILE__ << " ---" << endl;

    for_with_continue_and_break();
    loop_with_labels();

    return EXIT_SUCCESS;
}
