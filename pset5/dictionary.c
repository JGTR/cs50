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

#define LINELENGTH 50

#define APOSTROPHE "\'"

typedef struct node
  {
    bool word;
    struct node* children[NUMOFLETTERS];
  }
node;

struct node* createnode(char newletter)
{
  struct node* root = malloc(sizeof(struct node));

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
  // char *letters[sizeof(char)*NUMOFLETTERS] = {"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z","\'"};
  char line[sizeof(char)*LINELENGTH];

  struct node *root = createnode(0);
  // struct node *trav;

  FILE *dfile;
  dfile = fopen(dictionary, "r");

  while(fgets(line, 40, dfile) != NULL)
  {
    node *trie = root;

    int size = strlen(line);

    node *alt = createnode(0);

    strtok(line, "\n");
    printf("%s", line);

    for(int x = 0; x < size; x++)
    {
      if (strcmp(APOSTROPHE, &line[x]) == 0)
      {
        trie -> children[26] = alt;
      }
      else
      {
        trie -> children[25 - (97 - line[x])] = alt;
      }
      trie = alt;
    }
  }


  return true;


		// if (dfile != NULL)
		// {
		// 	return true;
		// }
		// else
		// {
		// 	return false;
		// }   
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
