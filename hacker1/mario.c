#include <cs50.h>
#include <stdio.h>

int renderoutcomes(int height);
int printfoutcomes(int height);

int main(void)
{
	printf("Height: ");
	int height = GetInt();
	renderoutcomes(height);
	printf("The height your provided is : %i\n", height);

}

int renderoutcomes(int height)
{
	for(int x = 0; x < height; x++)
	{
		printf("%*s", height-x, " ");
		printf("%*s\n",x, "#");
	}

	return 0;
}