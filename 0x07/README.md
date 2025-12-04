[© 2025, A.Voß, FH Aachen, codebasedlearning.dev](mailto:info@codebasedlearning.dev)

# Unit 0x07

## Tasks

<hr>

### 👉 Task 'Dover Town'

Operators

- Implement a class `states` that can contain a set of states, of which exactly one is active. Examples of states: {
  `Locked`, `Unlocked` } or { `Connected`, `Disconnected`, `Unknown` }.
- Internally use a `vector` of `string` to store the states, and an index for the current active state.
- Fundamentally, a specific state should be queryable and settable. Furthermore, the current state can be incremented or
  decremented by one. Of course, states should also be able to be added and all states deleted.
- Implement appropriate operators or functions so that the following code snippets work for a `states` instance `s`:
    - `s+="home"` adds state `home` to `s`.
    - `s=1;` sets current state to the second state.
    - `++s;` increments the current state by one.
    - `--s;` decrements the current state by one. Wrap around to start/end on over/underflow.
    - `s()` returns the current index.
    - `s[s()]` returns the current state (string).
    - `s.clear();` deletes all states.
    - `cout << s;` outputs a vector with all states.
- Test your code.

<hr>

### 👉 Task 'Heart Land'

Operators

- Implement a (generic) class `fastvector` that models a mathematical vector of coefficients with a fixed dimension that
  can be used for calculations. Use `int` if you want to skip the generic part.
- Internally use an `array` of fixed length. The dimension and type are determined by template parameters.
- Fundamentally, addition, subtraction and scalar multiplication should be possible. Of course, individual coefficients
  can be read and set.
- Implement appropriate operators or functions so that the following code snippets work for a `fastvector` instance `v`,
  or `v1` and `v2`:
    - `v=1;` sets all coefficients to a value, here 1.
    - `v1+v2` adds `v1` and `v2`.
    - `v1-v2` subtracts `v2` from `v1`.
    - `v*3` or `3*v` multiply v with a scalar, here 3.
    - `-v` negates all coefficients.
    - `v[i]` reads or writes the i-th coefficient.
    - `cout << v;` outputs the coefficients of `v`.
- Test your code.

<hr>

### 👉 Task 'Deerwoods'

Operators

- Implement a generic class `nullable` that models a mathematical value that can also be `null`.
- Internally use an attribute of the data type determined by the template parameter, and a `bool` that indicates whether
  the value is `null` or not.
- Fundamentally, addition should be possible. Of course, one should be able to test for `null` and set the value to
  `null`.
- Implement appropriate operators or functions so that the following code snippets work for a `nullable` instance `n`,
  or `n1` and `n2`:
    - `n=1;` sets a value, here 1.
    - `n.reset();` means setting `n` to `null`.
    - `n+=3;` adds a value to `n`, here 3.
    - `n1+n2` adds `n1` and `n2`.
    - `!n` tests for `null` and is true if not.
    - `(int)n;` converts to the concrete data type, here `int`.
    - `cout << n;` outputs the value of `n`.
- Test your code.

<hr>

### 👉 Task 'AI'

What would the AI say about it?

Pick your solutions and ask a GenAI-Tool of your choice (e.g., ChatGPT) for its opinion.
- What improvements are suggested?
- Do they make sense?

<hr>

### 👉 Task 'Couch Potato' - Recurring homework.

- If you have not completed the main tasks in the exercise, complete them at home.

<hr>

### 👉 Comprehension Check
- I have understood all codes and practice topics.
- I know 'operator overloading' and can overload unary and binary operators.
- I can explain why some operators are members and some are not.
- I know design rules that need to be considered when overloading operators.
- I know what 'friend' means.
- I know the different meanings of 'static'.
