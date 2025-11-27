[© 2025, A.Voß, FH Aachen, codebasedlearning.dev](mailto:info@codebasedlearning.dev)

# Unit 0x06

## Tasks

<hr>

### 👉 Task 'Reeds Field'

Working with C-strings.
- Create a C-string with arbitrary text, e.g. `char *str = "hallo";`
- Define a pointer to `char` and iterate through the C-string (including the null character)
  to output the pointer value, the character that the pointer points to, and
  the ASCII value.

Tips: Use appropriate casts if needed, i.e. `static_cast<new_type>(ptr)`.

<hr>

### 👉 Task 'South Birds Gale'

Work with pointers, arrays and unique_ptr.
- Define an array of four C-strings with 'This', 'is', 'a', 'sentence'.
- Program a function `length` that receives a pointer to a C-string as parameter 
  and returns the length of the C-string (excluding the null character).
- Test `length`.
- Implement a function `reverse` that receives a C-string, requests dynamic memory 
  with `new`, copies the passed C-string in reversed order to that location, 
  and returns the pointer to the new memory (remember the trailing null character).
- Test `reverse`.
- Copy `reverse` into a new function `make_reverse` returning a `unique_ptr` to
  a char-array containing the reversed string.
- Test `make_reverse`.

Extension:
- Check if the sanitizer tool detects any memory leaks.

<hr>

### 👉 Task 'Rose Pond'

Work with dynamic structures and smart pointers.

- Create a structure `address` that contains strings `name` and a `phone number`.
- Get three fictitious addresses from the heap with `new` and store them in
  an `unordered_map<int,address*>`.
- Print the key and value of all map entries.
- Make sure all allocated data is freed.

Extension:
- Use `unique_ptr` instead of raw pointers.

<hr>

### 👉 Task 'McAllen Spring Smart'

Extend 'McAllen Spring' from 'unit 0x05' and use smart pointers instead 
of raw pointers.

<hr>

### 👉 Task 'AI'

What would the AI say about it?

Pick your solutions and ask a GenAI-Tool of your choice (e.g., ChatGPT) for its opinion.
- What improvements are suggested?
- Do they make sense?

<hr>

### 👉 Task 'Couch Potato' - Recurring homework.

- If you have not completed the main tasks in the exercise, complete them at home.
- Study `study_2d_arrays` and `study_alloc_and_free`.

<hr>

### 👉 Comprehension Check

- I know commands to allocate and free objects on the heap.
- I understand the difference between a raw and a smart pointer.
- I know the difference between `delete` and `delete[]`.
- I know how to use `make_unique`.
- I know the concept of 'ownership' and 'lifetime'.
- I know what RAII is.
