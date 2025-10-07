// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
using std::cout, std::endl, std::cin;
using std::string;

void cut(double &num_a, double &num_b);
void rotate(string &str_x, string &str_y, string &str_z);

int main() {
    cout << "\n--- " << __FILE__ << " ---\n" << endl;

    double num_a, num_b;

    cout << "Enter num_a (double): "; cin >> num_a;
    cout << "Enter num_b (double): "; cin >> num_b;

    cout << "-> num_a: " << num_a << ", num_b: " << num_b << endl;
    cut(num_a, num_b);
    cout << "-> cut(num_a, num_b)" << endl;
    cout << "-> num_a: " << num_a << ", num_b: " << num_b << endl;

    string str_x, str_y, str_z;

    cout << "Enter str_x (string): "; cin >> str_x;
    cout << "Enter str_y (string): "; cin >> str_y;
    cout << "Enter str_z (string): "; cin >> str_z;

    cout << "-> str_x: " << str_x << ", str_y: " << str_y << ", str_z: " << str_z << endl;
    rotate(str_x, str_y, str_z);
    cout << "-> rotate(str_x, str_y, str_z)" << endl;
    cout << "-> str_x: " << str_x << ", str_y: " << str_y << ", str_z: " << str_z << endl;

    return EXIT_SUCCESS;
}

// cut decimal places
void cut(double &num_a, double &num_b) {
    num_a = floor(num_a);
    num_b = floor(num_b);
}

// rotate args
void rotate(string &str_x, string &str_y, string &str_z) {
    string help{str_x};
    str_x = str_y;
    str_y = str_z;
    str_z = help;
}
