#include <ctype.h>
#include <stdio.h>

/* There are two categories of functions in it
   1. character testing functions
   2. character case mapping functions

   Advantages of using it
   > speed ( macro defiantions)
   > portability
   > they obey locale when used (the bigger trade
   (The functions available all take in ints and return ints)

   CHARACTER TESTING FUNCTIONs
   > isalnum() -> alphanumeric [a-zA-z0-9]
   > isalpha() -> alpabetic [a-zA-z]
   > iscntrl() -> control character(\n,\e)
   > isdigit() ->  decimal digit
   > isgraph()-> printing charactre orther than a space
   > islower() -> [a-z]
   > isprint() -> printing character (includig space)
   > ispunct() -> is a punctuation ( all printing characters expect space and alphanumeric )
   > isspace() ->  whitespace character { space , \f, \n, \r, \t, \v }
   > isupper() -> [A-Z]
   > isxdigit() -> a hexadecimal digit

   [NOTE]
   -> worth noting that control characters in c start at \x00 to \x1f plus \x7f.
 */

int main(void)
{
/* A grate code is comming */
    return 0;
}
