[© 2025, A.Voß, FH Aachen, codebasedlearning.dev](mailto:info@codebasedlearning.dev)

# Unit 0x08

## SOLID Principles – Principles of Object-Oriented Design

The `SOLID` principles are a set of five design principles intended to make software designs more understandable,
flexible, and maintainable. For a reference start [here](https://en.wikipedia.org/wiki/SOLID).

### Single-Responsibility-Prinzip (SRP)

> "There should never be more than one reason for a class to change.", Robert C. Martin (Uncle Bob)

A class should have only one reason to change, meaning it should only have one job or responsibility.

In C++, this can be implemented by designing classes that focus on a single functionality.
Avoid creating "God objects" that try to handle multiple functionalities. Instead, break down
complex classes into smaller, more coherent units.

### Open-Closed-Prinzip (OCP)

> "Modules should be both open (for extension) and closed (for modification).", Bertrand Meyer

Software entities should be open for extension, but closed for modification.

In C++, this can be achieved by using abstract classes and interfaces (pure virtual classes in C++ terminology),
allowing classes to be extended without modifying existing code.

### Liskovsches Substitutionsprinzip (LSP)

> "That is, if S subtypes T, what holds for T-objects holds for S-objects.", Barbara Liskov

Objects of a superclass should be replaceable with objects of its subclasses without affecting
the correctness of the program.

In C++, this means that derived classes must be substitutable for their base classes without
altering the desirable properties of the program (e.g., correctness, performance).

Example: circle–ellipse-problem (or square–rectangle-problem) in software development:

class Circle inherits from class Ellipse (or class Square from class Rectangle), because the former
'is a special kind' of its base (is-a-relationship). What about base-class-methods like Ellipse.stretchX
(or Rectangle.stretchX)?

The problem illustrates the difficulties which can occur when a base class contains methods which
mutate an object in a manner which may invalidate a (stronger) invariant found in a derived class,
causing the Liskov substitution principle to be violated.

### Interface-Segregation-Prinzip (ISP)

> "Clients should not be forced to depend upon interfaces that they do not use.", Robert C. Martin

In C++, this can be translated to mean that interfaces (abstract classes with pure virtual functions)
should be specific and not generalized. Instead of one large interface,
multiple specific interfaces are preferred based on different client needs.
This reduces the side effects of changes in unrelated parts of the system and improves code readability.

### Dependency-Inversion-Prinzip (DIP)

> "High-level modules should not depend on low level modules. Both should depend on abstractions.
> Abstractions should not depend upon details. Details should depend upon abstractions.", R. C. Martin

In C++, this can be implemented by using abstract classes (interfaces) as dependencies
rather than concrete classes. This principle often leads to designs where high-level functionality
is achieved through composition of interfaces, and dependency injection is used to provide
the concrete implementations.

---

In C++, 4 of the 5 principles have something to do with interfaces or inheritance.


## Tasks

<hr>

### 👉 Task 'Union Beach'

Abstract Classes

- Implement an abstract class `matrix` that should represent a square matrix for integers.
  It has pure virtual methods for reading and writing elements (`at`), as well as a method
  to set the matrix to `0` (`make_zero`).
- The constructor receives the dimension `dim` as a parameter and stores it as a member of the class.
- The class has another non-virtual function for setting the identity matrix (`make_one`).
  This sets the matrix to `0` and then sets the diagonal elements to `1`.
- How the data is stored is decided by the derived classes.

Additionally

- Derive the class `full_matrix` from `matrix`. It stores its coefficients
  in a dynamic array of `int`.
- Implement the missing methods accordingly and use `unique_ptr` for the array.
- Derive the class `sparse_matrix` from `matrix`. It stores its coefficients in an `unordered_map`.
  The key is formed from `x` and `y` as `y*dim+x`, so that an entry can be found if it exists.
  Otherwise, it is `0`.
- Write meaningful test code for both classes.

Extension

- Efficiently extend the classes with operators.
- Make the class a template.


### 👉 Task 'Peters Mines'

Multiple Inheritance

- Define a class `vehicle_base` that contains the number of seats as a member.
- Define a class `vehicle` that contains a maximum speed as a member.
- Derive the classes `car` and `boat` from both `vehicle_base` and `vehicle`.
  The class `vehicle_base` should be inherited virtually.
- Implement a class `amphibian` that inherits from `boat` and `car`.
  Instances should then have only one number of seats, but two maximum speeds.

- Pass all necessary parameters to the constructors, i.e. initializing
  an `amphibian` with four seats and two speeds looks like this:
  `amphibian a{4,120,15};`
- Write meaningful test code and especially output the seats and speeds.

Extension

- Add additional members to `car` and `boat` that are also passed to the constructors.


### 👉 Task 'AI'

What would the AI say about it?

Pick your solutions and ask a GenAI-Tool of your choice (e.g., ChatGPT) for its opinion.
- What improvements are suggested?
- Do they make sense?

<hr>

### 👉 Task 'Couch Potato' - Recurring homework.

- If you have not completed the main tasks in the exercise, complete them at home.
- Study `study_vtable` and `study_windows`.

<hr>

### 👉 Comprehension Check

- I have understood all codes and practice topics.
- I know that in C++ you can choose whether a function is virtual or not.
- I have understood the difference between 'virtual' and 'override'.
- I know why there is no Interface keyword in C++.
- I know the difference between an abstract class and an interface.
- I know what 'pure virtual' means.
- I know the meaning of the modifiers 'public', 'protected' and 'private' in inheritance.
- I know some of the problems with multiple inheritance.
