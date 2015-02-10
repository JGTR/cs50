#include <cs50.h>
#include <stdio.h>
#include <math.h>

// The following is indented 2 spaces only out of personal preference.

int longlength(long long n);
int sumdigits(int digits, long long n);
int getdigit(long long n);
bool checkfour(long long n);

int main(void)
{
  printf("Number: ");
  long long num;
  num = GetLongLong();
  int digitlength = longlength(num);
  int relevantsum = sumdigits(digitlength, num);
  // printf("Sum = %i \n", relevantsum);
  bool startwfour = checkfour(num);
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
  // printf("count: %i \n", count);
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
    digit = getdigit(store);
    // printf ("digit = %i\n", digit);
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
    // printf("store = %llu\n", store);
  }

  return sum;
}

int getdigit(long long n)
{
  return n % 10;
}

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