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
  		return binsearch(value, values, lower, upper);
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
	int try = (upper + lower) / 2; // Sets the index of comparison between the two anchor indexes
	int tryvalue = values[try]; // Gets the value at the index of comparison
  bool answer = false; // Initializes the answer boolean to be false, pending change to true

  // We make sure that the bounds make sense for the operation
	if ( lower <= upper )
	{
		if (tryvalue == value)
		{
			answer = true; // If we find the value, we set answer to true
		}
		else if (tryvalue < value) // go right branch
		{
			answer = binsearch(value, values, try + 1, upper); // We need to avoid a perpetual loop by moving the average further right with the +1
		}
		else if ( tryvalue > value) // go left branch
    {
			answer = binsearch(value, values, lower, try - 1); // We need to avoid a perpetual loop by moving the average further left with the -1
		}
	}
  return answer;
}
