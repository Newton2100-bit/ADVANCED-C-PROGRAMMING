/*
   The prototype of printf is
   printf(format_string, arg1, arg2, arg3, arg4 ... , argn);
   A placeholder can be comprised of 
   %[flags][width][.precison][length]type
   
   [Flags]
   There are five flag characters -,+,space,# and 0
   - : left justification
   + : display signed vlaues
	space : display signed vlaues with a leading space if positive and minus sign if negative 
	0 : pads the field with zeros instead of spaces 
	[Output width]

	[Lenght modifier]
		The optional length modifier specifies the size of the argumant.
		we have l to denote long
		
		[for u, i, d]
		h -> short
		hh -> signed char
		l -> long
		ll -> long long

		[for floating point numbers]
		l for double (e, E, f, E)
		L for long double (e, E, f, F)


		so worth noting is (hhd , hhi adenote signed char and hhu denotes unsigned char)


 */
#include <stdio.h>
#define PI 3.14

int main(void){
	printf("%+010.2f\n", PI);
	printf("%010.2f\n", PI);

	char name[] = "newton irungu mwaura";
	printf("%0-7.5s\n", name);
	return 0;
}

