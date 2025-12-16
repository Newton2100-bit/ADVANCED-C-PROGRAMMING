extern int printf(char *, ...);

int main(void){
	/* exploring the mechanics of the layout of bits */
	int i = 5;
	float f = i;
	printf("[%i' ] ' %f \n",sizeof(f), f);

	float f2 = 67.54;
	int i2 = f2;
	printf("\n\n[%i] %f becomes [%i] %i\n",sizeof(f2), f2,sizeof(i2), i2);

	return 0;
}
