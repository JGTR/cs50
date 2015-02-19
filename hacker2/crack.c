// Jordan Trevino

// Compilation command : clang -o crack crack.c -lcrypt

#define _XOPEN_SOURCE
#include <stdio.h>
#include <string.h>
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
	tries = fopen(PASSWORDS, "r"); // Store passwords in file
	int counter = 1; // keep count of each try

	if (tries == NULL){
		printf("There was an error loading the file.");
	}

	// Run through the entire file
	while (fgets(try, 50, tries) != NULL)
	{
		strtok(try, "\n");
		// Stop the program once a match is reached
		if (ispassword(try, argv[1]))
		{
			printf("%s is the right password. \n", try);
			break;
		}
		if (counter % 100 == 0)
		{
			printf("%i tries...\n", counter);
		}
		counter++;
	}
	return 0;
}

bool ispassword(char *try, char *pass)
{
	char charsforsalt[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789./";
	char salttotry[2];
	char *crypted;

	for(int x = 0; x < 64; x++)
	{
		for (int y = 0; y < 64; y++)
		{
			salttotry[0] = charsforsalt[x];
			salttotry[1] = charsforsalt[y];

			crypted = crypt(pass, salttotry);
			if (strcmp(crypted, try) == 0)
			{
				return true;
			}
		}
	}
	return false;
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