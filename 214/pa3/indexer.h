#ifndef INDEXER_H
#define INDEXER_H

/* Globals Variables */
char* delims;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <ftw.h>
#include <ctype.h>


/* Structs */
struct fileNode {
  char* fileName;
  int count;
  struct fileNode* next;
};

struct wordNode{
  char* word;
  struct fileNode* files;
  struct wordNode* next;
};

typedef struct wordNode wordNode;
typedef struct fileNode fileNode;

/* Global Structs */
struct wordNode* wordList;

/* Functions */
int fileCallback(const char* pathname, const struct stat* ptr, int flag);
char* getDelims();
int addCount(char* path, char* word);
void printData(char* outputFile);
void gundamFreedom();


#endif
