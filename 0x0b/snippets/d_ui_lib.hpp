// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * Header-only UI library demonstrating:
 *  - EventHandler: Template-based event system for callback management
 *  - Widget base class: Non-copyable/movable design pattern for UI elements
 *  - Button: Event-driven widget with click handling
 *  - CommandButton: Template button binding specific commands to click events
 *  - Namespace organization and inline/extern variable declarations
 */

#ifndef D_UI_LIB_HPP                        // standard, fully portable
#define D_UI_LIB_HPP

// #pragma once                             // supported by essentially all mainstream compilers

#include <functional>
#include <string>
#include <utility>
#include <vector>
#include <iostream>

// globals
inline int default_margin = 3;              // inline prevents multiple definitions (linker: duplicate symbols)
extern double default_alpha;                // refers to some constant externally defined, usually in implementation

// better
namespace ui_lib {
    // example of a declared function
    void print_stats();

    // A simple EventHandler implementation.
    template <class... Args>
    class EventHandler {
        std::vector<std::function<void(Args...)>> handlers_;

    public:
        template <class F>
        void add(F &&f) {                   // any callable compatible with void(Args...)
            handlers_.emplace_back(std::forward<F>(f));
        }

        void operator()(Args... args) const {
            for (auto const &handler: handlers_) 
                handler(args...);
        }
    };

    class Widget {
    public:
        virtual ~Widget() = default;

        // UI widgets are often not safely movable/copyable because other parts hold pointers/references.
        Widget() = default;
        Widget(const Widget&)            = delete;
        Widget& operator=(const Widget&) = delete;
        Widget(Widget&&)                 = delete;
        Widget& operator=(Widget&&)      = delete;
    };

    class Button: public Widget {
        std::string text_;
    public:
        explicit Button(std::string text) : text_(std::move(text)) {}
        [[nodiscard]] const std::string& text() const { return text_; }
        
        EventHandler<const Button&> onClick;
        void click() const { onClick(*this); }// usually triggered by input events
    };

    template <typename Command>
    class CommandButton: public Button {
        Command command_;
    public:
        CommandButton(std::string text, Command cmd)
            : Button(std::move(text)), command_(std::move(cmd)) {
            // bind to 'this'; safe here because the widget is non-movable/non-copyable.
            onClick.add([this](const Button& b) { command_(b); });
        }
    };
}

#endif // D_UI_LIB_HPP
