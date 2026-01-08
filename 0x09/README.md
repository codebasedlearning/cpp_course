[© 2025, A.Voß, FH Aachen, codebasedlearning.dev](mailto:info@codebasedlearning.dev)

# Unit 0x09

## Tasks

<hr>

### 👉 Task 'Eastbourne'

Template Specialization

- Take the `point` class from 'Stone Ridge' (Unit 0x03) or 'Sparrow Town' (Unit 0x04),
  specialize it for `bool` and make the constructor private there, such that you cannot 
  create an instance of it.

<hr>

### 👉 Task 'Openshaw'

unique- and shared-ptr

- Design an arbitrary class and 
- fill (respectively) a `std::vector` with some dynamically allocated objects of your class. Use
  - (raw) pointers, 
  - `unique_ptr`s
  - and `shared-ptr`s.
- Output all elements in a loop.

Are all elements properly destroyed or are there memory leaks?

<hr>

### 👉 Task 'Banrockburn'

Application of shared-ptr and weak-ptr

Implement a generic doubly linked list with smart pointers instead of raw pointers. In detail:
- Design a template class `Node` with data, a (smart) pointer to the `next` element 
  and s (smart) pointer `prev` to the previous element. 
- Implement a template class `List` for a list with a `root` pointer to the first,
  and a `tail` pointer to the last element.
- Use `shared_ptr` and `weak_ptr`, such that all Nodes are properly destroyed.
- Implement a `+=`-operator for appending new elements.
- Write meaningful test code and iterate over a sample list forward and backward.

<hr>

### 👉 Task 'Wintervale'

Metaprogramming

- Write a template class that calculates B^N (B to the power of N) at compile time 
  for two natural numbers B and N.
- Write meaningful test code.

<hr>

### 👉 Task 'Clarcton'

Config-Files

- Write the string below to a file and read the file.
- Fill a `map` with key-value pairs (`string`).

Content
```
  api_key = 123456
  user = John
```

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
- I know how to specialize template classes.
- I know how to read and write files.
- I know what a `unique_ptr`, a `shared_ptr`, and a `weak_ptr` is, and I can use them.
