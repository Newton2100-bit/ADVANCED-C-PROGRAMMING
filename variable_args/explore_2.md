/* =====================================================================
   DEEP DIVE: C PROGRAMMING TRICKS - EXPLAINED IN DETAIL
   ===================================================================== */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

/* =====================================================================
   TRICK 1: X-MACROS - The DRY Principle Champion
   
   THE PROBLEM: You have an enum and want string names for each value.
   Normally you'd maintain two lists that can get out of sync:
   
   enum Color { RED, GREEN, BLUE };
   char* names[] = {"Red", "Green", "Blue"};  // Easy to mess up!
   
   THE SOLUTION: Define your data ONCE, use it EVERYWHERE.
   ===================================================================== */

// This is your single source of truth
#define COLOR_LIST \
    X(RED, "Red", 0xFF0000) \
    X(GREEN, "Green", 0x00FF00) \
    X(BLUE, "Blue", 0x0000FF) \
    X(YELLOW, "Yellow", 0xFFFF00) \
    X(PURPLE, "Purple", 0x800080)

// First expansion: Generate the enum
// The preprocessor replaces X(name, str, hex) with just "name,"
#define X(name, str, hex) name,
typedef enum { 
    COLOR_LIST 
    COLOR_COUNT  // Bonus: automatic count!
} Color;
#undef X  // Clean up so we can reuse X

// Second expansion: Generate string array
#define X(name, str, hex) str,
const char* color_names[] = { COLOR_LIST };
#undef X

// Third expansion: Generate hex values
#define X(name, str, hex) hex,
const int color_hex[] = { COLOR_LIST };
#undef X

void demo_xmacro() {
    printf("=== X-MACRO DEEP DIVE ===\n");
    printf("Why it's awesome: Add a color once, get enum + string + hex!\n\n");
    
    for (int i = 0; i < COLOR_COUNT; i++) {
        printf("Color %d: %-8s (0x%06X)\n", i, color_names[i], color_hex[i]);
    }
    
    // Real-world usage
    Color myColor = PURPLE;
    printf("\nSelected: %s\n", color_names[myColor]);
    printf("\n");
}

/* =====================================================================
   TRICK 2: COMPOUND LITERALS - Temporary Objects
   
   C99 lets you create objects "on the fly" without declaring variables.
   Think of it like anonymous objects in other languages.
   ===================================================================== */

typedef struct { int x, y; } Point;
typedef struct { Point topLeft, bottomRight; } Rectangle;

Point add_points(Point a, Point b) {
    return (Point){a.x + b.x, a.y + b.y};
}

void demo_compound_literals() {
    printf("=== COMPOUND LITERALS DEEP DIVE ===\n");
    
    // OLD WAY: Verbose
    Point p1 = {10, 20};
    Point p2 = {5, 15};
    Point result1 = add_points(p1, p2);
    
    // NEW WAY: Direct!
    Point result2 = add_points((Point){10, 20}, (Point){5, 15});
    
    printf("Results equal: %d\n", 
           result1.x == result2.x && result1.y == result2.y);
    
    // Works with nested structs
    Rectangle rect = {
        .topLeft = (Point){0, 0},
        .bottomRight = (Point){100, 100}
    };
    printf("Rectangle: (%d,%d) to (%d,%d)\n",
           rect.topLeft.x, rect.topLeft.y,
           rect.bottomRight.x, rect.bottomRight.y);
    
    // Array literals!
    int sum = 0;
    int *arr = (int[]){10, 20, 30, 40, 50};  // Creates temporary array
    for (int i = 0; i < 5; i++) sum += arr[i];
    printf("Sum: %d\n\n", sum);
}

/* =====================================================================
   TRICK 3: DESIGNATED INITIALIZERS - Skip the Boring Parts
   
   Initialize only the fields you care about. Rest get zeroed.
   Great for config structs with many optional fields.
   ===================================================================== */

typedef struct {
    char name[50];
    int age;
    double salary;
    int active;
    int level;
    char department[30];
    char email[50];
} Employee;

void demo_designated_init() {
    printf("=== DESIGNATED INITIALIZERS DEEP DIVE ===\n");
    
    // Only set what matters, rest is zero/NULL
    Employee emp1 = {
        .name = "Alice",
        .salary = 95000.0,
        .active = 1
        // age, level, dept, email all zero/empty!
    };
    
    printf("Name: %s, Active: %d, Age: %d (defaulted)\n",
           emp1.name, emp1.active, emp1.age);
    
    // Order doesn't matter!
    Employee emp2 = {
        .active = 1,
        .name = "Bob",
        .email = "bob@example.com",
        .salary = 75000.0
    };
    
    // Sparse arrays - set specific indices
    int lookup[100] = {
        [0] = 1,
        [10] = 11,
        [50] = 51,
        [99] = 100
    };
    printf("lookup[10] = %d, lookup[11] = %d (rest are 0)\n\n",
           lookup[10], lookup[11]);
}

/* =====================================================================
   TRICK 4: STATEMENT EXPRESSIONS - Macros That Don't Suck
   
   PROBLEM: Normal macros evaluate arguments multiple times:
   #define MAX(a,b) ((a) > (b) ? (a) : (b))
   MAX(x++, y++)  // BUG! Increments winner twice!
   
   SOLUTION: Statement expressions (GCC extension)
   ===================================================================== */

// Safe MAX - arguments evaluated exactly once
#define MAX(a, b) ({ \
    __typeof__(a) _a = (a); \
    __typeof__(b) _b = (b); \
    _a > _b ? _a : _b; \
})

// SWAP without temp variable clutter
#define SWAP(a, b) ({ \
    __typeof__(a) _tmp = (a); \
    (a) = (b); \
    (b) = _tmp; \
})

// Multi-statement macro with return value
#define DEBUG_PRINT(x) ({ \
    printf("DEBUG: %s = ", #x); \
    printf("%d\n", x); \
    (x); \
})

void demo_statement_expressions() {
    printf("=== STATEMENT EXPRESSIONS DEEP DIVE ===\n");
    
    int x = 5, y = 10;
    
    // Safe from double evaluation
    int z = MAX(x++, y++);
    printf("MAX with post-increment: z=%d, x=%d, y=%d\n", z, x, y);
    
    // SWAP without temp variable visible
    int a = 100, b = 200;
    SWAP(a, b);
    printf("After SWAP: a=%d, b=%d\n", a, b);
    
    // Multi-line logic in macro
    int val = DEBUG_PRINT(42);
    printf("Returned: %d\n\n", val);
}

/* =====================================================================
   TRICK 5: FLEXIBLE ARRAY MEMBERS - Dynamic Struct Tails
   
   Allocate a struct with variable-length array at the end.
   Common in networking, serialization, strings.
   ===================================================================== */

typedef struct {
    int id;
    size_t length;
    char data[];  // MUST be last! Zero-size placeholder
} Message;

typedef struct {
    int type;
    int count;
    double values[];
} Packet;

void demo_flexible_arrays() {
    printf("=== FLEXIBLE ARRAY MEMBERS DEEP DIVE ===\n");
    
    // Allocate struct + array space in one block
    const char* text = "Hello, World!";
    size_t text_len = strlen(text) + 1;
    
    Message* msg = malloc(sizeof(Message) + text_len);
    msg->id = 42;
    msg->length = text_len;
    strcpy(msg->data, text);
    
    printf("Message ID: %d\n", msg->id);
    printf("Message: %s\n", msg->data);
    printf("Total size: %zu bytes\n", sizeof(Message) + text_len);
    
    // Another example with numbers
    int num_count = 5;
    Packet* pkt = malloc(sizeof(Packet) + num_count * sizeof(double));
    pkt->type = 1;
    pkt->count = num_count;
    
    for (int i = 0; i < num_count; i++) {
        pkt->values[i] = i * 1.5;
    }
    
    printf("\nPacket values: ");
    for (int i = 0; i < pkt->count; i++) {
        printf("%.1f ", pkt->values[i]);
    }
    printf("\n\n");
    
    free(msg);
    free(pkt);
}

/* =====================================================================
   TRICK 6: CONTAINER_OF - Pointer Magic from Linux Kernel
   
   Given a pointer to a struct member, get the parent struct pointer.
   Uses offsetof() to calculate the address difference.
   ===================================================================== */

#define container_of(ptr, type, member) ({ \
    const typeof(((type *)0)->member) *__mptr = (ptr); \
    (type *)((char *)__mptr - offsetof(type, member)); })

typedef struct {
    int id;
    char name[50];
    double value;
    int count;
} Container;

void demo_container_of() {
    printf("=== CONTAINER_OF DEEP DIVE ===\n");
    
    Container c = {42, "Test Container", 3.14159, 100};
    
    // We only have a pointer to 'value' member
    double* value_ptr = &c.value;
    
    printf("value_ptr points to: %p (value=%.5f)\n", 
           (void*)value_ptr, *value_ptr);
    
    // Magic! Recover the whole struct
    Container* recovered = container_of(value_ptr, Container, value);
    
    printf("Recovered container at: %p\n", (void*)recovered);
    printf("ID: %d, Name: %s, Count: %d\n",
           recovered->id, recovered->name, recovered->count);
    
    // How it works:
    printf("\nHow it works:\n");
    printf("  Container address: %p\n", (void*)&c);
    printf("  value offset: %zu bytes\n", offsetof(Container, value));
    printf("  value_ptr - offset = %p\n\n",
           (void*)((char*)value_ptr - offsetof(Container, value)));
}

/* =====================================================================
   TRICK 7: DUFF'S DEVICE - Loop Unrolling with switch/case
   
   Invented by Tom Duff at Lucasfilm (1983). Combines loop and switch
   in a way that looks illegal but is perfectly valid C.
   Used for optimization: fewer loop iterations = faster code.
   ===================================================================== */

// Standard copy
void standard_copy(char* to, const char* from, size_t count) {
    while (count--) {
        *to++ = *from++;
    }
}

// Duff's Device - unrolled copy
void duffs_copy(char* to, const char* from, size_t count) {
    size_t n = (count + 7) / 8;  // Ceiling division by 8
    
    switch (count % 8) {  // Handle remainder first
        case 0: do { *to++ = *from++;  // Then fall through
        case 7:      *to++ = *from++;
        case 6:      *to++ = *from++;
        case 5:      *to++ = *from++;
        case 4:      *to++ = *from++;
        case 3:      *to++ = *from++;
        case 2:      *to++ = *from++;
        case 1:      *to++ = *from++;
               } while (--n > 0);  // 8 copies per iteration
    }
}

void demo_duffs_device() {
    printf("=== DUFF'S DEVICE DEEP DIVE ===\n");
    printf("Copies 8 bytes per iteration instead of 1!\n\n");
    
    const char* source = "The quick brown fox jumps over the lazy dog";
    char dest1[100] = {0};
    char dest2[100] = {0};
    
    standard_copy(dest1, source, strlen(source));
    duffs_copy(dest2, source, strlen(source));
    
    printf("Standard: %s\n", dest1);
    printf("Duff's:   %s\n", dest2);
    printf("Both equal: %d\n\n", strcmp(dest1, dest2) == 0);
}

/* =====================================================================
   TRICK 8: FUNCTION POINTERS IN STRUCTS - OOP in C
   
   Simulate polymorphism by storing function pointers in structs.
   Each "object" can have its own implementation.
   ===================================================================== */

typedef struct Shape Shape;

struct Shape {
    void (*draw)(Shape* self);
    double (*area)(Shape* self);
    void (*destroy)(Shape* self);
    void* data;  // Type-specific data
};

typedef struct {
    double radius;
} CircleData;

typedef struct {
    double side;
} SquareData;

void draw_circle(Shape* s) {
    CircleData* c = (CircleData*)s->data;
    printf("  Drawing circle (radius=%.2f)\n", c->radius);
}

double area_circle(Shape* s) {
    CircleData* c = (CircleData*)s->data;
    return 3.14159 * c->radius * c->radius;
}

void draw_square(Shape* s) {
    SquareData* sq = (SquareData*)s->data;
    printf("  Drawing square (side=%.2f)\n", sq->side);
}

double area_square(Shape* s) {
    SquareData* sq = (SquareData*)s->data;
    return sq->side * sq->side;
}

void destroy_shape(Shape* s) {
    free(s->data);
    free(s);
}

Shape* create_circle(double radius) {
    Shape* s = malloc(sizeof(Shape));
    CircleData* data = malloc(sizeof(CircleData));
    data->radius = radius;
    
    s->draw = draw_circle;
    s->area = area_circle;
    s->destroy = destroy_shape;
    s->data = data;
    return s;
}

Shape* create_square(double side) {
    Shape* s = malloc(sizeof(Shape));
    SquareData* data = malloc(sizeof(SquareData));
    data->side = side;
    
    s->draw = draw_square;
    s->area = area_square;
    s->destroy = destroy_shape;
    s->data = data;
    return s;
}

void demo_function_pointers() {
    printf("=== FUNCTION POINTERS (OOP) DEEP DIVE ===\n");
    
    // Array of different shapes - polymorphism!
    Shape* shapes[3];
    shapes[0] = create_circle(5.0);
    shapes[1] = create_square(4.0);
    shapes[2] = create_circle(3.0);
    
    for (int i = 0; i < 3; i++) {
        printf("Shape %d:\n", i);
        shapes[i]->draw(shapes[i]);
        printf("  Area: %.2f\n", shapes[i]->area(shapes[i]));
    }
    
    // Cleanup
    for (int i = 0; i < 3; i++) {
        shapes[i]->destroy(shapes[i]);
    }
    printf("\n");
}

/* =====================================================================
   TRICK 9: TAGGED UNIONS - Type-Safe Unions
   
   Unions alone are dangerous - you can write as int, read as float.
   Add a "tag" to track which member is active.
   ===================================================================== */

typedef enum { 
    TYPE_NONE,
    TYPE_INT, 
    TYPE_FLOAT, 
    TYPE_STRING,
    TYPE_POINT 
} ValueType;

typedef struct {
    ValueType type;
    union {
        int as_int;
        float as_float;
        char* as_string;
        Point as_point;
    } data;
} Value;

Value make_int(int x) {
    Value v = {TYPE_INT};
    v.data.as_int = x;
    return v;
}

Value make_float(float x) {
    Value v = {TYPE_FLOAT};
    v.data.as_float = x;
    return v;
}

Value make_string(const char* s) {
    Value v = {TYPE_STRING};
    v.data.as_string = strdup(s);
    return v;
}

void print_value(Value v) {
    switch (v.type) {
        case TYPE_INT:
            printf("int: %d", v.data.as_int);
            break;
        case TYPE_FLOAT:
            printf("float: %.2f", v.data.as_float);
            break;
        case TYPE_STRING:
            printf("string: \"%s\"", v.data.as_string);
            break;
        case TYPE_POINT:
            printf("point: (%d, %d)", 
                   v.data.as_point.x, v.data.as_point.y);
            break;
        default:
            printf("unknown type");
    }
}

void free_value(Value v) {
    if (v.type == TYPE_STRING) {
        free(v.data.as_string);
    }
}

void demo_tagged_unions() {
    printf("=== TAGGED UNIONS DEEP DIVE ===\n");
    
    Value values[4];
    values[0] = make_int(42);
    values[1] = make_float(3.14f);
    values[2] = make_string("Hello");
    values[3] = (Value){TYPE_POINT, {.as_point = {10, 20}}};
    
    for (int i = 0; i < 4; i++) {
        printf("Value[%d] = ", i);
        print_value(values[i]);
        printf("\n");
    }
    
    // Cleanup
    for (int i = 0; i < 4; i++) {
        free_value(values[i]);
    }
    printf("\n");
}

/* =====================================================================
   TRICK 10: OBSCURE OPERATORS - The "WTF?" Collection
   ===================================================================== */

void demo_obscure_operators() {
    printf("=== OBSCURE OPERATORS DEEP DIVE ===\n");
    
    // 1. "Goes to" operator -->
    printf("1. 'Goes to' operator:\n");
    int x = 10;
    printf("   Countdown: ");
    while (x --> 0) {  // Actually: (x--) > 0
        printf("%d ", x);
    }
    printf("\n");
    
    // 2. Array index commutativity
    printf("\n2. Array indexing trick:\n");
    int arr[] = {10, 20, 30, 40, 50};
    printf("   arr[2] = %d\n", arr[2]);
    printf("   2[arr] = %d (same!)\n", 2[arr]);
    printf("   Why? arr[i] expands to *(arr + i)\n");
    printf("   And addition is commutative: *(arr + i) == *(i + arr)\n");
    
    // 3. XOR swap (no temp variable)
    printf("\n3. XOR swap (no temp):\n");
    int a = 5, b = 10;
    printf("   Before: a=%d, b=%d\n", a, b);
    a ^= b;  // a = a XOR b
    b ^= a;  // b = b XOR (a XOR b) = a
    a ^= b;  // a = (a XOR b) XOR a = b
    printf("   After:  a=%d, b=%d\n", a, b);
    
    // 4. Comma operator
    printf("\n4. Comma operator:\n");
    int result = (printf("   Side effect! "), 42);
    printf("Result: %d\n", result);
    
    printf("\n");
}

/* =====================================================================
   TRICK 11: TERNARY AS LVALUE - Conditional Assignment Target
   ===================================================================== */

void demo_ternary_lvalue() {
    printf("=== TERNARY AS LVALUE DEEP DIVE ===\n");
    
    int x = 10, y = 20;
    int use_x = 1;
    
    printf("Before: x=%d, y=%d\n", x, y);
    
    // Assign to EITHER x or y based on condition!
    (use_x ? x : y) = 999;
    
    printf("After (use_x=1): x=%d, y=%d\n", x, y);
    
    use_x = 0;
    (use_x ? x : y) = 777;
    
    printf("After (use_x=0): x=%d, y=%d\n\n", x, y);
}

/* =====================================================================
   TRICK 12: COROUTINES - State Machines with Switch
   
   Fake coroutines using switch/case and static variables.
   Each call resumes where it left off.
   ===================================================================== */

int fibonacci_generator() {
    static int state = 0;
    static int a = 0, b = 1;
    
    switch (state) {
        case 0:  // First call
            state = 1;
            return a;
            
        case 1:  // Second call
            state = 2;
            return b;
            
        case 2:  // Subsequent calls
            int next = a + b;
            a = b;
            b = next;
            return next;
    }
    return -1;
}

void demo_coroutines() {
    printf("=== COROUTINES DEEP DIVE ===\n");
    printf("Fibonacci sequence (first 10):\n");
    
    for (int i = 0; i < 10; i++) {
        printf("%d ", fibonacci_generator());
    }
    printf("\n\n");
}

/* =====================================================================
   MAIN - Run All Demos
   ===================================================================== */

int main() {
    printf("╔════════════════════════════════════════════════════════╗\n");
    printf("║     C PROGRAMMING TRICKS - DEEP DIVE EDITION           ║\n");
    printf("╚════════════════════════════════════════════════════════╝\n\n");
    
    demo_xmacro();
    demo_compound_literals();
    demo_designated_init();
    demo_statement_expressions();
    demo_flexible_arrays();
    demo_container_of();
    demo_duffs_device();
    demo_function_pointers();
    demo_tagged_unions();
    demo_obscure_operators();
    demo_ternary_lvalue();
    demo_coroutines();
    
    printf("╔════════════════════════════════════════════════════════╗\n");
    printf("║  🎯 All tricks explained and demonstrated!             ║\n");
    printf("╚════════════════════════════════════════════════════════╝\n");
    
    return 0;
}
