No, C doesn't have a built-in function called `inc` that tells you the type of a variable. 

I think you might be confusing this with something else, or perhaps you meant to ask about type-checking functions in general?

## What C Has for Type Information:

1. **`_Generic` (C11)** - I showed you this earlier:
```c
#define get_type(x) _Generic((x), \
    int: "int", \
    double: "double", \
    char*: "char*", \
    default: "unknown" \
)
```

2. **`typeof` (GCC extension)** - Gets the type, doesn't return a string:
```c
typeof(x) y;  // y has same type as x
```

3. **`sizeof`** - Tells you size in bytes:
```c
printf("Size: %zu bytes\n", sizeof(x));
```

## There's No `inc()` Function

If you saw `inc` somewhere, it might be:
- A custom function someone wrote
- Short for "increment" (like `inc(x)` to increment x)
- From a different language (like type introspection in other languages)

Could you share where you saw `inc`? That would help me understand what you're looking for!
