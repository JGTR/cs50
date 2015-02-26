/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
 	int lower = 0;
 	int upper = n-1; // Anchor index for algorithm

    if (value < 1) 
    {
    	return false;
    }
    else 
    {
		if (binsearch(value, values, lower, upper))
		{
			return true;
		}
		else
		{
			return false;
		}
    }
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // Selection sort
    
    int store; // Initializes variable to store minimum value

    // First loop focuses on the i-th int in the set
	for(int i = 0; i < n - 1; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			// The second loop will swap out the value of the value at index i if an int at values[j] is found that is smaller
			if (values[i] > values[j])
			{
				store = values[i];
				values[i] = values[j];
				values[j] = store;
			}
		}
	}

    return;
}


bool binsearch(int value, int values[], int lower, int upper)
{
	printf("lower: %i and upper: %i\n", lower, upper);
	if (lower > upper)
	{
		return false;
	}
	else if ( lower == upper)
	{
		if(values[upper] == value)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else if ( lower < upper )
	{
		int try = (upper + lower) / 2;
		printf("try: %i\n", try);
		int tryvalue = values[try];

		if (tryvalue == value)
		{
			return true;
		}
		// go right branch
		else if (tryvalue < value) 
		{
			binsearch(value, values, try + 1, upper);
		}
		// go left branch
		else if ( tryvalue > value) {
			binsearch(value, values, lower, try - 1);
		}
	}
	return false;
}
