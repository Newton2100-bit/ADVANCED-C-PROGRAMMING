/* ========================================
   PROGRAM 1: Basic Variable Sum
   Demonstrates: va_start, va_arg, va_end
   ======================================== */
#include <stdio.h>
#include <stdarg.h>

int sum(int count, ...) {
    va_list args;
    va_start(args, count);
    
    int total = 0;
    for (int i = 0; i < count; i++) {
        total += va_arg(args, int);
    }
    
    va_end(args);
    return total;
}

void test_program1() {
    printf("=== PROGRAM 1: Basic Sum ===\n");
    printf("Sum of 3 numbers (10,20,30): %d\n", sum(3, 10, 20, 30));
    printf("Sum of 5 numbers (1,2,3,4,5): %d\n\n", sum(5, 1, 2, 3, 4, 5));
}

/* ========================================
   PROGRAM 2: Generic Printf Clone
   Demonstrates: Format string parsing
   ======================================== */
void my_printf(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    
    while (*fmt) {
        if (*fmt == '%') {
            fmt++;
            switch (*fmt) {
                case 'd': printf("%d", va_arg(args, int)); break;
                case 'f': printf("%f", va_arg(args, double)); break;
                case 's': printf("%s", va_arg(args, char*)); break;
                case 'c': printf("%c", va_arg(args, int)); break;
                default: putchar('%'); putchar(*fmt);
            }
        } else {
            putchar(*fmt);
        }
        fmt++;
    }
    
    va_end(args);
}

void test_program2() {
    printf("=== PROGRAM 2: Custom Printf ===\n");
    my_printf("Integer: %d, Float: %f, String: %s\n", 42, 3.14, "Hello");
    my_printf("Char: %c, Multiple: %d %d %d\n\n", 'A', 1, 2, 3);
}

/* ========================================
   PROGRAM 3: Min/Max with Variable Args
   Demonstrates: Default promotions
   ======================================== */
int find_max(int count, ...) {
    va_list args;
    va_start(args, count);
    
    int max = va_arg(args, int);
    for (int i = 1; i < count; i++) {
        int val = va_arg(args, int);
        if (val > max) max = val;
    }
    
    va_end(args);
    return max;
}

int find_min(int count, ...) {
    va_list args;
    va_start(args, count);
    
    int min = va_arg(args, int);
    for (int i = 1; i < count; i++) {
        int val = va_arg(args, int);
        if (val < min) min = val;
    }
    
    va_end(args);
    return min;
}

void test_program3() {
    printf("=== PROGRAM 3: Min/Max Finder ===\n");
    printf("Max of (45,12,89,23,67): %d\n", find_max(5, 45, 12, 89, 23, 67));
    printf("Min of (45,12,89,23,67): %d\n\n", find_min(5, 45, 12, 89, 23, 67));
}

/* ========================================
   PROGRAM 4: va_copy Demonstration
   Demonstrates: Copying va_list
   ======================================== */
void print_twice(const char* fmt, ...) {
    va_list args1, args2;
    va_start(args1, fmt);
    va_copy(args2, args1);
    
    printf("First pass: ");
    vprintf(fmt, args1);
    
    printf("Second pass: ");
    vprintf(fmt, args2);
    
    va_end(args1);
    va_end(args2);
}

void test_program4() {
    printf("=== PROGRAM 4: va_copy Usage ===\n");
    print_twice("Numbers: %d, %d, %d\n", 10, 20, 30);
    printf("\n");
}

/* ========================================
   PROGRAM 5: Dynamic String Builder
   Demonstrates: Building strings dynamically
   ======================================== */
#include <string.h>
#include <stdlib.h>

char* build_string(int count, ...) {
    va_list args, args_copy;
    va_start(args, count);
    va_copy(args_copy, args);
    
    // Calculate total length
    size_t total_len = 0;
    for (int i = 0; i < count; i++) {
        total_len += strlen(va_arg(args, char*));
    }
    
    // Allocate and build
    char* result = malloc(total_len + 1);
    result[0] = '\0';
    
    for (int i = 0; i < count; i++) {
        strcat(result, va_arg(args_copy, char*));
    }
    
    va_end(args);
    va_end(args_copy);
    return result;
}

void test_program5() {
    printf("=== PROGRAM 5: String Builder ===\n");
    char* str = build_string(4, "Hello", " ", "World", "!");
    printf("Built string: %s\n\n", str);
    free(str);
}

/* ========================================
   PROGRAM 6: Average Calculator (Mixed Types)
   Demonstrates: Different type handling
   ======================================== */
double average_doubles(int count, ...) {
    va_list args;
    va_start(args, count);
    
    double sum = 0.0;
    for (int i = 0; i < count; i++) {
        sum += va_arg(args, double);
    }
    
    va_end(args);
    return sum / count;
}

void test_program6() {
    printf("=== PROGRAM 6: Average Calculator ===\n");
    printf("Average: %.2f\n\n", average_doubles(4, 10.5, 20.3, 30.7, 15.1));
}

/* ========================================
   PROGRAM 7: Nested Variadic Function
   Demonstrates: Passing va_list to another function
   ======================================== */
void inner_print(const char* prefix, va_list args) {
    printf("%s: ", prefix);
    char* str;
    while ((str = va_arg(args, char*)) != NULL) {
        printf("%s ", str);
    }
    printf("\n");
}

void outer_print(const char* prefix, ...) {
    va_list args;
    va_start(args, prefix);
    inner_print(prefix, args);
    va_end(args);
}

void test_program7() {
    printf("=== PROGRAM 7: Nested Variadic ===\n");
    outer_print("Items", "apple", "banana", "cherry", NULL);
    printf("\n");
}

/* ========================================
   PROGRAM 8: Type-Safe Variadic with Sentinel
   Demonstrates: Using sentinel values
   ======================================== */
#define END_ARGS -9999

int sum_until_sentinel(int first, ...) {
    va_list args;
    va_start(args, first);
    
    int sum = first;
    int val;
    while ((val = va_arg(args, int)) != END_ARGS) {
        sum += val;
    }
    
    va_end(args);
    return sum;
}

void test_program8() {
    printf("=== PROGRAM 8: Sentinel-Based Sum ===\n");
    printf("Sum: %d\n\n", sum_until_sentinel(5, 10, 15, 20, END_ARGS));
}

/* ========================================
   PROGRAM 9: Generic Array Printer
   Demonstrates: Pointer handling
   ======================================== */
typedef enum { INT, FLOAT, CHAR, STRING } DataType;

void print_array(DataType type, int count, ...) {
    va_list args;
    va_start(args, count);
    
    printf("[ ");
    for (int i = 0; i < count; i++) {
        switch (type) {
            case INT:
                printf("%d ", va_arg(args, int));
                break;
            case FLOAT:
                printf("%.2f ", va_arg(args, double));
                break;
            case CHAR:
                printf("%c ", va_arg(args, int));
                break;
            case STRING:
                printf("%s ", va_arg(args, char*));
                break;
        }
    }
    printf("]\n");
    
    va_end(args);
}

void test_program9() {
    printf("=== PROGRAM 9: Generic Array Printer ===\n");
    print_array(INT, 5, 10, 20, 30, 40, 50);
    print_array(STRING, 3, "red", "green", "blue");
    printf("\n");
}

/* ========================================
   PROGRAM 10: Error Logger with Levels
   Demonstrates: Practical application
   ======================================== */
typedef enum { DEBUG, INFO, WARNING, ERROR } LogLevel;

void log_message(LogLevel level, const char* fmt, ...) {
    const char* levels[] = {"DEBUG", "INFO", "WARNING", "ERROR"};
    printf("[%s] ", levels[level]);
    
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
    
    printf("\n");
}

void test_program10() {
    printf("=== PROGRAM 10: Error Logger ===\n");
    log_message(INFO, "Application started");
    log_message(WARNING, "Low memory: %d%% remaining", 15);
    log_message(ERROR, "File '%s' not found at line %d", "config.txt", 42);
    printf("\n");
}

/* ========================================
   PROGRAM 11: Mathematical Expression Evaluator
   Demonstrates: Complex state management
   ======================================== */
typedef enum { ADD, SUB, MUL, DIV } Operation;

double calculate(Operation op, int count, ...) {
    va_list args;
    va_start(args, count);
    
    double result = va_arg(args, double);
    
    for (int i = 1; i < count; i++) {
        double val = va_arg(args, double);
        switch (op) {
            case ADD: result += val; break;
            case SUB: result -= val; break;
            case MUL: result *= val; break;
            case DIV: result /= val; break;
        }
    }
    
    va_end(args);
    return result;
}

void test_program11() {
    printf("=== PROGRAM 11: Expression Evaluator ===\n");
    printf("ADD: %.2f\n", calculate(ADD, 4, 10.0, 5.0, 3.0, 2.0));
    printf("MUL: %.2f\n", calculate(MUL, 3, 2.0, 3.0, 4.0));
    printf("\n");
}

/* ========================================
   PROGRAM 12: Struct Formatter
   Demonstrates: Complex data structures
   ======================================== */
typedef struct {
    char name[50];
    int age;
    double salary;
} Person;

void print_people(int count, ...) {
    va_list args;
    va_start(args, count);
    
    printf("%-20s %-5s %-10s\n", "Name", "Age", "Salary");
    printf("----------------------------------------\n");
    
    for (int i = 0; i < count; i++) {
        Person p = va_arg(args, Person);
        printf("%-20s %-5d $%-9.2f\n", p.name, p.age, p.salary);
    }
    
    va_end(args);
}

void test_program12() {
    printf("=== PROGRAM 12: Struct Printer ===\n");
    Person p1 = {"Alice Johnson", 30, 75000.50};
    Person p2 = {"Bob Smith", 25, 62000.00};
    Person p3 = {"Carol Davis", 35, 89000.75};
    print_people(3, p1, p2, p3);
    printf("\n");
}

/* ========================================
   MAIN: Run All Programs
   ======================================== */
int main() {
    test_program1();
    test_program2();
    test_program3();
    test_program4();
    test_program5();
    test_program6();
    test_program7();
    test_program8();
    test_program9();
    test_program10();
    test_program11();
    test_program12();
    
    return 0;
}
