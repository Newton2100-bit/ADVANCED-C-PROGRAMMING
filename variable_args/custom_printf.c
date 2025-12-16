/* These is a simple project
   It will focus on a simple custom printf function
   It is supposed to enhance understanding of the variadic functions
   in c language
 */

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

int custom_printf(char *fmt, ...){
	int count = 0;
	va_list arguments;
	va_start(arguments, fmt);
	
	int  fmt_length = strlen(fmt);
	while (true)
	{
		/* i,d = int, s = string, f = float, d = double, o = octal, c = character 
		   we have c for character but i guess it is graduated to int
		   and flaot to double i think
		 */
	    i
