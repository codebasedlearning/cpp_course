[© 2025, A.Voß, FH Aachen, codebasedlearning.dev](mailto:info@codebasedlearning.dev)

# Unit 0x00

## Compile and Run

Open a terminal, change into the `snippets` directory, and compile your first C++ file. 
Run

```
g++ a_helloworld.cpp -o a_helloworld.out
```

This produces an executable named `a_helloworld.out`. Now launch it:

```
./a_helloworld.out
```

If you skip the -o option, the compiler defaults to the very imaginative name `a.out` — which 
is fine until you have three of them and can’t remember who’s who.

## Make

Instead of compiling everything every time, use `make`. It checks what changed and only rebuilds 
what’s necessary. The rules and dependencies live in a file called `makefile`. To use it, just type:

```
make
```

## CMake

Behind the scenes in many IDEs (like CLion), `CMake` orchestrates the build. CMake isn’t a build system 
itself — it generates build files for one (e.g., makefiles). In practice, you mostly edit `CMakeLists.txt`
to declare sources, targets, and dependencies; CLion runs CMake and the build tools for you. 

## Comments

Questions, improvements, or clever suggestions? Send friendly notes (and constructive critique) to
[me](mailto:info@codebasedlearning.dev).
