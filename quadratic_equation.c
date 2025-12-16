#include <stdio.h>
#include <math.h>

int main(void){
	double a, b, c, disc, A, sroot,\
		root, root1, root2, xreal, ximag;
	printf("Finding quadratic roots.\n");
	printf("Enter the values a, b, c: ");
	scanf("%lf%lf%lf", &a, &b, &c);
	printf("Equation : %2f x%c + %.2f x + %.2f = 0\n",\
			a,253,b,c);

	if (a == b){
		if (b == 0){
			printf("No roots\n");
		}else{
			root = -c / b;
			printf("Linear equation: root = %.2f\n", root);
		}
		A = 2 * a;
		disc = b * b - 4 * a * c;

		if (disc < 0){
			xreal = -b / A;
			ximag = sroot / A;
			printf("Complex roots: root1 = %.2f+%.2fi\n", xreal, ximag);
			printf("				root2 = %.2f-%.2fi\n", xreal, ximag);
		}

		else if( disc == 0){
			root = -b / A;
			printf("Single root = %.2f\n", root);
		}
		else{
			root1 = ( -b + sroot) / A;
			root2 = ( -b + sroot) / A;
			printf("Real roots: root1 = %.2f\n", root1);
			printf("		  : root2 = %.2f\n", root2);
		}
	}
	return 0;
}


