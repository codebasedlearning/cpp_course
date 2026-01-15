// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * Demonstrates input/output operations:
 *  – String stream operations (istringstream/ostringstream) for parsing and formatting.
 *  – Modern C++20/23 formatting with std::format and std::print/println.
 *  – File I/O with ifstream/ofstream for reading and writing files.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <format>

using std::cout, std::endl;
using std::string, std::string_view;
using std::istringstream, std::ostringstream, std::ifstream, std::ofstream;
using std::print, std::println, std::format;
using std::vector;

void using_string_streams();
void using_print_and_format();
void preparing_print_and_format();
void using_file_streams();

int main() {
    cout << endl << "--- " << __FILE__ << " ---" << endl << endl;

    using_string_streams();
    using_print_and_format();
    preparing_print_and_format();
    using_file_streams();

    return EXIT_SUCCESS;
}

void using_string_streams() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    cout << " 1| read from a string value by value" << endl;

    string lines = "S1 123\nS2 456";
    istringstream is1(lines);               // now it is a stream

    string s1, s2;
    int n1, n2;

    is1 >> s1 >> n1 >> s2 >> n2;            // assume, the format is fixed and error free

    cout << " 2| -> s1=" << s1 << ", n1=" << n1 << ", s2=" << s2 << ", n2=" << n2 << endl << endl;

    cout << " 3| read a string line by line" << endl;

    istringstream is2(lines);
    if (is2) {
        string line;
        while (getline(is2,line)) {
            cout << " 4| -> line: '" << line << "'" << endl;

            istringstream sline(line);
            string s;
            int n;
            sline >> s >> n;
            cout << " 5| -> s:" << s << ", n:" << n << endl;
        }
    }
    cout << endl;

    cout << " 6| and back to string" << endl;
    ostringstream os;
    os << " 7| " << 123 << ", 0x" << std::hex << 0x1234 << std::dec << ", "  << 124 << endl
       << ", |" << std::setfill('-') << std::setw(10) << std::setprecision(5) << 12.345678 << "|" << endl;
    // string s = os.str();
    cout << os.str() << endl;
}

void using_print_and_format() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    // ints
    {
        auto s1 = std::format("{}", 23);
        cout << " 1| '" << s1 << "'" << endl;

        auto s2 = std::format("{:5}", 42);          // width (and right-aligned)
        cout << " 2| '" << s2 << "'" << endl;

        auto s3 = std::format("{:<5}", 42);         // left aligned
        cout << " 3| '" << s3 << "'" << endl;

        auto s4 = std::format("{:05}", 42);         // zero-padded
        cout << " 4| '" << s4 << "'" << endl;

        auto s5a = std::format("{:+05}", 42);       // with sign
        auto s5b = std::format("{:+05}", -42);
        cout << " 5| '" << s5a << "'" << endl
             << "  | '" << s5b << "'" << endl;

        auto s6a = std::format("{:#x}", 254);       // hex
        auto s6b = std::format("{:#b}", 10);        // bin
        auto s6c = std::format("{:#o}", 10);        // oct
        cout << " 6| '" << s6a << "'" << endl
             << "  | '" << s6b << "'" << endl
             << "  | '" << s6c << "'" << endl;

        /*
         * From here, we use print or println (with line-feed) directly (C++23).
         * std::print with format info:
         *  – Formats directly into the output buffer.
         *  – Typically no intermediate allocation.
         *  – Faster, fewer temporaries.
         */

        // auto s2 = std::format("{:5}", 42);
        // cout << ...
        println(" 7| '{:5}'", 42);

        /*
         * std::print also has type checks for all parameters.
         */
        println(" 8| n={}, s='{}'", 23, "Text");

        /*
         * Also with ostream (not clear if standard).
         */
        println(cout," 9| '{:5}' \n", 99);
    }

    // floating-points
    {
        auto pi = 3.14159;

        println("11| '{:.3f}'", pi);        // Precision (decimal places)

        println("12| '{:8.2f}'", pi);       // Width + precision

        println("13| '{:08.2f}'", 3.14159); // Zero-padded

        auto d = 1234.0;

        println("14| '{:.2e}'", d);         // Scientific

        println("15| '{:.4g}' \n", d);      // General
    }

    // strings
    {
        auto s = "HoHoHo";

        println("21| '{:>10}'", s);         // Width (right-aligned)

        println("22| '{:<10}'", s);         // Left-aligned

        println("23| '{:^10}'", s);         // Centered

        println("24| '{:.3}'", s);          // Truncate

        println("25| '{:>6.3}' \n", s);     // Width + truncate
    }

    // exotic
    {
        // log line
        println("31| |id:{:04} |val:{:8.2f} |name:{:<10}|", 7, 1.23456, "node");

        // filled text
        println("32| '{:*^10}'", "Ho");     // "****Ho****"
        println("33| '{:_<10}'", "Ho");     // "Ho________"
    }
}

struct A {
    int n;
};

template <>
struct std::formatter<A> {
    constexpr auto parse(std::format_parse_context& ctx) {
        return ctx.begin();  // accept everything (or parse if you want)
    }

    template <typename FormatContext>
    auto format(const A& f, FormatContext& ctx) const {
        return std::format_to(ctx.out(), "({})", f.n);
    }
};

struct B {
    int m;
};

template <>
struct std::formatter<B> : std::formatter<std::string_view> {
    template <typename FormatContext>
    auto format(const B& f, FormatContext& ctx) const {
        std::string tmp = std::format("({})", f.m);
        return std::formatter<std::string_view>::format(tmp, ctx);
    }
};

void preparing_print_and_format() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    A a{42};
    println(" 1| '{}'", a);

    B b{23};
    println(" 2| '{:10}'", b);
}

void using_file_streams() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    vector<string> lines;
    string fileName("../../0x09/snippets/sixlines");

    cout << " 1| read all lines" << endl;

    ifstream file_in(fileName+".txt");      // Read via input file stream.
    // if (!file) throw std::runtime_error("cannot open file");

    if (file_in) {                          // Or with .is_open()
        string line;
        while (getline(file_in,line)) {
            lines.push_back(line);
            if (lines.size()>=5)
                break;
        }
        file_in.close();

        cout << " 2| lines: ";
        for (const auto &line : lines) cout << "'" << line << "' ";
        cout << endl;
    } else {
        cout << " 3| cannot open file" << endl;
    }

    cout << " 4| write lines" << endl;

    /*
    ofstream file_out(fileName+"_copy.txt");
    if (file_out) {
        for (const auto &line : lines) {
            file_out << line << endl;
        }
        file_out.close();
    }
    */
}
