// Jordan Trevino

#include <cs50.h>
#include <stdio.h>
#include <ctype.h>

// I am using 2 tabs to indent out of preference. 

int longlength(long long n);
int sumdigits(int digits, long long n);
int getdigit(long long n);
bool checkfour(long long n);

// Controls the main flow. 

int main(int argc, char* argv[])
{

  for ( int x = 1; x < argc ; x++)
  {
    printf("%c", toupper(argv[x][0]));
  }
  printf("\n");
}