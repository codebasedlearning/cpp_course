// (C) 2025 A.Voß, a.voss@fh-aachen.de, info@codebasedlearning.dev

/*
 * The aim of this programme is to introduce the topic of pointers. We will
 * therefore examine local variables on the stack in memory.
 * The key point to note is that these are located at specific memory addresses,
 * which are ultimately contained by pointers, enabling manipulation of the
 * variables via these addresses.
 *
 * 1. Recap
 *  - CPU-registers and roles, AX,BX,... SI,DI,IP,SP
 *    https://en.wikipedia.org/wiki/X86 - Image "Registers available in the x86-64 instruction set"
 *  - Stack
 *    https://de.wikipedia.org/wiki/Stapelspeicher (downwards)
 *
 * 2. CLion
 *  - 'Line Breakpoint' at "int n=..."
 *  - 'Debug' prg until then
 *  - 'Memory View' at "&n"
 *  - 'Step Over', view memory changes
 *
 * 3. Compiler Explorer
 *  - https://godbolt.org
 *  - copy prg into source window (left)
 *  - select 'x86-64 clang' as compiler
 *    explain stack frame with BP
 *    local vars dword ptr [rbp - x]
 *    registers as params
 *  - get optimized code with 'Compiler options' "-O"
 */

#include <cstdlib>

int two() { return 2; }

int inc2(int n) { return n+two(); }

int main() {
    int n = 97;
    int m = 65;
    int k = m+n;

    k = inc2(k);

    return EXIT_SUCCESS;
}
