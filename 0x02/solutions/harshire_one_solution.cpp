// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

#include <iostream>
#include <string>
#include <cstdlib>
using std::cout, std::endl, std::ostream;
using std::string;

const size_t stack_dim{3};

// Stack, see https://de.wikipedia.org/wiki/Stapelspeicher
struct stack {
    int buffer[stack_dim];
    size_t next{0};
};

ostream &operator<<(std::ostream& os, const stack& st) {
    std::string delim;
    for (size_t i = 0; i < stack_dim; i++) {
        os << delim << st.buffer[i];
        delim = ", ";
    }
    return os;
}

struct stack_exception {
    string what;
    char level;
};

int pop(stack& st);
void push(stack& st, int n);
void reset(stack& st);

int main() {
    cout << "\n--- " << __FILE__ << " ---" << endl;

    // test code
    stack st;
    cout << "st: " << st << endl;
    reset(st);
    cout << "-> stack after reset: " << st << endl;

    try {
        cout << "push..." << endl;

        push(st, 2);
        cout << "-> st: " << st << endl;

        push(st, 3);
        cout << "-> st: " << st << endl;

        push(st, 5);
        cout << "-> st: " << st << endl;

        push(st, 7);
        cout << "-> st: " << st << endl;
    } catch (const stack_exception& e) {
        cout << "-> error: " << e.what << endl;             // better: cerr
    }

    int num;

    try {
        cout << "pop..." << endl;

        num = pop(st);
        cout << "-> st: " << st << ", num: " << num << endl;

        num = pop(st);
        cout << "-> st: " << st << ", num: " << num << endl;

        num = pop(st);
        cout << "-> st: " << st << ", num: " << num << endl;

        num = pop(st);
        cout << "-> st: " << st << ", num: " << num << endl;
    } catch (const stack_exception& e) {
        cout << "-> error: " << e.what << endl;             // better: cerr
    }

    return EXIT_SUCCESS;
}

int pop(stack& st) {
    if (st.next <= 0) {
        throw stack_exception{"stack empty", 'E'};
    }
    return st.buffer[--st.next];
}

void push(stack& st, int n) {
    if (st.next >= stack_dim) {
        throw stack_exception{"stack full", 'E'};
    }
    st.buffer[st.next++] = n;
}

void reset(stack& st) {
    for (size_t i = 0; i < stack_dim; ++i) {
        st.buffer[i] = 0;
    }
}
