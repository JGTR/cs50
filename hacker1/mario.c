#include <cs50.h>
#include <stdio.h>

int renderoutcomes(int height);
int printline(int spaces, int hashes);
int printreverseline(int spaces, int hashes);

int main(void)
{
	printf("Height: ");
	int height = GetInt();
	renderoutcomes(height);
}

int renderoutcomes(int height)
{
	for(int x = 1; x <= height; x++)
	{
		printline(height-x, x);
		printf("  ");
		printreverseline(height-x, x);
		printf("\n");
	}

	return 0;
}


int printline(int units, int hashes)
{
	for(int x = 0; x < units; x++)
	{
		printf(" ");
	}
	for(int y = 0; y < hashes; y++)
	{
		printf("#");
	}
	return 0;
}

int printreverseline(int units, int hashes)
{
	for(int y = 0; y < hashes; y++)
	{
		printf("#");
	}
	for(int x = 0; x < units; x++)
	{
		printf(" ");
	}
	return 0;

}
