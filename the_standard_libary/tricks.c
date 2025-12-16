/* It is worth noting that the c standard library has 15 distinct headers 

   	Header files contain
   	> function prototypes
   	> type definations
   	> macro definations

   	Restrictions of the library
	   > One can't reuse the types and names used in the header files
	   >  don't redefine or use names used in the header files.
	   > You should not use names that 
		1. begin with double underscores
		2. begin with an underscore and a capital letter

	AVAILABLE HEADER FILES.
		1. assert.h
		2. ctype.h
		3. errno.h
		4. float.h
		5. limits.h
		6. locale.h
		7. math.h
		8. setjmp.h
		9. signal.h
		10. stdarg.h
		11. stddef.h
		12. stdio.h
		13. stdlib.h
		14. string.h
		15. time.h

	<stddef.h>
		- It does not declare an y function, It provides definations of fre
		used types and macros 
		- ptrdiff_t -> type of the result of substraction of two pointers.
		- size_t -> the return type of sizeof() operator
		- wchar_t -> A type large enougth to represent all the characters in the current surported locale

*/
/* Under stddef lets look at the macro <offsetof> */



	


	


