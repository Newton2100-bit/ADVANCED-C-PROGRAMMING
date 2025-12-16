Here are the main macros found in `sys/wait.h`:

**Status Checking Macros:**

- **`WIFEXITED(status)`** - Returns true if child terminated normally
- **`WEXITSTATUS(status)`** - Returns exit status of child (only if WIFEXITED is true)
- **`WIFSIGNALED(status)`** - Returns true if child terminated due to a signal
- **`WTERMSIG(status)`** - Returns signal number that caused termination
- **`WCOREDUMP(status)`** - Returns true if child produced a core dump (not POSIX)
- **`WIFSTOPPED(status)`** - Returns true if child is currently stopped
- **`WSTOPSIG(status)`** - Returns signal number that stopped the child
- **`WIFCONTINUED(status)`** - Returns true if child was resumed by SIGCONT

**Options for wait() functions:**

- **`WNOHANG`** - Return immediately if no child has exited
- **`WUNTRACED`** - Also return for stopped children
- **`WCONTINUED`** - Also return for continued children

**Example usage:**

```c
int status;
pid_t pid = wait(&status);

if (WIFEXITED(status)) {
    printf("Child exited with status: %d\n", WEXITSTATUS(status));
}
else if (WIFSIGNALED(status)) {
    printf("Child killed by signal: %d\n", WTERMSIG(status));
}
```

You can see the full documentation with:
```bash
man 2 wait
```


These macros are used when you need to **manage child processes** in C. Here are the main scenarios:

**1. After forking a process:**
```c
pid_t pid = fork();
if (pid == 0) {
    // Child process
    execl("/bin/ls", "ls", "-l", NULL);
    exit(1);  // If exec fails
} else {
    // Parent process
    int status;
    wait(&status);  // Wait for child to finish
    
    if (WIFEXITED(status)) {
        printf("Child exited with code: %d\n", WEXITSTATUS(status));
    }
}
```

**2. Building shells (like bash):**
When you run commands in a shell, the shell forks and uses these macros to determine if the command succeeded or failed.

**3. Process monitoring/supervision:**
Checking if a child process crashed (signaled) vs exited normally.

**4. Daemon processes:**
Managing worker processes and restarting them if they crash.

**Common real-world examples:**

- **Your shell (bash/zsh)** - uses these to report command exit status (`$?`)
- **Web servers** - spawn worker processes and monitor them
- **Init systems** - manage service processes
- **Job control** - implementing background jobs with Ctrl+Z

**In dwm (which you're using)**, these concepts appear when the window manager spawns programs - it needs to know if they started successfully or failed.

The `wait()` family and these macros are fundamental to Unix/Linux process management!
