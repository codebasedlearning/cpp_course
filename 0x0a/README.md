[© 2025, A.Voß, FH Aachen, codebasedlearning.dev](mailto:info@codebasedlearning.dev)

# Unit 0x0a

## Tasks

<hr>

### 👉 Task 'Roarport'

Lambda Expression

Write a lambda expression for each of the following:
- adds three passed double values and returns the result;
- tests whether a passed int value lies within an interval `[a,b]`,
  where `a` and `b` are local variables, captured by a copy;
- has no arguments but sets a local int variable `z` to `-z` (academic example).

<hr>

### 👉 Task 'Kreley'

Function Pointers, function

- Define a function pointer data type `funktion_t` for a function that receives 
  two ints x,y and returns a double.
- Implement a function Q that calculates the value `x/y` from passed values `x` 
  and `y`.
- Initialize a function pointer with Q and call Q through it.
- Make the same with `function`.

<hr>

### 👉 Task 'Yrouwood'

Function Pointers, Lambda Expression

Write a function `approx` that takes as parameters a starting value `x0`, 
a `function` `f(double)->double` to be iterated, and an `eps`:
- `approx` calculates `x=f(x)`, with `x=x0` at the beginning, as long as the new 
  `x`-value differs from the previous one by more than `eps`.
- Return the last calculated value.
- Test `approx` for the Heron method (square root calculation, see Wikipedia),
  given as a lambda expression, and `a=2`, `a=4` with `x0=1` and `eps=1e-10`.

<hr>

### 👉 Task 'Pleim'

Algorithms

Generate a vector with the binomial coefficients (`n` choose `k`, or, `n` over `k`) 
for a fixed `n`, e.g., for `n=4` we have [1,4,6,4,1].

- Use only functions from the algorithms or ranges library, such as `for_each` or
  `generate`, and no explicit for- or other loops.

<hr>

### 👉 Task 'Westwheat'

Threads, Mutex, ref

Start two threads. Each fills a (global) `int`-vector with `n` (any or random) numbers (via `push_back`).
- Start with a small `n<3` and do not protect access to the vector. Does it work?
- Increase the number `n` until the program crashes or is frozen. Why is that?
- Protect the vector during insertion with a `lock_guard` (thread-safe). Does it work again now?

<hr>

### 👉 Task 'Coldwall'

Threads, Mutex, ref

- Consider an appropriate parallel strategy with multiple threads and sum the
  numbers `1..n` in parallel and thread-safe.
- Measure the time for no parallelization, for two threads, three threads, etc.
  From how many threads does it not get faster anymore, or does it get faster at all?

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
- I have understood what a lambda is for.
- I know what a function pointer is for.
- I can start a thread and wait for it to finish.
- I can use a `lock_guard` to protect a shared ressource.
