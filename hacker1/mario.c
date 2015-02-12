// Jordan Trevino

// I am using 2 tabs to indent out of preference. 

#include <cs50.h>
#include <stdio.h>

int render(int height);
int printline(int spaces, int hashes);
int printreverse(int spaces, int hashes);


// Controls the flow of the program.
int main(void)
{
  int height = -1;
  while( height < 0 || height > 24)
  {
    printf("Enter a non-negative integer < 24: ");
    int height = GetInt();
    if (height >= 0 && height < 24)
    {
      render(height);
      break;
    }
  }
}

// Calls the print functions
int render(int height)
{
  for(int x = 1; x <= height; x++)
  {
    printline(height-x, x);
    printf("  ");
    printreverse(height-x, x);
    printf("\n");
  }

  return 0;
}

// Prints the left hand pyramid
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


// Prints the right-hand pyramid
int printreverse(int units, int hashes)
{
  for(int y = 0; y < hashes; y++)
  {
    printf("#");
  }
  return 0;
}