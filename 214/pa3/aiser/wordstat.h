#include <stdio.h>
#include <stdlib.h>

typedef struct dictionaryWord{
  char word[256];
  struct dictionaryWord *next;
}dictionaryWord;

typedef struct normalWord{
  char word[256];
  int count;
  int inDict;
  struct normalWord *next;
}normalWord;

  void printHelp();
int numberLines (char *nameOfFile);
int numberWords (char *nameOfFile);
int palindrome  (char *nameOfFile);
