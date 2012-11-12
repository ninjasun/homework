#include "search.h"
#include <stdio.h>

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("Invalid input. Please enter the name of an index.\n");
    return 1;
  }
  
  char* searchInput = malloc(1024);
  
  char* inputLine;
  char* searchOption;

  char** fileList = 
  
  buildWordList(argv[1]);
    
  while (1 == 1)
  {
    printf("Search> ");
    scanf("%s", searchInput);

    if(strncmp(searchInput, "q", 1) == 0)
    {
      return 0;
    }

    searchOption = strtok(inputLine, " ");

    if(strncmp(searchOption[1], "sa", 2) == 0)
    {

    }
    else if(strncmp(searchOption[1], "sa", 2) == 0)
    {

    }
    else
    {
      printf("Invalid search input, please try again. \n");
    }
      
  }

  return 0;
}

int countFiles(const char* indexFile){
  char* line;
  FILE *file = fopen (indexFile, "r");
  int count = 0;
  int inFile = 0;

  if (file != NULL) {
    line = malloc(1024);
  }
  while (fgets(line, 1024, file ) != NULL) {
    if (strstr(line, "<file>")){
      inFile = 1;
    }
    else if (strstr(line, "</file>")){
        break;
    }
    else if (inFile) {
      count += 1;
    }

  }
  return count;
}

char** buildFiles(const char* indexFile){
  int fileCount = countFiles(indexFile);
  char** fileList = malloc(sizeof(char*) * fileCount + 1);
  char* line;
  FILE *file = fopen (indexFile, "r");
  int inFile = 0;

  if (file != NULL) {
    line = malloc(2048); //Buffer where line is stored
  }
  while (fgets(line, 2048, file ) != NULL) /* read a line */
  {
    if (strstr(line, "<file>")){
      inFile = 1;
      continue;
    }
    else if (strstr(line, "</file>")){
      inFile = 0;
      break;
    }
    else if (! inFile) {
      continue;
    }
    else {
        fileList[fileCount] = malloc(strlen(line) - 2);
        strcpy(fileList[fileCount], line+2);
        fileCount--;
    }
  }
  return fileList;
}


wordNode* buildWordList(const char* indexFile) {
  /*wordNode* wordList = malloc(sizeof(fileNode*) + 1);*/
  /*wordNode* curr = wordList;*/

  char* line;
  char* word = "";
  FILE *file = fopen (indexFile, "r");
  int inList = 0;

  if (file != NULL){
    line = malloc(2048); /*Buffer where line is stored*/
  }

  while (fgets(line, 2048, file ) != NULL){
    if (strstr(line, "<list>")){
      word = malloc(strlen(line+6));
      inList = 1;
      strncpy(word, line+7, strlen(line+7) - 1);
      printf("Word: %s\n", word);
    }
    /*else if (strstr(line, "</list>")){*/
      /*inList = 0;*/
      /*continue;*/
    /*}*/

  }
  fclose(file);

  return NULL;
  /*return wordList;*/
}
