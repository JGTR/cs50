/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "dictionary.h"

// Global variable to count number of words
int count = 0;
struct node* root;


bool releaseNode(node* trie)
{

  // Start with the left-most non-null node and probe as deeply as possible.
  for(int x = 0; x < NUMOFLETTERS; x++)
  {
    if (trie -> children[x] != NULL)
    {
    releaseNode(trie -> children[x]);  
    }
  }

  free(trie);
  return true;
}

struct node* createnode(void)
{
  struct node* r = malloc(sizeof(struct node));
  r -> word = false;
  memset(r, 0, sizeof(struct node));
  return r;
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
  // Get size of word
  int size = strlen(word);

  char tocheck[size];
  memset(tocheck, '\0', sizeof(tocheck));
  strcpy(tocheck, word);

  // Removes line break and space characters from the line
  strtok(tocheck, "\n");
  strtok(tocheck, "\t");

  // Ensure word is all lower case
  for (int x = 0; x < size; x++)
    tocheck[x] = tolower(tocheck[x]);

  // Retrieve the trie
  node* trie = root;

  // Go through char by char and compare to node
  for(int i = 0, address = 0; i < size; i++)
  {
    // Determine position of char
    if (tocheck[i] != '\0' && tocheck[i] != 39)
    {
      address = (tocheck[i] - 97);
    }
    else if(tocheck[i] == 39 )
    {
      address = NUMOFLETTERS - 1;
    }

    // Traverse through rest of nodes if they are not null
    if (0 != (trie -> children[address]) )
    {
      trie = (trie -> children[address]);
    }
    else if ((trie -> children[address]) == 0)
    {
      return false;
    }

    // If the word is set to true, we have our answer. But we can only check this if the length of tocheck is reached
    if ( i == size-1 && (trie -> word) == true)
    {
      return true;
    }
  }
  return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
  // Create array of chars to hold array
  char line[sizeof(char)*LENGTH];
  // Creat root node
  root = createnode();
  // Create file pointer and open dictionary file
  FILE* dfile = fopen(dictionary, "r");
  // Error out if the file cannot be opend
  if (dfile == NULL){
    return false;
  }

  while(fgets(line, LENGTH, dfile) != NULL)
  {
    // Create trie node and set it to root
    struct node* trie = root;

    // Removes line break and space characters from the line
    strtok(line, "\n");
    strtok(line, "\t");

    // Determine the size of the line
    int size = strlen(line);

    // Ensure all chars are lower case
    for (int y = 0; y < size; y++)
      line[y] = tolower(line[y]);

    int address = 0;
    // Iterate through every char of the line
    for(int x = 0; x <= size; x++)
    {
      // if(line[x] == 10)
      // {
      //   break;
      // }

      // Ensure that the current char is not a terminator or apostrophe
      if (line[x] != '\0' && line[x] != 39)
      {
        // Calculate the position of the char in the array of letters from a to z
        address = (line[x] - 97);
      }
      // Special logic for apostrophes
      else if (39 == line[x])
      {
        address = NUMOFLETTERS - 1;
      }

      // Check if the node does not exist.
      if (trie -> children[address] == NULL)
      {
        // Create new node
        trie -> children[address] = createnode();
      }

      // Add word
      if (x == size && x > 0)
      {
      // Set the word to true
      trie -> word = true;
      // Increase the count of words
      count++;
      // Exit the loop
      break;
      }

      // Traverse to the next node
      trie = trie -> children[address];
    } 
  }
  fclose(dfile);
  return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
  return count;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{

  if (releaseNode(root))
  {
    return true;
  }
  else
  {
    return false;
  }
}
