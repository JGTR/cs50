// Jordan Trevino

#include <cs50.h>
#include <stdio.h>
#include <math.h>

// I am using 2 tabs to indent out of preference. 

int longlength(long long n);
int sumdigits(int digits, long long n);
int getdigit(long long n);
bool checkfour(long long n);

// Controls the main flow. 

int main(void)
{
  printf("Number: ");
  long long num;
  num = GetLongLong();
  
  // Get inputs necessary for program. 

  int digitlength = longlength(num);
  int relevantsum = sumdigits(digitlength, num);
  bool startwfour = checkfour(num);

  // Logic to assess whether invalid or the credit card type.

  if (relevantsum % 10 == 0)
  {
    switch (digitlength)
    {
      case 13:
        printf("VISA\n");
        break;
      case 16:
        if (startwfour)
        {
          printf("VISA\n");
          break;
        }
        else 
        {
          printf("MASTERCARD\n");
          break;
        }
      case 15:
        printf("AMEX\n");
        break;
    }
  }
  else
  {
    printf("INVALID\n");
  }
  
}

// Determines the length of the number.
int longlength(long long n)
{
  int count = 0;
  while (n != 0)
  {
      n /= 10 ;
      ++count;
  }
  return count;
}

// Sums the digits in the way they need to be summed.
int sumdigits(int length, long long longnum)
{
  int sum = 0;
  long long store = longnum;
  int digit;

  for(int count = 0; count <= length ; count++)
  {
    // Splits logic based on whether even or odd to perform different operations.
    digit = getdigit(store);
    if (count % 2 == 0)
    {
      sum = sum + digit;
    }
    else 
    {
      int counter = 0;
      while(digit > 0)
      {
        if (counter == 0) 
        {
          digit = digit * 2;
        }
        sum = sum + getdigit(digit);
        digit = digit / 10;
        counter++;
      }
    }
    store = store / 10;
  }

  return sum;
}

// Gets the units digit from any number
int getdigit(long long n)
{
  return n % 10;
}

// Checks to see if the card starts with 4
bool checkfour(long long n)
{
  int x;
  while(n > 0)
  {
    x = n % 10;
    n = n / 10;
  }
  return x == 4;
}