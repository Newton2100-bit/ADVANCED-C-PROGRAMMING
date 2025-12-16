#include <stdio.h>
int main(void){
    int array[3];
    printf("Memory locations.\n");
    printf("%p\n%p\n", array, (array + 1));
    return 0;
}
