
I got you — you want to understand **what actually happens on the stack/registers**, not how to use the safe API.
That’s fair. But first: **your current pointer trick will *never* work**, because you’re mixing pointer arithmetic on local variables with assumptions about argument layout.

So let’s do this properly:
I’ll show you **exactly where the variadic arguments are located in memory** on a real platform (x86-64 System V ABI, the most common for Linux/macOS).

---

# ✅ Why `(&count - sizeof(int))` cannot work

`count` is a **local variable** (stored in the function’s stack frame), not the original stack argument.

Inside `integers()` the call stack looks like this (simplified):

```
| caller stack frame |
-----------------------
| return address      |
| old rbp             |
| local variable: count  <-- you are here (&count)
| local variable: arguments (va_list)
| ...
```

But the arguments were passed *before* the function prologue even set up the frame.
On x86-64, most of them aren’t even on the stack — **they go in registers**.

So `&count` has *zero* relationship to the original arguments.

---

# ✅ How variadic arguments really work (x86-64 System V)

On this ABI:

* The first integer/pointer args go in registers:

  * `rdi` = count
  * `rsi` = first variadic argument (78)
  * `rdx` = second variadic argument (45)

Nothing is on the stack yet.

`va_list` for x86-64 is actually a struct containing register save areas:

```c
typedef struct {
    unsigned int gp_offset;      // how many bytes of GPRs consumed
    unsigned int fp_offset;
    void *overflow_arg_area;     // where stack args would go
    void *reg_save_area;         // copy of the argument registers
} va_list[1];
```

That’s why `va_start` makes a copy of the registers into a buffer, and `va_arg` just walks that buffer.

---

# ✅ If you want to “manually” grab what `va_arg` would grab

Here’s how to actually do it *unsafely but correctly*:

```c
#include <stdio.h>
#include <stdarg.h>

int integers(int count, ...) {
    va_list ap;
    va_start(ap, count);

    // Get raw internals of va_list
    struct {
        unsigned int gp_offset;
        unsigned int fp_offset;
        void *overflow_arg_area;
        void *reg_save_area;
    } *vap = (void*)&ap;

    int *reg_area = vap->reg_save_area;

    int first = *(int*)((char*)reg_area + vap->gp_offset);
    vap->gp_offset += 8;

    int second = *(int*)((char*)reg_area + vap->gp_offset);
    vap->gp_offset += 8;

    printf("1st arg = %d\n", first);
    printf("2nd arg = %d\n", second);

    va_end(ap);
}
```

This works because we are literally **re-implementing `va_arg`** using the ABI.

---

# 🚨 But this only works on:

✔ Linux x86-64
✔ macOS x86-64

It **will not work** on:

* Windows x64 (different ABI)
* ARM / AArch64
* 32-bit systems
* Any optimization differences

---

# 🧠 TL;DR What You Wanted to Know

### Where are the variadic arguments in your program?

On x86-64 System V:

```
count  → rdi
78     → rsi
45     → rdx
```

`va_list` contains a saved copy of those registers in a buffer that looks like:

```
reg_save_area:
   [0x00] rdi (count)
   [0x08] rsi (78)
   [0x10] rdx (45)
   [0x18] rcx
   [0x20] r8
   [0x28] r9
```

`va_arg` simply indexes into this buffer.

---

# ✔ If you want, I can write:

* a version that prints raw memory around the stack frame
* a version that prints the entire `va_list` internal structure
* versions for ARM, Windows, or 32-bit

Just tell me which direction you want to explore.
