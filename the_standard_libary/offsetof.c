/*
#include <stdio.h>
#include <stddef.h>

int main(void){
    struct a{
	char a;
	int b[2];
	double c;
    }random;

    printf("size of int %zi.\n", sizeof(int));
    printf("Size of char is %zi.\n", sizeof(char));
    printf("Size of double is %zi.\n", sizeof(double));
    printf("the size of our struct is %zi.\n", sizeof(struct a));
    int offsetofa = offsetof(random, a);
    printf("the offset of a is %i bytes.\n", offsetofa);
    int offsetofb = offsetof(random, b);
    printf("the offset of a is %i bytes.\n", offsetofb);
    int offsetofc = offsetof(random, c);
    printf("the offset of a is %i bytes.\n", offsetofc);
    return 0;
}
*/
       #include <stddef.h>
       #include <stdio.h>
       #include <stdlib.h>

       int
       main(void)
       {
           typedef struct s {
               int i;
               char c;
               double d;
               char a[];
           }random;

           /* Output is compiler dependent */
           printf("offsets: i=%zu; c=%zu; d=%zu a=%zu\n",
                  offsetof(random, i), offsetof(random, c),
                  offsetof(random, d), offsetof(random, a));

           printf("offsets: i=%zu; c=%zu; d=%zu a=%zu\n",
                  offsetof(struct s, i), offsetof(struct s, c),
                  offsetof(struct s, d), offsetof(struct s, a));
           printf("sizeof(struct s)=%zu\n", sizeof(struct s));

           exit(EXIT_SUCCESS);
       }
