[© 2025, A.Voß, FH Aachen, codebasedlearning.dev](mailto:info@codebasedlearning.dev)

# Unit 0x03

Some notes on classes and constructors.

1) There are special member functions
- Default ctor: `T();`
- Dtor: `~T();`
- Copy ctor: `T(const T&);`
- Copy assignment: `T& operator=(const T&);`
And from C++11 (not yet covered):
- Move ctor: `T(T&&) noexcept;`
- Move assignment: `T& operator=(T&&) noexcept;`

2) The rules
- Rule of Zero: Prefer no custom special members. Let RAII members (`string`, `vector`, smart pointers) manage resources.
- Rule of Three: If you define any of {dtor, copy ctor, copy assign}, you likely need all three (for manual resource management).
- Rule of Five: In C++11+, if you manage resources and define copy ops, also define move ctor and move assign.
- Rule of Big Two (rare): If you only need to forbid copying (e.g., unique ownership), delete copy ctor/assign and provide moves.

3) Defaulting and deleting
- `=default`: Ask the compiler to generate the usual behavior explicitly.
- `=delete`: Forbid a function (e.g., `T(const T&) = delete;`).
- If you declare any ctor, the implicit default ctor is not generated unless you `=default` it.
- If you declare a dtor (non-trivial), the implicit move operations are suppressed; you must provide them if needed.
- If you declare copy ctor or copy assign, implicit move operations are suppressed.

4) Converting vs explicit constructors
- Single-argument ctors act as implicit conversions. Prefer `explicit` for single-arg ctors to avoid surprise: `explicit T(int x);`
- Provide targeted converting ctors only when you want implicit conversions.

5) Copy vs move semantics
- Copy: duplicate state/resources.
- Move: transfer ownership; leave source valid but unspecified. Mark move ops noexcept when possible to enable container optimizations.

6) Best practices
- Aim for Rule of Zero: use standard containers/smart pointers.
- If you must manage resources, implement all five or use copy-and-swap for strong exception safety in `operator=`.
- Keep initialization in member initializer lists; avoid work in bodies when possible.
- Provide default ctor only if a meaningful 'default state' exists.
- Consider `=delete` for operations that don’t make sense (e.g., copying a mutex-like type).


## Tasks

<hr>

### Task 'Ravencastle'

Design your own class `fraction`.
- Implement a default constructor and a destructor (consider whether a default constructor makes sense).
- Implement a constructor taking numerator and denominator; use a member-initializer list.
- Implement getters and setters for the integer numerator and denominator.
- Write meaningful test code.

Extension:

- Implement a copy constructor.
- Implement `operator<<` for output.
- Use `const` wherever possible.

<hr>

### Task 'Stone Ridge'

This task is similar to the previous one. So if you have completely understood the previous task, 
you can skip 'Stone Ridge'.

Design a class `point` with `x` and `y` coordinates.
- Implement a default constructor and a destructor.
- Implement another constructor that takes two doubles (`x` and `y`); use a member-initializer list.
- Implement getters and setters.
- Write meaningful test code.

Extension:

- Implement a copy constructor.
- Implement `operator<<` for output.
- Use `const` wherever possible.

<hr>

### Task 'Lucky Rock'

Design a class `contact` with `age` and `name`.
- Implement a default constructor and a destructor.
- Implement a constructor that takes an `unsigned int age` and a `string name`; use a member-initializer list.
- Implement getters and setters.
- Write meaningful test code.

Extension:

- Implement a copy constructor.
- Implement `operator<<` for output.
- Use const wherever possible.

<hr>

### Task 'Meadow River'

Convert the struct `polynom` from exercise 'Elkford' into a class `polynom`.
- Turn the free function `eval` into a member function.
- Implement a member function `at(i)` that returns the i-th coefficient; 
  throw if `i` is invalid.
- Use a raw array, or the generic class `array` or `vector` from the standard library
  for the coefficients.

Extension:

- Implement a free function `add` that adds two polynomials and returns the result.
- Reuse your 'Elkford' tests and additionally test with dimension 4.

<hr>

### Task 'Coral Creek'

Sometimes, a value is optional: for example, a temperature sensor that may not yet 
have produced data.

Instead of using 'magic numbers' like -1 to mean 'no value,' we wrap the integer in 
a small class `OptionalInt` that knows whether it’s set (similar to `std::optional<int>`). 

Implement a class `OptionalInt` — an integer that may or may not be present. In detail, you need:
- A default constructor that creates an unset value.
- A constructor that takes an integer and sets the value.
- A copy-constructor.
- A destructor (it should print a message).
- A function `hasValue` and a boolean operator that check whether the value is set.
- A getter `getValue` and an int operator that return the value if the value is set, 
  otherwise it throws a `runtime_error`.
- A getter `getValueOr(int fallback)` that returns the value if the value is set, otherwise 
  it returns `fallback`.
- A setter `setValue` that sets the value.
- A function `clear` that clears the value.
- A stream insertion operator `operator<<` that prints the value if the value is set, 
  otherwise it prints 'none'.

Write test code for the class.

Extension preview (i.e. you need to figure it out yourself):

- Make it template-based `MyOptional`.
- Track a 'version' counter each time a value is set.
- Implement equality operators `==`, `!=`.

<hr>

### 👉 Task 'AI'

What would the AI say about it?

Pick your solutions and ask a GenAI-Tool of your choice (e.g., ChatGPT) for its opinion.
- What improvements are suggested?
- Do they make sense?

<hr>

### 👉 Task 'Couch Potato' - Recurring homework.

- If you have not completed the main tasks in the exercise, complete them at home.
- Study `work_stoi_stod` and `work_trailingreturn`.

<hr>

### 👉 Comprehension Check

- I have understood all codes and exercise topics.
- I know the difference between `struct` and `class`. 
- I know how to define a class. 
- I can define constructors, destructors, getters, and setters. 
- I understand the meaning of `const` in the context of member functions. 
- I know when a copy constructor is called and how to use it. 
- I know when a assignment operator is called and how to use it.
- I can write my own `operator<<` for my class.
- I know what RAII stands for.
- I know why there is no 'finally' in C++.
