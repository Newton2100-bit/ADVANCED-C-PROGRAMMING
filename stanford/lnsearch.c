#include <stdio.h>
#include <string.h>
/* There is these bullt in in c
   bsearch(void *key, void *base, int n, int elemsize, int (*cmp)(void *, void *));
 */


void *lsearch(void *key,void *base, int n, int elemsize, int (*cmpfn)(void *, void *)){
    for (int i = 0; i < n; i++){
	void *elemadrr = (char*)base + i * elemsize;
	if(cmpfn(key, elemadrr) == 0)
	    return elemadrr;
    }	
    return NULL;
}

int intCmp(void *vp1, void *vp2){
    int *ip1 = vp1;
    int *ip2 = vp2;

    return *ip1 - *ip2;
}


int StrCmp(void *vp1, void *vp2){
    char *s1 = *(char **)vp1;
    char *s2 = *(char **)vp2;
    return strcmp(s1, s2);
}

int main(void)
{
    char *notes[] = {"Ab", "F#", "B", "6b", "D"};
    char *keynote = "B";

    char **found = lsearch(&keynote, notes,5, sizeof(char *), StrCmp);
    if(found == NULL)
	printf("String \" %s \" wasn't found.\n", keynote);
    else{
	printf("Found at position %p.\n", found);
	printf("AS int => %i,\nAS hex we have %x\n", *(found), *(found));

	/* SOME EXPERIMENTALS */
	//	printf("AT found we a char ** which we can say it is === %s\n",found);
	printf("One step ahead %p => %s.\n",*(found), *found);
    }
    return 0;
}


