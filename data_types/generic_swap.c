#include <stdio.h>
#include <string.h>

void swap(void *, void*, int);

int main(void){
	short s = 5;
	int i = 44;
	printf("BEFORE SWAP: s = %hi i = %i\n", s, i);
	swap(&s, &i, sizeof(short));
	printf("AFTER SWAP: s = %hi i = %i\n", s, i);
	return 0;
}

void swap(void *vp1, void *vp2, int size){
    char buffer[size];
    memcpy(buffer, vp1, size);
    memcpy(vp1, vp2, size);
    memcpy(vp2, buffer, size);
}

