// Jordan Trevino

// Compilation command : clang -o crack crack.c -lcrypt

#define _XOPEN_SOURCE
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <cs50.h>

// Dictionary file to crack passwords. For testing: #define PASSWORDS "passtest.txt"
# define PASSWORDS "/usr/share/dict/words"

// Exclude a few of the tries if they are too long or have invalid chars.
bool testvalidity(char *try)
{
	if (strlen(try) <= 8 && strchr(try, '\'') == NULL)
	{
		return true;
	}
	return false;
}

// Define function that can determine if the password matches the cracked try.
bool ispassword(char *try, char *pass)
{
	char charsforsalt[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789./"; 
	char salttotry[2];
	char *crypted;

	// Loop through all possible chars for the two characters of the salt.
	for(int x = 0; x < 64; x++)
	{
		for (int y = 0; y < 64; y++)
		{
			salttotry[0] = charsforsalt[x];
			salttotry[1] = charsforsalt[y];

			// Generate a crypted string to compare with the initial usuer input.
			crypted = crypt(try, salttotry);

			// Compare crypted with initial input.
			if (strcmp(crypted, pass) == 0)
			{
				return true;
			}
		}
	}
	return false;
}

int main(int argc, char *argv[])
{

	// file pointer for tries
	FILE *tries;
	// store word to try
	char try[50]; 
	// Store passwords in file -- it did not work if I tried to take the stream directly...
	tries = fopen(PASSWORDS, "r");
	// keep count of each try to give user intermittent updates.
	int counter = 1;
	// Determine length of password try
	bool valid;

	// In case the file cannot be found.
	if (tries == NULL)
	{
		printf("There was an error loading the file.");
	}

	// Run through the entire file line by line
	while (fgets(try, 50, tries) != NULL)
	{
		// Removes line break characters from the password to try
		strtok(try, "\n");
		valid = testvalidity(try);
		// Stop the program once a match is reached
		if (valid && ispassword(try, argv[1]))
		{
			printf("%s is the right password. \n", try);
			break;
		}
		if (counter % 100 == 0)
		{
			printf("%i tries...\n", counter);
			printf("Current try: %s \n", try);
		}
		counter++;
	}
	return 0;
}

// I couldn't figure out pointers well enough to break down the above into smaller functions, which was my goal.