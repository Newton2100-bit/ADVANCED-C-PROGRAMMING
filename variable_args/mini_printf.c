#include <stdio.h>
#include <stdarg.h>

void mini_printf(const char *fmt, ...){
	va_list args;
	va_start(args, fmt);
	
	while(*fmt){
		if(*fmt == '%'){
			fmt++;

			switch(*fmt){
				case 'd':
				case 'i':
					printf("%d", va_arg(args, int));
					break;
				case 's':
					printf("%s", va_arg(args, char*));
					break;
				case 'c':
					putchar((char)va_arg(args, int));
					break;
				case 'f':
					printf("%f", va_arg(args, double));
					break;
				case '%':
					putchar('%');
					break;
			}
		}
		else{
			putchar(*fmt);
		}
		fmt++;
	}
	va_end(args);
}

int main(void){
	mini_printf("Hi %s, age: %d,  grade: %c, height: %f%%\n",
			"ada", 20, 'A', 5.9);
	return 0;
}
