These files only exist as long as the program is running.
Examples;
	C compilers pften create temp files for the compilation process.
stdio.h offers two prototypes for two functions
	1. tmpfile
	2. tmpnam
1. tmpfile
- creates a file that exists until it is closed or the program exists.
- It returns a file pointer.

FILE * ptr = tmpfile();
return NULL if by any chance it fails.

2. tmpnam (temp name)
- generate a name for temporary file.
- if the argumant is null , tmpnam stores the file in a static variable and returns a pointer to it.
	char *filename;
	filename = tempnam(NULL);
	or
	char filename[LEN];
	tempnam(filename);
	 - It is adivsable for you to use L_tmpnam as the length of the array to hold your name 
	 after calling tmpnam since it is well crafted and it saves on memory

	 TMP_MAX - is a macro that defines the maximum number of times you can call tmpnam function in your program .


