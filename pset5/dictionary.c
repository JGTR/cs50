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
struct node* root = NULL;

typedef struct node
  {
    bool word;
    struct node* children[NUMOFLETTERS];
  }
node;

struct node* createnode(void)
{
  struct node* r = malloc(sizeof(struct node));
  r -> word = false;
  // memset(r -> children, 0, sizeof(struct node));
  return r;
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
  // Get size of word
  int size = strlen(word);
  printf("%d\n", size);

  char tocheck[size];
  memset(tocheck, '\0', sizeof(tocheck));
  strcpy(tocheck, word);

  // Ensure word is all lower case
  for (int x = 0; x < size; x++)
            tocheck[x] = tolower(tocheck[x]);

  // printf("%s\n", tocheck);

  struct node* trie = root;

  // Go through char by char and compare to node
  for(int i = 0, address = 0; i < size; i++)
  {
    // Determine position of char
    if(tocheck[i] == 39)
    {
      address = NUMOFLETTERS - 1;
    }
    else
    {
      address = (tocheck[i] - 97);
    }
  

    // Traverse trie

      // If the word is set to true, we have our answer
    if (trie -> word)
    {
      return true;
    }
    // Check h
    else if ((trie -> children[i]) != 0)
    {
      printf("Not null: %c\n", tocheck[i]);
      trie = trie -> children[i];
    }
    else if ((trie -> children[1]) == 0)
    {
      printf("Null: %c\n", tocheck[i]);
      return false;
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
        if (trie -> children[NUMOFLETTERS - 1] == NULL)
        {
          // Create new node
          trie -> children[NUMOFLETTERS - 1] = createnode();
          // printf("New apostrophe node. \n");
          // printf("%d\n", (int)&trie);
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
        if (trie -> children[address] == NULL)
        {
          // Create the new node at the right element in the children array
          trie -> children[address] = createnode();
          // printf("New node for address: %d. \n", address);
          // printf("%p\n", (void*) trie->children[address]);
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
      }
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
  // TODO
  return false;
}
