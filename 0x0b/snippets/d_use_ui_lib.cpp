// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * This file demonstrates how to use constants, functions and classes from the library.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>

using std::cout, std::endl;
using std::string, std::string_view;

#include "d_ui_lib.hpp"

void button_clicks();

int main() {
    cout << endl << "--- " << __FILE__ << " ---" << endl << endl;

    button_clicks();

    return EXIT_SUCCESS;
}

void button_clicks() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    cout << " 1| default_margin=" << default_margin << endl;
    cout << " 2| default_alpha=" << default_alpha << endl;

    // call function from lib
    ui_lib::print_stats();

    using namespace ui_lib;

    // use classes from lib
    Button button{"Plain"};
    button.onClick.add([](const Button &btn){
        std::cout << " 3| clicked " << btn.text() << std::endl;
    });
    button.onClick.add([](const Button &btn){
        std::cout << " 4| clicked " << btn.text() << std::endl;
    });
    button.click();

    auto cmd = [](const Button& btn){
        std::cout << " 5| command executed from: " << btn.text() << std::endl;
    };
    const CommandButton saveButton{"Save", cmd};
    saveButton.click();
}
