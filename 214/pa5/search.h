#ifndef SEARCH_H
#define SEARCH_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


struct filenode {
  char* fileName;
  struct filenode* next;
};

struct wordnode {
  char* word;
  struct wordnode* next;
  struct filenode* files;
  unsigned int size;
};


unsigned int cacheSize = 0;
struct wordnode* cache = NULL;


char** buildFiles(const char*, unsigned int);
struct wordnode* buildWordList(const char*);
struct wordnode* getFileList(char*);
struct wordnode* checkCache(char*);
void andSearch(char*);
void orSearch(char*);
void freedom(struct wordnode*);


#endif
