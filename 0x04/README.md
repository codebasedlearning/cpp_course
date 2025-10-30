[© 2025, A.Voß, FH Aachen, codebasedlearning.dev](mailto:info@codebasedlearning.dev)

# Unit 0x04

## Tasks

<hr>

### 👉 Task 'Oakberg'

- Define an `int` array initialized with values `2, 3, 5, 7, 11` and a `vector` initialized 
  with the same values. Perform the following operations on both containers.
- Traverse each container in a range-based for and output each element.
- Use `auto&` in a range-based for and double the value of each element.
- Search for element `6` (3*2) and output this and the next two elements (incl.), if present.

<hr>

### 👉 Task 'Ashfield'

Mapping of ISBN numbers to books.
- Implement a struct `book` which (simplified) contains an author and a title.
- Define a custom type `catalog_t` through an `unordered_map` that maps a `string` (ISBN) to
  a `book`. Create an instance `catalog` of this type.
- Fill `catalog` with three (or more) real books (and ISBN) of your choice, e.g. 
  `44245381X` → `{'Walter Moers','The 13 1/2 Lives of Captain Bluebear'}`, etc.
- Search for all books whose title is longer than 40 characters and output them.

<hr>

### 👉 Task 'Sparrow Town'

- Extend the class `fraction` from exercise 'Ravencastle' or class `point` from 'Stone Ridge'
  (both Unit 0x03) to a template.
- Test your generic class with different data types.

<hr>

### 👉 Task 'Brickgate'

In the snippet 'study_vector', standard operations and functions are discussed:
- creating instances
- inserting and deleting elements
- searching for elements
- outputting elements.

Implement these for the classes `list`, `set` (or `unordered_set`) and `map` (or `unordered_map`).

<hr>

### 👉 Task 'AI'

What would the AI say about it?

Pick your solutions and ask a GenAI-Tool of your choice (e.g., ChatGPT) for its opinion.
- What improvements are suggested?
- Do they make sense?

<hr>

### 👉 Task 'Couch Potato' - Recurring homework.

- If you have not completed the main tasks in the exercise, complete them at home.
- Study `study_more_generics`, `study_more_iterators` and `study_vector`.

<hr>

### 👉 Comprehension Check

- I know different containers, namely?
- I can search, delete, add and remove elements.
- I know range-based for loops with and without copy and with iterators.
- I know the differences between set/map and unordered_set/map.
- I know the differences between vector/list/deque.
- I know what a string_view is and what dangers lurk.
- I can implement an output operator.

