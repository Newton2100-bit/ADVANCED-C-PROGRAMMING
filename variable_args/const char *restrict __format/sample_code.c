/* =====================================================================
   UNDERSTANDING: const char *restrict __format
   ===================================================================== */

#include <stdio.h>
#include <string.h>

/* =====================================================================
   PART 1: What is 'restrict'?
   
   restrict is a TYPE QUALIFIER (like const, volatile)
   It's a CONTRACT with the compiler:
   "I promise this pointer is the ONLY way to access this data"
   ===================================================================== */

// WITHOUT restrict - Compiler must be conservative
void copy_without_restrict(int* dest, int* src, size_t n) {
    for (size_t i = 0; i < n; i++) {
        dest[i] = src[i];
        // Compiler thinks: "What if dest and src overlap?"
        // Must reload src[i] each time (slow!)
    }
}

// WITH restrict - Compiler can optimize aggressively
void copy_with_restrict(int* restrict dest, int* restrict src, size_t n) {
    for (size_t i = 0; i < n; i++) {
        dest[i] = src[i];
        // Compiler knows: "dest and src don't overlap"
        // Can use registers, vectorize, reorder operations (fast!)
    }
}

void demo_restrict_basics() {
    printf("=== RESTRICT BASICS ===\n\n");
    
    printf("Without restrict:\n");
    printf("  - Compiler assumes pointers MIGHT alias (point to same memory)\n");
    printf("  - Must reload memory after every write\n");
    printf("  - Conservative, slower code\n\n");
    
    printf("With restrict:\n");
    printf("  - You PROMISE pointers don't alias\n");
    printf("  - Compiler can keep values in registers\n");
    printf("  - Can reorder operations for speed\n");
    printf("  - Can use SIMD/vector instructions\n\n");
}

/* =====================================================================
   PART 2: The Aliasing Problem
   ===================================================================== */

void add_arrays_no_restrict(int* a, int* b, int* result, size_t n) {
    for (size_t i = 0; i < n; i++) {
        result[i] = a[i] + b[i];
        // What if 'result' points inside 'a' or 'b'?
        // Compiler can't optimize much
    }
}

void add_arrays_restrict(int* restrict a, 
                         int* restrict b, 
                         int* restrict result, 
                         size_t n) {
    for (size_t i = 0; i < n; i++) {
        result[i] = a[i] + b[i];
        // Compiler KNOWS they're separate
        // Can unroll loop, use vector instructions
    }
}

void demo_aliasing_problem() {
    printf("=== THE ALIASING PROBLEM ===\n\n");
    
    int a[] = {1, 2, 3, 4, 5};
    int b[] = {10, 20, 30, 40, 50};
    int result[5];
    
    // This is SAFE - all separate arrays
    add_arrays_restrict(a, b, result, 5);
    
    printf("Safe usage:\n");
    printf("  a and b are separate arrays\n");
    printf("  result is separate\n");
    printf("  Result: ");
    for (int i = 0; i < 5; i++) printf("%d ", result[i]);
    printf("\n\n");
    
    // This BREAKS the restrict contract!
    printf("DANGEROUS - breaks restrict promise:\n");
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8};
    // This is UNDEFINED BEHAVIOR if function uses restrict:
    // add_arrays_restrict(data, data+2, data+4, 3);
    printf("  If data, data+2, data+4 overlap\n");
    printf("  Using restrict = UNDEFINED BEHAVIOR!\n");
    printf("  (Code might work, might crash, might give wrong answer)\n\n");
}

/* =====================================================================
   PART 3: Real-world Example - memcpy vs memmove
   ===================================================================== */

void demo_memcpy_vs_memmove() {
    printf("=== MEMCPY vs MEMMOVE ===\n\n");
    
    printf("memcpy:\n");
    printf("  void* memcpy(void* restrict dest,\n");
    printf("               const void* restrict src,\n");
    printf("               size_t n);\n");
    printf("  - Uses restrict = FAST but requires non-overlapping\n");
    printf("  - Undefined behavior if src and dest overlap!\n\n");
    
    printf("memmove:\n");
    printf("  void* memmove(void* dest,\n");
    printf("                const void* src,\n");
    printf("                size_t n);\n");
    printf("  - NO restrict = SAFE but slower\n");
    printf("  - Handles overlapping memory correctly\n\n");
    
    char buffer[20] = "Hello World!";
    
    // CORRECT: Use memmove for overlapping regions
    printf("Moving overlapping memory:\n");
    printf("  Before: %s\n", buffer);
    memmove(buffer + 2, buffer, 10);  // Overlap is OK
    printf("  After:  %s\n\n", buffer);
}

/* =====================================================================
   PART 4: const char *restrict __format - Breaking it down
   ===================================================================== */

// This is what you'd see in printf:
// int printf(const char *restrict format, ...);

void my_printf_example(const char *restrict __format, ...) {
    // const char* = pointer to constant string
    // restrict    = this is the ONLY pointer to this format string
    // __format    = parameter name (__ avoids conflicts)
    
    printf("Format string: %s\n", __format);
}

void demo_format_string() {
    printf("=== const char *restrict __format ===\n\n");
    
    printf("Breaking it down:\n\n");
    
    printf("1. const char*\n");
    printf("   - Pointer to constant characters\n");
    printf("   - Can't do: __format[0] = 'X'; (would be error)\n");
    printf("   - Can do:   char c = __format[0]; (reading is OK)\n\n");
    
    printf("2. restrict\n");
    printf("   - Promise: no other pointer accesses this string\n");
    printf("   - Allows compiler to cache the string\n");
    printf("   - Common in I/O functions (printf, scanf, etc.)\n\n");
    
    printf("3. __format\n");
    printf("   - Just the parameter name\n");
    printf("   - __ prefix = implementation detail, avoid conflicts\n");
    printf("   - You'd normally use 'format' or 'fmt'\n\n");
    
    // Example usage:
    my_printf_example("Hello %d %s", 42, "world");
    printf("\n");
}

/* =====================================================================
   PART 5: When to Use restrict
   ===================================================================== */

// GOOD: Separate buffers
void process_buffers_good(int* restrict input,
                          int* restrict output,
                          size_t n) {
    for (size_t i = 0; i < n; i++) {
        output[i] = input[i] * 2;
    }
}

// BAD: Same buffer used for both
void process_buffers_bad_usage(int* restrict data, size_t n) {
    // This function promises 'data' is unique
    // But if caller does: process_buffers_bad_usage(arr, ...)
    // and internally we access arr through another pointer...
    // UNDEFINED BEHAVIOR!
    
    for (size_t i = 0; i < n; i++) {
        data[i] = data[i] * 2;  // This is actually OK
    }
}

void demo_when_to_use() {
    printf("=== WHEN TO USE RESTRICT ===\n\n");
    
    printf("✓ USE restrict when:\n");
    printf("  - Pointers point to separate memory regions\n");
    printf("  - You're writing library functions (memcpy, strcpy)\n");
    printf("  - Performance matters and you can guarantee no aliasing\n");
    printf("  - Working with large arrays/buffers\n\n");
    
    printf("✗ DON'T use restrict when:\n");
    printf("  - Pointers might overlap\n");
    printf("  - You're not sure about memory layout\n");
    printf("  - Debugging weird behavior (try removing it!)\n");
    printf("  - Function might be called with aliased pointers\n\n");
    
    int input[] = {1, 2, 3, 4, 5};
    int output[5];
    
    process_buffers_good(input, output, 5);
    
    printf("Example result: ");
    for (int i = 0; i < 5; i++) printf("%d ", output[i]);
    printf("\n\n");
}

/* =====================================================================
   PART 6: Performance Impact
   ===================================================================== */

void demo_performance_impact() {
    printf("=== PERFORMANCE IMPACT ===\n\n");
    
    printf("Assembly difference (simplified):\n\n");
    
    printf("WITHOUT restrict:\n");
    printf("  loop:\n");
    printf("    load  r1, [src]     ; Load from memory\n");
    printf("    store [dest], r1    ; Store to memory\n");
    printf("    load  r1, [src]     ; Must reload! (might have changed)\n");
    printf("    add   src, 4\n");
    printf("    add   dest, 4\n");
    printf("    jmp   loop\n\n");
    
    printf("WITH restrict:\n");
    printf("  loop:\n");
    printf("    load  r1, [src]     ; Load once\n");
    printf("    load  r2, [src+4]   ; Load next (pipelined!)\n");
    printf("    load  r3, [src+8]   ; Load next (vectorized!)\n");
    printf("    store [dest], r1    ; Store\n");
    printf("    store [dest+4], r2  ; Store\n");
    printf("    store [dest+8], r3  ; Store\n");
    printf("    add   src, 12       ; Unrolled!\n");
    printf("    add   dest, 12\n");
    printf("    jmp   loop\n\n");
    
    printf("Speedup: 2-4x is common for restrict!\n\n");
}

/* =====================================================================
   PART 7: Common Mistakes
   ===================================================================== */

void demo_common_mistakes() {
    printf("=== COMMON MISTAKES ===\n\n");
    
    printf("MISTAKE 1: Overlapping regions\n");
    printf("  char buf[100];\n");
    printf("  strcpy(buf+10, buf);  // WRONG if strcpy uses restrict!\n\n");
    
    printf("MISTAKE 2: Aliasing through global/static\n");
    printf("  int* global_ptr;\n");
    printf("  void foo(int* restrict p) {\n");
    printf("    *p = 5;\n");
    printf("    *global_ptr = 10;  // If global_ptr == p, UB!\n");
    printf("  }\n\n");
    
    printf("MISTAKE 3: Returning restrict pointer\n");
    printf("  int* restrict bad_function() {\n");
    printf("    static int x = 5;\n");
    printf("    return &x;  // Meaningless! restrict applies to function scope\n");
    printf("  }\n\n");
    
    printf("MISTAKE 4: restrict on struct members\n");
    printf("  struct S {\n");
    printf("    int* restrict p;  // WRONG! restrict is for function params\n");
    printf("  };\n\n");
}

/* =====================================================================
   PART 8: Quick Reference
   ===================================================================== */

void demo_quick_reference() {
    printf("=== QUICK REFERENCE ===\n\n");
    
    printf("Syntax:\n");
    printf("  type * restrict pointer_name\n\n");
    
    printf("Examples:\n");
    printf("  int* restrict p\n");
    printf("  char* restrict str\n");
    printf("  const char* restrict fmt\n");
    printf("  void* restrict dest\n\n");
    
    printf("Standard library uses:\n");
    printf("  memcpy(void* restrict dst, const void* restrict src, size_t n)\n");
    printf("  strcpy(char* restrict dst, const char* restrict src)\n");
    printf("  sprintf(char* restrict str, const char* restrict fmt, ...)\n");
    printf("  printf(const char* restrict format, ...)\n\n");
    
    printf("Remember:\n");
    printf("  - It's a PROMISE to the compiler\n");
    printf("  - Breaking the promise = undefined behavior\n");
    printf("  - Enables optimizations (2-4x speedup possible)\n");
    printf("  - Only use if you're CERTAIN pointers don't alias\n\n");
}

/* =====================================================================
   MAIN
   ===================================================================== */

int main() {
    printf("╔════════════════════════════════════════════════════════╗\n");
    printf("║     UNDERSTANDING: const char *restrict __format       ║\n");
    printf("╚════════════════════════════════════════════════════════╝\n\n");
    
    demo_restrict_basics();
    demo_aliasing_problem();
    demo_memcpy_vs_memmove();
    demo_format_string();
    demo_when_to_use();
    demo_performance_impact();
    demo_common_mistakes();
    demo_quick_reference();
    
    printf("╔════════════════════════════════════════════════════════╗\n");
    printf("║  🎯 Now you understand restrict!                       ║\n");
    printf("╚════════════════════════════════════════════════════════╝\n");
    
    return 0;
}
