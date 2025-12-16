Great questions! Let me explain these important system calls:

## **`dup()` and `dup2()` - Duplicate File Descriptors**

These duplicate file descriptors, commonly used for **I/O redirection**.

**Basic `dup()`:**
```c
int fd = open("file.txt", O_RDONLY);
int fd_copy = dup(fd);  // Creates a copy pointing to same file
// Both fd and fd_copy refer to the same open file
```

**`dup2()` - More useful (specify target fd):**
```c
// Redirect stdout to a file
int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
dup2(fd, STDOUT_FILENO);  // Now stdout goes to output.txt
close(fd);

printf("This goes to output.txt\n");  // Written to file!
```

**Common use cases:**

**1. Implementing shell redirection (`>`, `<`, `|`):**
```c
// Implementing: command > output.txt
pid_t pid = fork();
if (pid == 0) {
    int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    dup2(fd, STDOUT_FILENO);  // Redirect stdout
    close(fd);
    
    execlp("ls", "ls", "-l", NULL);
}
wait(NULL);
```

**2. Implementing pipes (`|`):**
```c
// Implementing: ls | wc -l
int pipefd[2];
pipe(pipefd);

if (fork() == 0) {
    // Child 1: ls
    dup2(pipefd[1], STDOUT_FILENO);  // stdout -> pipe write end
    close(pipefd[0]);
    close(pipefd[1]);
    execlp("ls", "ls", NULL);
}

if (fork() == 0) {
    // Child 2: wc
    dup2(pipefd[0], STDIN_FILENO);   // stdin <- pipe read end
    close(pipefd[0]);
    close(pipefd[1]);
    execlp("wc", "wc", "-l", NULL);
}

close(pipefd[0]);
close(pipefd[1]);
wait(NULL);
wait(NULL);
```

**3. Saving and restoring stdout/stdin:**
```c
int saved_stdout = dup(STDOUT_FILENO);  // Save original stdout

// Redirect stdout temporarily
int fd = open("temp.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
dup2(fd, STDOUT_FILENO);
printf("Goes to file\n");
close(fd);

// Restore original stdout
dup2(saved_stdout, STDOUT_FILENO);
close(saved_stdout);
printf("Goes to terminal\n");
```

---

## **`setbuf()` and `setvbuf()` - Control Buffering**

These control how buffering works for FILE streams (not raw file descriptors).

**Three buffering modes:**
- **Fully buffered** - Data written when buffer fills
- **Line buffered** - Data written on newline (default for terminal)
- **Unbuffered** - Data written immediately

**`setbuf()` - Simple version:**
```c
FILE *fp = fopen("file.txt", "w");
setbuf(fp, NULL);  // Disable buffering (unbuffered)
// OR
char buffer[BUFSIZ];
setbuf(fp, buffer);  // Use custom buffer (fully buffered)
```

**`setvbuf()` - More control (preferred):**
```c
FILE *fp = fopen("file.txt", "w");

// Unbuffered (immediate write)
setvbuf(fp, NULL, _IONBF, 0);

// Line buffered (flush on \n)
setvbuf(fp, NULL, _IOLBF, 0);

// Fully buffered with custom size
char buffer[8192];
setvbuf(fp, buffer, _IOFBF, sizeof(buffer));
```

**Common use cases:**

**1. Debugging output:**
```c
// Make sure errors appear immediately
setvbuf(stderr, NULL, _IONBF, 0);
fprintf(stderr, "Error happened!\n");  // Appears immediately
```

**2. Progress indicators:**
```c
// Without line buffering, progress won't show until \n
setvbuf(stdout, NULL, _IONBF, 0);
for (int i = 0; i < 100; i++) {
    printf("\rProgress: %d%%", i);
    fflush(stdout);  // Or just unbuffer it
    usleep(50000);
}
```

**3. Performance optimization:**
```c
// Large buffer for better performance with big files
FILE *fp = fopen("huge.dat", "rb");
char buffer[1048576];  // 1MB buffer
setvbuf(fp, buffer, _IOFBF, sizeof(buffer));
```

**4. Real-time logging:**
```c
FILE *log = fopen("app.log", "a");
setvbuf(log, NULL, _IOLBF, 0);  // Line buffered
fprintf(log, "Event occurred\n");  // Written immediately
```

**Key differences:**
- `dup()` works with **file descriptors** (low-level, integer handles)
- `setvbuf()` works with **FILE streams** (high-level, buffered I/O)

**When to use:**
- `dup/dup2`: Shell redirection, pipes, daemon process setup
- `setvbuf`: Control when data is actually written (debugging, performance, logging)

Need examples for any specific scenario?
