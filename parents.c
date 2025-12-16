#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#define NAME "Newton Irungu Mwaura"
/* These is a comment */

pid_t parent1, num1, num2, child1, child2;
void fun1(void), fun2(void), funchild1(void), funchild2(void);
int main(void){
	printf("we are inside the original parent\n");

	char *name = strdup(NAME);

	parent1 = getpid();
	num1 = fork();

	if(getpid() == num1){
		fun1();
		child1 =  fork();
		funchild1();
		sleep(5);
	}
	if(getpid() == parent1){
		num2 = fork();
	}

	if(getpid() == num2){
		fun2();
		child2 = fork();
		funchild2();
		sleep(10);
	}
	if(getpid() == parent1){
		printf("we want to exit the parent and see the behaviours of our pids.\n");
		exit(0);
	} 

	fun1();
	fun2();
	funchild1();
	funchild2();
}

void fun1(void){
	printf("We have the PID of the first child as %d.\n", getpid());
}

void fun2(void){
	printf("We  have the second child PID as %d.\n", getpid());
}

void funchild1(void){
	printf("We are child one and our PID is %d.\n", getpid());
}

void funchild2(void){
	printf("We have our child two with PID as %d.\n", getpid());
}
