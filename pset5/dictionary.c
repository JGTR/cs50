/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "dictionary.h"

#define NUMOFLETTERS 27
#define APOSTROPHE "\'"

typedef struct node
  {
    bool word;
    struct node* children[NUMOFLETTERS];
  }
node;

struct node* createnode(void)
{
  return malloc(sizeof(struct node));
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
  char line[sizeof(char)*LENGTH];
  struct node *root = createnode();

  FILE* dfile = fopen(dictionary, "r");

  if (dfile == NULL){
    return false;
  }

  int count = 0;

  while(fgets(line, sizeof(line), dfile) != NULL)
  {

    node *trie = root;
    int size = strlen(line);
    node *alt = createnode();

    strtok(line, "\n");
    // printf("%s\n", line);

    for(int x = 0; x < size; x++)
    {
      if (strcmp(APOSTROPHE, &line[x]) == 0)
      {
        if(trie -> children[26] == NULL)
        {
          trie -> children[26] = alt;
          trie = alt;
        }
      }
      else if (line[x] == '\0')
      {
        trie -> word = true;
        count++;
      }
      else
      {
        if (trie -> children[(97 - line[x])] == NULL)
        {
          trie -> children[(97- line[x])] = alt;
          trie = alt;
        }
          
        // printf("%d\n", (line[x] - 97) );
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
