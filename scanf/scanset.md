The [ specifier is a more complex version of the s specifier
Though [ is more flexible
Format
	%{*}{widht}(hlL}[set]
	%{*}{widht}(hlL}[^set]
If ']' i spart of the scanset then it must come first in the set
[%][*] [width] [h,l,L] [specifier]

Conversion specifiers
d -  matches a decimal
i - matches an integer but it makes a decision o fthe base based on the appearance
o - will inteparate the value as an octal
u - the value is assumed to be unsigned
x,X - matches a hexadecimal integer (assumed to be a poiner to unsigned int)
e,E,f,g,G - matches a float
s - matches a sequece of non-white space characeters and adds a null character at the end.
[ - matches a non-empty sequence of characters from a scanset and adds a null character at the end.
c - matches n characters (n is defined by the width you give) not null is added here.
p - matches a pointer value in the form that printf might have written it
n - the corresponding argument must point to a variable of type int,(short int of %hn and long int if %ln

Worth noting
When * is used the matched characters aren't counted aand they arent stored in a variable.

