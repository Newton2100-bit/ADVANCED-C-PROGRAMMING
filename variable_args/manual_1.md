Oh man, here are **18 mind-bending C tricks** that'll make you go "wait, WHAT?!" 🤯

**The Really Cool Ones:**

1. **X-Macros** - Keep enums and strings synced automatically (game changer!)
2. **Compound Literals** - Create temporary structs/arrays inline (C99 magic)
3. **Designated Initializers** - Skip struct fields, init by name
4. **Statement Expressions** - Multi-line macros that return values (GCC)
5. **Flexible Array Members** - Variable-length structs
6. **Container_of** - Linux kernel trick to get parent struct from member pointer

**The Mind-Bending Ones:**

7. **Duff's Device** - Loop unrolling with switch/case (looks illegal but isn't!)
8. **Coroutines** - Fake coroutines using switch statements
9. **Tagged Unions** - Type-safe unions (proper way to use them)
10. **Function Pointers in Structs** - OOP-style polymorphism in C

**The "Wait, That Works?!" Ones:**

11. **2[array]** instead of **array[2]** - both valid! (a[b] == *(a+b))
12. **x --> 0** - "goes to zero" operator (it's actually `x-- > 0`)
13. **Ternary as lvalue** - `(cond ? a : b) = 99;` assigns to either variable!
14. **Comma operator** - `c = (a=5, b=10, a+b);` executes all, returns last

**The Power User Ones:**

15. **Bit fields** - Pack data into specific bit counts
16. **Inline assembly** - Direct CPU instructions
17. **Compile-time assertions** - Catch errors before runtime
18. **Zero-length arrays** - GCC extension for flexible structs

**Personal favorites:** X-Macros (no more enum/string mismatch!), container_of (pure genius), and Duff's Device (looks like a bug but it's not 😄).

Compile with: `gcc -std=gnu99 tricks.c -o tricks`

Which one blew your mind the most?
