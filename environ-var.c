#include <unistd.h>
#include <stdio.h>

extern char **environ;  // Declared in unistd.h on POSIX

int main(void) {
    for (char **env = environ; *env != NULL; env++) {
        printf("%s\n", *env);
    }
    return 0;
}
