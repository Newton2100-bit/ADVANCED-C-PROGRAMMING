
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

int main(int argc, char *argv[]) {
    int opt;
    int verbose = 0;
    char *filename = NULL;

    static struct option long_options[] = {
        {"file", required_argument, 0, 'f'},
        {"verbose", no_argument, 0, 'v'},
        {"help", no_argument, 0, 'h'},
        {0, 0, 0, 0}
    };

    while ((opt = getopt_long(argc, argv, "f:vh", long_options, NULL)) != -1) {
        switch (opt) {
            case 'f':
                filename = optarg;
                break;
            case 'v':
                verbose = 1;
                break;
            case 'h':
                printf("Usage: %s --file <name> [--verbose]\n", argv[0]);
                exit(0);
            case '?':
                // getopt_long already printed an error
                exit(1);
        }
    }

    if (verbose) {
        printf("Verbose mode ON\n");
    }
    if (filename) {
        printf("Filename: %s\n", filename);
    }

    return 0;
}
