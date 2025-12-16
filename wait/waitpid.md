These are **options/flags** you pass to `waitpid()` to control its behavior:

**1. `WNOHANG` - Non-blocking wait**

Used when you don't want the parent to hang/block waiting for a child:

```c
int status;
pid_t result = waitpid(-1, &status, WNOHANG);

if (result == 0) {
    // No child has exited yet, parent continues
    printf("Child still running, doing other work...\n");
} else if (result > 0) {
    // Child exited
    printf("Child %d finished\n", result);
}
```

**Use cases:**
- Event loops (like in GUI apps or game loops)
- Servers handling multiple clients
- Checking child status without blocking

**2. `WUNTRACED` - Detect stopped children**

Returns when a child is **stopped** (Ctrl+Z / SIGSTOP), not just terminated:

```c
waitpid(pid, &status, WUNTRACED);

if (WIFSTOPPED(status)) {
    printf("Child stopped by signal %d\n", WSTOPSIG(status));
}
```

**Use cases:**
- **Job control in shells** (implementing Ctrl+Z, `fg`, `bg` commands)
- Debuggers (like gdb)

**3. `WCONTINUED` - Detect resumed children**

Returns when a stopped child is **resumed** by SIGCONT:

```c
waitpid(pid, &status, WCONTINUED);

if (WIFCONTINUED(status)) {
    printf("Child was resumed\n");
}
```

**Use cases:**
- **Shell job control** (tracking when background jobs resume)
- Process supervisors

**Combining flags:**
```c
// Non-blocking check for stopped/continued children
waitpid(-1, &status, WNOHANG | WUNTRACED | WCONTINUED);
```

**Real example - Shell implementation:**
```c
// Shell checking background jobs without blocking
pid_t pid;
while ((pid = waitpid(-1, &status, WNOHANG | WUNTRACED)) > 0) {
    if (WIFEXITED(status)) {
        printf("[%d] Done\n", pid);
    } else if (WIFSTOPPED(status)) {
        printf("[%d] Stopped\n", pid);
    }
}
```

These are essential for implementing shells like bash!
