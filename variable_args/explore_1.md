/* ========================================
   TRICK 1: X-Macro for Enum-String Mapping
   Problem: Keeping enums and strings in sync
   ======================================== */
#include <stdio.h>
#include <string.h>

// Define once, use everywhere!
#define COLOR_LIST \
    X(RED, "Red") \
    X(GREEN, "Green") \
    X(BLUE, "Blue") \
    X(YELLOW, "Yellow") \
    X(PURPLE, "Purple")

// Generate enum
#define X(name, str) name,
typedef enum { COLOR_LIST COLOR_COUNT } Color;
#undef X

// Generate string array
#define X(name, str) str,
const char* color_names[] = { COLOR_LIST };
#undef X

void demo_xmacro() {
    printf("=== X-MACRO TRICK ===\n");
    for (int i = 0; i < COLOR_COUNT; i++) {
        printf("Color %d: %s\n", i, color_names[i]);
    }
    printf("\n");
}

/* ========================================
   TRICK 2: Compound Literals (C99)
   Create temporary objects on the fly
   ======================================== */
typedef struct { int x, y; } Point;

void print_point(Point p) {
    printf("Point: (%d, %d)\n", p.x, p.y);
}

void demo_compound_literals() {
    printf("=== COMPOUND LITERALS ===\n");
    
    // No need to declare a variable!
    print_point((Point){10, 20});
    
    // Works with arrays too
    int sum = 0;
    for (int i = 0; i < 5; i++) {
        sum += (int[]){1, 2, 3, 4, 5}[i];
    }
    printf("Sum: %d\n\n", sum);
}

/* ========================================
   TRICK 3: Designated Initializers
   Initialize specific struct/array members
   ======================================== */
typedef struct {
    char name[50];
    int age;
    double salary;
    int active;
} Employee;

void demo_designated_init() {
    printf("=== DESIGNATED INITIALIZERS ===\n");
    
    // Skip fields, set specific ones
    Employee emp = {
        .name = "Alice",
        .salary = 75000.0,
        .active = 1
        // age defaults to 0
    };
    
    printf("Name: %s, Salary: %.2f, Active: %d\n", emp.name, emp.salary, emp.active);
    
    // Sparse arrays
    int arr[100] = {[0] = 1, [50] = 99, [99] = 100};
    printf("arr[0]=%d, arr[50]=%d, arr[99]=%d\n\n", arr[0], arr[50], arr[99]);
}

/* ========================================
   TRICK 4: Statement Expressions (GCC)
   Multi-line macros with return values
   ======================================== */
#define MAX(a, b) ({ \
    __typeof__(a) _a = (a); \
    __typeof__(b) _b = (b); \
    _a > _b ? _a : _b; \
})

#define SWAP(a, b) ({ \
    __typeof__(a) _tmp = (a); \
    (a) = (b); \
    (b) = _tmp; \
})

void demo_statement_expressions() {
    printf("=== STATEMENT EXPRESSIONS ===\n");
    
    int x = 10, y = 20;
    printf("MAX(%d, %d) = %d\n", x, y, MAX(x, y));
    
    SWAP(x, y);
    printf("After SWAP: x=%d, y=%d\n\n", x, y);
}

/* ========================================
   TRICK 5: Flexible Array Members
   Dynamic struct sizing
   ======================================== */
typedef struct {
    int length;
    int data[];  // Must be last member!
} DynamicArray;

void demo_flexible_arrays() {
    printf("=== FLEXIBLE ARRAY MEMBERS ===\n");
    
    int size = 5;
    DynamicArray* arr = malloc(sizeof(DynamicArray) + size * sizeof(int));
    arr->length = size;
    
    for (int i = 0; i < size; i++) {
        arr->data[i] = i * 10;
    }
    
    for (int i = 0; i < arr->length; i++) {
        printf("%d ", arr->data[i]);
    }
    printf("\n\n");
    
    free(arr);
}

/* ========================================
   TRICK 6: Bit Field Tricks
   Pack multiple values efficiently
   ======================================== */
typedef struct {
    unsigned int is_active : 1;
    unsigned int level : 4;      // 0-15
    unsigned int type : 3;       // 0-7
    unsigned int reserved : 24;
} Flags;

void demo_bitfields() {
    printf("=== BIT FIELDS ===\n");
    
    Flags f = {1, 12, 5, 0};
    printf("Size of Flags: %zu bytes\n", sizeof(Flags));
    printf("Active: %d, Level: %d, Type: %d\n\n", f.is_active, f.level, f.type);
}

/* ========================================
   TRICK 7: Array Length Macro (Compile-Time)
   Safe array length calculation
   ======================================== */
#define ARRAY_LEN(arr) (sizeof(arr) / sizeof((arr)[0]))

void demo_array_length() {
    printf("=== ARRAY LENGTH MACRO ===\n");
    
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    printf("Array length: %zu\n\n", ARRAY_LEN(numbers));
}

/* ========================================
   TRICK 8: Container_of Macro (Linux Kernel)
   Get struct from member pointer
   ======================================== */
#define container_of(ptr, type, member) ({ \
    const typeof(((type *)0)->member) *__mptr = (ptr); \
    (type *)((char *)__mptr - offsetof(type, member)); })

typedef struct {
    int id;
    char name[50];
    double value;
} Container;

void demo_container_of() {
    printf("=== CONTAINER_OF MACRO ===\n");
    
    Container c = {42, "Test", 3.14};
    double* value_ptr = &c.value;
    
    // Get back to the Container from just the value pointer!
    Container* c_ptr = container_of(value_ptr, Container, value);
    printf("ID: %d, Name: %s\n\n", c_ptr->id, c_ptr->name);
}

/* ========================================
   TRICK 9: Function Pointers in Structs (OOP Style)
   C-style polymorphism
   ======================================== */
typedef struct Shape {
    void (*draw)(struct Shape*);
    void (*area)(struct Shape*);
    int type;
} Shape;

void draw_circle(Shape* s) { printf("Drawing Circle\n"); }
void area_circle(Shape* s) { printf("Circle area calculation\n"); }

void draw_square(Shape* s) { printf("Drawing Square\n"); }
void area_square(Shape* s) { printf("Square area calculation\n"); }

void demo_function_pointers() {
    printf("=== FUNCTION POINTERS (OOP Style) ===\n");
    
    Shape circle = {draw_circle, area_circle, 1};
    Shape square = {draw_square, area_square, 2};
    
    circle.draw(&circle);
    square.draw(&square);
    printf("\n");
}

/* ========================================
   TRICK 10: Duff's Device
   Loop unrolling optimization
   ======================================== */
void duffs_device(char* dest, const char* src, size_t count) {
    size_t n = (count + 7) / 8;
    switch (count % 8) {
        case 0: do { *dest++ = *src++;
        case 7:      *dest++ = *src++;
        case 6:      *dest++ = *src++;
        case 5:      *dest++ = *src++;
        case 4:      *dest++ = *src++;
        case 3:      *dest++ = *src++;
        case 2:      *dest++ = *src++;
        case 1:      *dest++ = *src++;
               } while (--n > 0);
    }
}

void demo_duffs_device() {
    printf("=== DUFF'S DEVICE ===\n");
    
    char src[] = "Hello World!";
    char dest[20] = {0};
    
    duffs_device(dest, src, strlen(src));
    printf("Copied: %s\n\n", dest);
}

/* ========================================
   TRICK 11: Zero-Length Arrays (GCC Extension)
   Sentinel in structs
   ======================================== */
typedef struct {
    int count;
    char data[0];  // Zero-length!
} Buffer;

void demo_zero_length() {
    printf("=== ZERO-LENGTH ARRAYS ===\n");
    printf("Size of Buffer struct: %zu bytes\n\n", sizeof(Buffer));
}

/* ========================================
   TRICK 12: Comma Operator for Multi-Init
   Execute multiple statements in one
   ======================================== */
void demo_comma_operator() {
    printf("=== COMMA OPERATOR TRICKS ===\n");
    
    int a, b, c;
    // All in one line!
    c = (a = 5, b = 10, a + b);
    printf("a=%d, b=%d, c=%d\n\n", a, b, c);
}

/* ========================================
   TRICK 13: Inline Assembly (x86)
   Direct CPU instructions
   ======================================== */
void demo_inline_asm() {
    printf("=== INLINE ASSEMBLY ===\n");
    
    int a = 10, b = 20, result;
    
    #ifdef __GNUC__
    __asm__ ("addl %%ebx, %%eax;"
             : "=a" (result)
             : "a" (a), "b" (b));
    printf("10 + 20 via ASM = %d\n\n", result);
    #else
    printf("Inline assembly not supported on this compiler\n\n");
    #endif
}

/* ========================================
   TRICK 14: Compile-Time Assertions
   Catch errors at compile time
   ======================================== */
#define STATIC_ASSERT(expr, msg) \
    typedef char static_assert_##msg[(expr) ? 1 : -1]

STATIC_ASSERT(sizeof(int) == 4, int_must_be_4_bytes);

void demo_static_assert() {
    printf("=== COMPILE-TIME ASSERTIONS ===\n");
    printf("If you see this, sizeof(int)==4 on your system!\n\n");
}

/* ========================================
   TRICK 15: Coroutines with switch/case
   State machine implementation
   ======================================== */
typedef struct {
    int state;
    int counter;
} Coroutine;

int coroutine_run(Coroutine* c) {
    switch (c->state) {
        case 0:  // Start
            c->counter = 0;
            
        case 1:  // Loop
            while (c->counter < 5) {
                c->state = 1;
                return c->counter++;
            }
            
        case 2:  // End
            c->state = 2;
            return -1;
    }
    return -1;
}

void demo_coroutines() {
    printf("=== COROUTINES (State Machine) ===\n");
    
    Coroutine c = {0, 0};
    int val;
    while ((val = coroutine_run(&c)) != -1) {
        printf("Yielded: %d\n", val);
    }
    printf("\n");
}

/* ========================================
   TRICK 16: Tagged Unions (Type-Safe Unions)
   Safe union access
   ======================================== */
typedef enum { INT_TYPE, FLOAT_TYPE, STRING_TYPE } ValueType;

typedef struct {
    ValueType type;
    union {
        int i;
        float f;
        char* s;
    } data;
} Value;

void print_value(Value v) {
    switch (v.type) {
        case INT_TYPE:    printf("Int: %d\n", v.data.i); break;
        case FLOAT_TYPE:  printf("Float: %.2f\n", v.data.f); break;
        case STRING_TYPE: printf("String: %s\n", v.data.s); break;
    }
}

void demo_tagged_unions() {
    printf("=== TAGGED UNIONS ===\n");
    
    Value v1 = {INT_TYPE, {.i = 42}};
    Value v2 = {FLOAT_TYPE, {.f = 3.14f}};
    Value v3 = {STRING_TYPE, {.s = "Hello"}};
    
    print_value(v1);
    print_value(v2);
    print_value(v3);
    printf("\n");
}

/* ========================================
   TRICK 17: Obscure Operators
   Hidden gems in C
   ======================================== */
void demo_obscure_operators() {
    printf("=== OBSCURE OPERATORS ===\n");
    
    int x = 10;
    
    // Goes to zero operator
    while (x --> 0) {  // Actually x-- > 0
        // Loop from 9 to 0
    }
    printf("x after 'goes to': %d\n", x);
    
    // Array indexing trick
    int arr[] = {1, 2, 3, 4, 5};
    printf("arr[2] = %d, 2[arr] = %d (same!)\n\n", arr[2], 2[arr]);
}

/* ========================================
   TRICK 18: Abuse the Ternary Operator
   Conditional lvalue
   ======================================== */
void demo_ternary_lvalue() {
    printf("=== TERNARY AS LVALUE ===\n");
    
    int a = 5, b = 10;
    int condition = 1;
    
    // Assign to either a or b based on condition!
    (condition ? a : b) = 99;
    
    printf("a=%d, b=%d\n\n", a, b);
}

/* ========================================
   MAIN: Run All Demos
   ======================================== */
#include <stdlib.h>
#include <stddef.h>

int main() {
    demo_xmacro();
    demo_compound_literals();
    demo_designated_init();
    demo_statement_expressions();
    demo_flexible_arrays();
    demo_bitfields();
    demo_array_length();
    demo_container_of();
    demo_function_pointers();
    demo_duffs_device();
    demo_zero_length();
    demo_comma_operator();
    demo_inline_asm();
    demo_static_assert();
    demo_coroutines();
    demo_tagged_unions();
    demo_obscure_operators();
    demo_ternary_lvalue();
    
    printf("🎯 All tricks demonstrated!\n");
    return 0;
}
