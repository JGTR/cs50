// Jordan Trevino

// Compilation command : clang -o crack crack.c -lcrypt

#include <stdio.h>
#include <string.h>
#define _XOPEN_SOURCE
#include <unistd.h>
#include <cs50.h>

// Dictionary file to crack passwords
#define PASSWORDS "/usr/share/dict/words"

// char gettry(int counter);

bool ispassword(char *try, char *pass);

int main(int argc, char *argv[])
{

	FILE *tries; // file pointer for tries
	char try[50]; // store word to try

	tries = fopen(PASSWORDS, "r");

	if (tries == NULL){
		printf("There was an error loading the file.");
	}

	// Run through the entire file
	for (int x = 1; x < 100000; x++)
	{
		if (fgets(try, 50, tries) != NULL)
		{
			strtok(try, "\n");
			// Stop the program once a match is reached
			if (ispassword)
			{
				printf("%s is the right password. Found with %i attempts.\n", try, x);
				break;
			}
		}
	}
	return 0;
}

bool ispassword(char *try, char *pass)
{
	return true;
}


// char gettry(int counter)
// {
// 	FILE *tries; // file pointer for tries
// 	char try[50]; // store word to try

// 	tries = fopen(PASSWORDS, "r");

// 	if (tries == NULL){
// 		printf("There was an error loading the file.");
// 	}

// 	if (fgets(try, 50, tries) != NULL)
// 	{
// 		fclose(tries);
// 		return try;
// 	}
// 	else 
// 	{
// 		return NULL;
// 	}

// }