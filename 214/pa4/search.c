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


  buildWordList(argv[1]);

  return 0;

  while (1 == 1)
  {
    printf("Search> ");
    scanf("%s", searchInput);

    if(strncmp(searchInput, "q", 1) == 0)
    {
      return 0;
    }

    searchOption = strtok(inputLine, " ");

    /*if(strncmp(searchOption[1], "sa", 2) == 0)*/
    /*{*/
      /*puts("sa");*/
    /*}*/
    /*else if(strncmp(searchOption[1], "so", 2) == 0)*/
    /*{*/
      /*puts("so");*/
    /*}*/
    /*else*/
    /*{*/
      /*printf("Invalid search input, please try again. \n");*/
    /*}*/

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
    if (strstr(line, "<files>")){
      inFile = 1;
    }
    else if (strstr(line, "</files>")){
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
  while (fgets(line, 2048, file ) != NULL) {
    if (strstr(line, "<files>") != NULL){
      inFile = 1;
      continue;
    }
    else if (strstr(line, "</files>") != NULL){
      inFile = 0;
      break;
    }
    else if (inFile == 0) {
      continue;
    }
    else {
        fileCount--;
        fileList[fileCount] = malloc(strlen(line));
        strncpy(fileList[fileCount], line+2, strlen(line) - 3);
    }
  }
  fclose(file);
  return fileList;
}


struct wordnode* buildWordList(const char* indexFile) {
  struct wordnode* wordList = NULL;
  struct wordnode* curr = NULL;

  char* line;
  char** fileList = buildFiles(indexFile);
  char* word = NULL;
  FILE *file = fopen (indexFile, "r");
  int inList = 0;

  if (file != NULL){
    line = malloc(2048);
  }

  while (fgets(line, 2048, file ) != NULL){
    if (strstr(line, "<list>")){
      inList = 1;
      word = malloc(strlen(line+6));
      strncpy(word, line+7, strlen(line+7) - 1);
      curr = malloc(sizeof(struct wordnode) + 1);
      curr->word = word;
      curr->files = NULL;
      curr->next = wordList;

      if (wordList == NULL){
        wordList = (curr);
      }
    }
    else if (strstr(line, "</list>")){
      inList = 0;
      continue;
    }
    else if (inList){
      struct filenode* currFile = malloc(sizeof(struct filenode) + 1);

      int colonSpot = 0;
      while (colonSpot < strlen(line) && line[colonSpot] != ':'){
        colonSpot++;
      }
      line[colonSpot] = '\0';
      strcpy(line, line+1);

      currFile->fileName = malloc(colonSpot + 1);
      strcpy(currFile->fileName, fileList[atoi(line)]);
      currFile->next = curr->files;
      curr->files = currFile;
    }
  }
  fclose(file);

  return wordList;
}
