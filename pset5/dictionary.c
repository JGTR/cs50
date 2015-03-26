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

#define NUMOFLETTERS 27

// Global variable to count number of words
int count = 0;

typedef struct node
  {
    bool word;
    struct node* children[NUMOFLETTERS];
  }
node;

struct node* createnode(void)
{
  struct node* root = malloc(sizeof(struct node));
  root -> word = false;
  memset(root -> children, 0, sizeof(struct node));
  return root;
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
  // TODO
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
  struct node* root = createnode();

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

    // Removes line break characters from the line
    strtok(line, "\n");

    // Determine the size of the line
    int size = strlen(line);

    // Ensure all chars are lower case
    for (int x = 0; x < size; x++)
            line[x] = tolower(line[x]);

    // Iterate through every char of the line
    for(int x = 0; x < size; x++)
    {
      // printf("%c\n", line[x]);

      // Special logic for apostrophes
      if (39 == line[x])
      {
        // Check if the node does not exist.
        if (trie -> children[NUMOFLETTERS - 1] == 0)
        {
          // Create new node
          trie -> children[NUMOFLETTERS - 1] = createnode();
        }
        // Traverse to the next node
        trie = trie -> children[NUMOFLETTERS - 1];
      }

      // Ensure that the current char is not a terminator
      else if (line[x] != '\0')
      {
        // Calculate the position of the char in the array of letters from a to z
        int address = (line[x] - 97);
        // Check if the node does not exist
        if (trie -> children[address] == 0)
        {
          // Create the new node at the right element in the children array
          trie -> children[address] = createnode();
        }
        // Traverse to the next node
        trie = trie -> children[address];
        // printf("%d\n", (line[x] - 97) );
      }

      // If the next char is a terminator, we know we have our word
      if (line[x+1] == '\0')
      {
        // Set the word to true
        trie -> word = true;
        // Increase the count of words
        count++;
        // Exit the loop
        break;
      }
    } 
  }

  printf("%d\n", count);
  fclose(dfile);
  return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
  // TODO
  return 0;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
  // TODO
  return false;
}
