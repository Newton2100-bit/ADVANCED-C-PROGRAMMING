/* These is based on a sentinel
   Sentinel-based
   */
#include <stdio.h>
#include <stdarg.h>

void print_string(const char *first, ...){
	va_list arguments, target;
	va_start(arguments, first);
	va_copy(target, arguments);

	printf("%p >\n", &(first));
	printf("%s <>\n", *(&first - sizeof(char *)));
	printf("%p >\n", first);
	
	/*
	for (int i = 0; i < 2; i++){
		printf("%i\n", va_arg(arguments, int));
	}
	*/
	va_end(arguments);
	for (int i = 0; i < 2; i++){
		printf("%s\n", va_arg(target, char*));
	}
	va_end(target);
	return;
}
int main(void){
	print_string("newton", "45", "78", NULL);
	return 0;
}

/*
I can see you're exploring variadic functions and trying to understand how arguments are laid out in memory. Let me help clarify what's happening and guide you toward the correct approach.

## Issues in Your Current Code

1. **`printf("%s <>\n", *(&first - sizeof(char *)));`** - This is problematic:
   - `&first` gives you the address of the `first` parameter
   - Subtracting `sizeof(char *)` (which is 8 on 64-bit systems) moves the pointer by 8 pointers, not 1
   - You likely meant `&first - 1` to move back one pointer position
   - Dereferencing this attempts to read memory before your function's parameters, which is undefined behavior

2. **Sentinel-based approach**: You're using `NULL` as a sentinel, but your loop hardcodes `i < 2` instead of checking for the sentinel.

## Correct Approach for Sentinel-Based Variadic Function

Here's how to properly implement what you're trying to achieve:

```c
#include <stdio.h>
#include <stdarg.h>

void print_string(const char *first, ...) {
    va_list arguments;
    va_start(arguments, first);
    
    // Print the first argument
    printf("%s\n", first);
    
    // Loop until we hit the NULL sentinel
    const char *arg;
    while ((arg = va_arg(arguments, const char *)) != NULL) {
        printf("%s\n", arg);
    }
    
    va_end(arguments);
}

int main(void) {
    print_string("newton", "45", "78", NULL);
    return 0;
}
```

## Key Points to Understand

1. **Don't Access Stack Memory Directly**: The layout of function parameters on the stack is implementation-defined. Using pointer arithmetic like `&first - 1` is dangerous and non-portable.

2. **Use `va_arg` Properly**: This is the correct way to access variadic arguments. It handles the stack layout for you.

3. **Sentinel Pattern**: When using `NULL` as a sentinel:
   - Loop until you encounter `NULL`
   - Don't hardcode the loop count
   - Remember to print `first` separately since it's not in the `va_list`

4. **Why `va_copy`?**: You had `va_copy` in your code. It's useful when you need to traverse the argument list multiple times:

```c
void print_twice(const char *first, ...) {
    va_list args1, args2;
    va_start(args1, first);
    va_copy(args2, args1);
    
    // First pass
    printf("First pass:\n%s\n", first);
    const char *arg;
    while ((arg = va_arg(args1, const char *)) != NULL) {
        printf("%s\n", arg);
    }
    
    // Second pass (using the copy)
    printf("\nSecond pass:\n%s\n", first);
    while ((arg = va_arg(args2, const char *)) != NULL) {
        printf("%s\n", arg);
    }
    
    va_end(args1);
    va_end(args2);
}
```

## Memory Layout Exploration (For Learning)

If you're trying to understand memory layout for educational purposes, here's a safer approach:

```c
void print_addresses(const char *first, ...) {
    va_list args;
    va_start(args, first);
    
    printf("Address of 'first' parameter: %p\n", (void*)&first);
    printf("Value of 'first': %p -> \"%s\"\n", (void*)first, first);
    
    // Note: This shows how va_list works, but internal structure is opaque
    printf("va_list size: %zu bytes\n", sizeof(args));
    
    va_end(args);
}
```

The key takeaway: always use the `va_*` macros to access variadic arguments rather than trying to manipulate pointers directly. The C standard provides these macros precisely because the underlying implementation varies across platforms and compilers.
*/
