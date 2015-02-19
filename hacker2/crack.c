// Jordan Trevino

// Compilation command : clang -o crack crack.c -lcrypt

#include <stdio.h>
#include <string.h>
#define _XOPEN_SOURCE
#include <unistd.h>

// Dictionary file to crack passwords
#define PASSWORDS "/usr/share/dict/words"

char getword();

int main(int argc, char *argv[])
{
	FILE *tries; // file pointer for tries
	char try[50]; // store word to try

	tries = fopen(PASSWORDS, "r");
	if (tries == NULL){
		printf("There was an error loading the file.");
	}


	if (fgets(try, 50, tries) != NULL)
	{
		puts(try);	
	}
	
	return 0;
}


int tryword()
{
	return 1;
}