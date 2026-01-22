// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * UI library implementation providing statistics for UI elements.
 * Defines default values and namespace for UI-related functions.
 */

#include <iostream>
#include "d_ui_lib.hpp"                     // note: "file", looks in the including file’s directory first

double default_alpha = 0.3;                 // implementation of "extern" variable

namespace ui_lib {
    void print_stats() {
        std::println(" a| number ui-elements: {}", 123);
    }
}
