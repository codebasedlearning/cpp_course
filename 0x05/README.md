[© 2025, A.Voß, FH Aachen, codebasedlearning.dev](mailto:info@codebasedlearning.dev)

# Unit 0x05

## Tasks

<hr>

### 👉 Task 'Copper View'

Modify variables using pointers:
- Create a local 'int' and 'float' variable and initialize them with arbitrary values.
- Create two pointers and initialize them so that they each point to these two variables.
- Change the values of the variables using the pointers.
- Print the pointer, the value it points to, and the corresponding variable for each.

Extension:
- Create a pointer to the pointer to 'int', initialize it with the address of the 
  'int' pointer and print out the value of the 'int' variable through it.

<hr>

### 👉 Task 'Kengate'

Return of multiple values using pointers:
- The function `divmod` should, similar to `swap`, calculate and 'return' the integer division 
  and remainder using two pointers. Additionally, it should return whether the division was actually
  performed, i.e. whether division by 0 was avoided.
- The function signature is
  `bool divmod(const int n, const int p, int *pdiv, int *pmod)`,
  where `pdiv` and `pmod` point to the variables that should contain the result after calling the function.
- In case of division by 0, the function should return `false` and set `pdiv` and `pmod` to 0.
- Write test code that calls the function and prints the result.

<hr>

### 👉 Task 'McAllen Spring'

A first improvised list:
- Create a class `Node`.
- It contains a private integer member `payload` and a pointer `next` to the next node.
- Add a constructor that initializes these members accordingly. The pointer is optional.
- The class gets a method `get_payload` that returns the payload, and a method `get_next` 
  that returns the pointer to the next node.
- Create four local variables of type `Node`. Use the address of the previous `Node`, 
  when available, as `next`. Name the last variable `root`.
- Starting from `root`, iterate through this local list and print the payload of each `Node` 
  to the console.

Please note that we will discuss ways to create nodes dynamically. Local variables would 
usually not be 'linked', such a situation is very prone to using pointers to no longer 
valid memory locations!

<hr>

### 👉 Task 'Don't do this, or I'll tell your mum'

Try to change single bytes of local variables on the stack through pointer manipulations, 
that is without directly addressing the variables.
Hint: First determine the address of some local variable. The others are 'nearby' on the stack. 
You can use the type `std::byte` and cast a pointer to byte pointer using `(byte*)p` or 
`reinterpret_cast<byte*>(p)` to access single bytes.

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

- I understand that a pointer is a variable that stores the memory address of another variable.
- I can declare pointers using type* syntax and initialize them using & operator or nullptr.
- I know how to dereference pointers with * to access and modify the data they point to.
- I understand how to pass pointers as function parameters to allow functions to modify variables.
- I know that & in type definitions creates a reference while & before a variable gets its address.
- I know that * in type definitions declares a pointer while * before a pointer dereferences it.
- I understand that local variables are stored (more or less) sequentially on the stack in memory.
