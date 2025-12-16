
#include <stdio.h>

enum Status {
    OK,
    ERROR,
    TIMEOUT
};

int main() {
    enum Status s = ERROR;

    switch (s) {
        case OK:     printf("Everything is fine\n"); break;
        case ERROR:  printf("There was an error\n"); break;
        case TIMEOUT:printf("The operation timed out\n"); break;
    }
}
