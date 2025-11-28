// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * This snippet demonstrates a SmallBuffer container class that
 * uses Small Buffer Optimization (SBO).
 *  – SmallBuffer<T,N> is a vector-like container that can store N elements inline.
 *  – When size exceeds N, it switches to heap allocation.
 *  – Implements rule of three/five (destructor, copy constructor/assignment,
 *    move constructor/assignment).
 *  – Shows memory management principles using both stack and heap storage.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <cstdlib>
#include <memory>
#include <vector>
#include <initializer_list>
#include <algorithm>                        // std::copy, std::move

using std::cout, std::endl, std::ostream;
using std::string, std::string_view;
using std::runtime_error;
using std::copy, std::move, std::initializer_list;

void testing_smallbuffer_class();

int main() {
    cout << endl << "--- " << __FILE__ << " ---" << endl << endl;

    testing_smallbuffer_class();

    return EXIT_SUCCESS;
}

/*
 * A very small vector-like container with Small Buffer Optimization (SBO).
 *    - Stores up to N elements inline (inside the object, no heap).
 *    - If more than N elements are pushed, it switches to heap allocation.
 *    - Demonstrates: RAII, rule of five, (move semantics,) SBO trade-offs.
 *
 * The rule of five (previously rule of three) defines the five special
 * member functions that manage ownership and resources in a class:
 *    - Destructor: Clean up owned resources (heap memory, files, etc).
 *    - Copy constructor: Make a copy of data from source object.
 *    - Copy assignment: Clean up existing data and make a copy from source.
 *    - Move constructor: Transfer ownership of resources from source (from C++11).
 *    - Move assignment: Clean up and transfer ownership from source (from C++11).
 *
 * Best practice is to implement all five (or three, if you skip moves)
 * if you implement any, since they work together.
 */
template <typename T, size_t N = 4>
class SmallBuffer {
public:
    // Default ctor: No elements, capacity N, data points to inline storage.
    SmallBuffer() noexcept
        : _size(0), _capacity(N), _data(_inline) {}

    // Shows how we decide between inline vs heap storage.
    SmallBuffer(initializer_list<T> init)
        : _size(init.size()),
          _capacity(_size <= N ? N : _size),
          _data(_size <= N ? _inline : new T[_capacity]) {
        copy(init.begin(), init.end(), _data);
    }

    // Copy ctor (not optimized fpr DRY, could use some delegation pattern here)
    SmallBuffer(const SmallBuffer &other)
        : _size(other._size),
          _capacity(other._size <= N ? N : other._size),
          _data(_size <= N ? _inline : new T[_capacity]) {
        copy(other._data, other._data + _size, _data);
    }

    // Copy assignment, any issues here? (also not optimized)
    SmallBuffer& operator=(const SmallBuffer &other) {
        if (this == &other) return *this;   // self-assignment guard

        if (!using_inline())                // free heap data if any
            delete[] _data;

        _size     = other._size;
        _capacity = other._size <= N ? N : other._size;
        _data     = (_size <= N) ? _inline : new T[_capacity];

        copy(other._data, other._data + _size, _data);
        return *this;
    }

    // Move ctor (will be discussed)
    // SmallBuffer(SmallBuffer &&other) noexcept

    // Move assignment (will be discussed)
    // SmallBuffer& operator=(SmallBuffer &&other) noexcept

    /*
     * Remarks
     *
     * The copy assignment is not exception-safe and actually dangerous.
     * If 'new' throws bad_alloc, data is already deleted.
     *
     * Later we can use the classic copy-and-swap pattern, but we skip this here.
     * Idea: parameter is taken by value
     *      SmallBuffer& operator=(SmallBuffer other) noexcept {
     *          swap(*this, other);
     *          return *this;
     *      }
     */

    // dtor
    ~SmallBuffer() {
        if (!using_inline())
            delete[] _data;
    }

    [[nodiscard]] size_t size() const noexcept     { return _size; }
    [[nodiscard]] size_t capacity() const noexcept { return _capacity; }
    bool empty() const noexcept                    { return _size == 0; }

    T& operator[](size_t i)             { return _data[i]; }
    const T& operator[](size_t i) const { return _data[i]; }

    void push_back(const T &value) {
        ensure_capacity(_size + 1);
        _data[_size++] = value;
    }

    friend ostream& operator<<(ostream &os, const SmallBuffer &sb) {
        os << "[";
        for (size_t i = 0; i < sb.size(); ++i) {
            os << sb[i];
            if (i < sb.size() - 1) os << ", ";
        }
        return os << "] ("
            << "inline=" << sb.using_inline()
            << ", size=" << sb.size()
            << ", capacity=" << sb.capacity()
            << ")";
    }

private:
    size_t _size;                           // number of used elements
    size_t _capacity;                       // total capacity of the current buffer
    T*     _data;                           // points to either _inline or heap-allocated array
    T      _inline[N];                      // SBO: small inline buffer (always constructed, trade-off).

    bool using_inline() const noexcept { return _data == _inline; }

    void ensure_capacity(size_t desired) {
        if (desired <= _capacity) return;

        size_t newCap = _capacity * 2;
        if (newCap < desired) newCap = desired;

        T* newData = new T[newCap];

        // Move existing elements into buffer (cheap for movable types).
        move(_data, _data + _size, newData);

        if (!using_inline())
            delete[] _data;

        _data     = newData;
        _capacity = newCap;
    }
};

void testing_smallbuffer_class() {
    cout << "\n" << __func__ << "\n" << string(string_view(__func__).size(), '=') << endl;

    SmallBuffer<int, 4> sb = {1, 2, 3};
    cout << " 1| sb=" << sb << endl;

    sb.push_back(4); // still inline
    cout << " 2| sb=" << sb << endl;

    sb.push_back(5); // now moves to heap
    cout << " 3| sb=" << sb << endl;
}
