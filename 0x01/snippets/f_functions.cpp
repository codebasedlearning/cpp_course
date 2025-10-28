// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * This snippet discusses:
 *   – Function declarations and definitions
 *   – Recursion with factorial and Fibonacci examples
 *   – The '?' ternary operator
 *   – Function calls and parameter passing
 *   - scopes
 *   - type inference and 'auto'.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>

using std::cout, std::endl, std::cin;
using std::string, std::string_view;

/*
 * From the compiler's perspective, all expressions must be known at least in form and data type.
 * Here the function 'factorial' is defined, after which the compiler knows it and understands that
 * it takes an int as parameter and also returns an int.
 *
 * The function 'fib' is only declared by specifying its signature. It still needs to be defined
 * elsewhere, but for the compiler it's enough to know how it is called and what it returns.
 *
 * Remark: Usually you separate the source code and don't put everything in one file. This is
 * disadvantageous for presentation since you'd constantly jump between codes. That would be
 * doubly confusing on top of the content. Therefore the snippets are (almost) all present in
 * one file – production code would be split up!
 */

int factorial(int n) {
	// '?'-operator returns the second expression if the (first) condition is true, otherwise the third.
	return (n>1) ? n*factorial(n-1) : 1;
}

int fib(int n);

void print_number() {
	cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

	int n=5;
	cout << " 1| factorials and Fibonaccis until i=" << n << ":" << endl;

	int i{0};
	while ((++i)<=n) {						// Note the increment in the expression.
		cout << " 2|   i=" << i
			 << ", " << i << "! = " << factorial(i)
			 << ", " << "f_" << i << ": " << fib(i) << endl;
	}
}

int main()  {
	cout << "\n--- " << __FILE__ << " ---" << endl;

	print_number();

	return EXIT_SUCCESS;
}

// Here is the recursive definition of the function 'fib' (compare this version again iterative one).
int fib(int n) {
	/*
	 * Note:
	 *    – 'result' is only valid within the function, or more generally within the {} block (scope).
	 *    – 'auto' allows the compiler to determine the type of 'result' itself, namely from the type
	 *		of the right side (type inference).
	 *		It is important to understand that this is equivalent to
	 *			int result = ...
	 *		Here 'result' is of no 'dynamic data type' or something similar. It is a plain integer.
	 */
	auto result = (n <= 1) ? n : fib(n - 1) + fib(n - 2);
	return result;
}
