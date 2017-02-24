/*
 * task template
 * http://ideone.com/Drsm7h
 */
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	char name[6];
	printf("Enter your name: ");
	gets(name);
	printf("Hello, %s!\n", name);
	return 0;
}
