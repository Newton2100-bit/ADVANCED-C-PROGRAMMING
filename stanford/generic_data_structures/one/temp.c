#include <stdio.h>
#include <ctype.h>

int main(void){
    char spaces[] = {' ', '\n', '\r'};
    for (int i = 0; i < sizeof(spaces); i++)
    {
	printf("%c is taken as a chacter %i",spaces[i], isspace(spaces[i]));
    }
    return 0;
}
