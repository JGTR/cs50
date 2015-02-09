#include <cs50.h>
#include <stdio.h>
#include <math.h>

int longlength(long long n);
int sumrelevantdigits(int digits, long long n);
int getdigit(long long n);

int main(void)
{
  printf("Number: ");
  long long num;
  num = GetLongLong();
  int digitlength = longlength(num);
  int relevantsum = sumrelevantdigits(digitlength, num);
  printf("%i \n", relevantsum);
}

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

int sumrelevantdigits(int d, long long longnum)
{
  int sum = 0;
  long long store = longnum;
  int digit;

  for(int count = 0; count < d ; count++)
  {
    digit = getdigit(store);
    // printf ("digit = %i\n", digit);
    if (count % 2 == 0)
    {
      sum = sum + digit;
    }
    else {
      sum = sum + digit * 2;
    }
    store = store / 10;
    // printf("store = %llu\n", store);
  }
  return sum;
}

int getdigit(long long n)
{
  while(n > 10)
  {
    n = n % 10;
  }
  return n;
}