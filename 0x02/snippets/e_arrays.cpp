// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 *
 */

#include <iostream>
#include <string>
#include <string_view>
#include <array>
#include <vector>
#include <cstdlib>

using std::cout, std::endl;
using std::string, std::string_view;
using std::array;
using std::vector;

void use_raw_arrays() {
	cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

	/*
	 * An array of data type int with length 'dim', initialized with values 2,3,5.
	 *   – The array brackets [] are placed after the variable name.
     *   – The dimension must be a constant expression.
     *   – The array is created at this point and allocates space for 'dim' elements.
	 *   – Elements can be accessed (read, write) using indices from 0 to dim-1.
     *     Accessing elements with index < 0 or >= dim causes undefined behavior.
	 */
	const int dim{3};
	int a[dim] { 2, 3, 5 };
	
	cout << " 1| dim=" << dim << endl;
	cout << " 2| a[0]=" << a[0]	<< ", a[1]=" << a[1] << ", a[2]=" << a[2] << endl;

	a[0] = 1;
	a[1] = 1;
	a[2] = a[1]+a[0];
	// a[3] = 1234;							// error?
	cout << " 3| a[0]=" << a[0] << ", a[1]=" << a[1] << ", a[2]=" << a[2] << endl;
}

void use_arrays() {
	cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

	/*
	 * std::array<> is a generic array type that provides standard container functions like size().
	 * The array length is fixed and specified as second template parameter.
     * The at() member function performs bounds checking.
	 */
	const int dim{3};
	array<int,dim> f{5, 6, 8};
	f[2] = 7;
	// f[3] = 9;
	cout << " 1| f[0]=" << f[0] << ", f[1]=" << f[1] << ", f[2]=" << f[2] << ", f[2]=" << f.at(2) << endl;
}

void use_vectors() {
	cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

	/*
	 * std::vector<> is a generic array type that can grow dynamically, unlike std::array<>.
	 * push_back() adds elements at the end.
	 */
	vector<int> v{1,2};
	v.push_back(4);
	v[2] = 3;
	cout << " 1| v[0]=" << v[0] << ", v[1]=" << v[1] << ", v[2]=" << v[2] << ", v[2]=" << v.at(2) << endl;
}

int main() {
	cout << "\n--- " << __FILE__ << " ---" << endl;

	use_raw_arrays();
	use_arrays();
	use_vectors();
    
    return EXIT_SUCCESS;
}
