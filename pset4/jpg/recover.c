// Jordan Trevino

/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */

 #include <stdio.h>
 #include <stdint.h>
 #include	"bmp.h"
 #include <stdlib.h>
 #include <stdbool.h>


int main(int argc, char* argv[])
{
    // TODO

	bool reading_jpeg = true;


	if (argc != 2)
	{
		printf("Usage: ./recover file\n");
	}

	// open file
	FILE* file = fopen(argv[1], "r");
	if (file == NULL){
		printf("Wrong file\n");
		return 1;
	}

	// buffer that is 512 bytes
	unsigned char buffer[512];

	// Check through file in some sort of loop

	int filenum = 0;

		// Find a jpeg and initialize the recovery
		reading_jpeg = fread(buffer, sizeof(BYTE), 512, file);
		while(reading_jpeg)
		{
		// Create an output file and write to it

			FILE *output = ;

		// Exit the recovery once a new file is found

		// Terminate the program at EOF.
			reading_jpeg = fread(buffer, sizeof(BYTE), 512, file);
			filenum++;
		}


}
