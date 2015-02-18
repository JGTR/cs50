// Jordan Trevino

#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

// I am using 2 tabs to indent out of preference. 

// Controls the main flow. 

int main(void)
{
  // The boolean tells the program whether to print this char or not, depending on whether it follows a space.
  bool exec = true;
	string name = GetString();

  // Checks that input is real and not an error.
  if (name != NULL)
  {
    for ( int x = 0; x < strlen(name) ; x++)
    {
      // Assigns the relevant char to the variable consider .
      char consider = name[x];
      // Checks that the program is primed to print the char and that the char is not a space.
      if ( consider != ' ' && exec == true)
      {
        printf("%c", toupper(name[x]));
        exec = false;
      }
      // Branch for when the char is a space.
      else if (consider == ' ')
      {
        // We prepare the program to pick out the first letter after a space.
        exec = true;
      }
    }
    printf("\n");
  }
}