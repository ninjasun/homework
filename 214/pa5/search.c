#include "search.h"

int main(int argc, char **argv) {
  if (argc < 2 || argc > 6) {
    printf("Invalid number of arguments");
    return 1;
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

void freedom(struct wordnode* target) {
  struct filenode* shackled = target->files;
  while (shackled != NULL) {
    struct filenode* tmpF = shackled;
    shackled = shackled->next;
    free(tmpF->fileName);
    free(tmpF);
  }

  free(target->word);
  free(target);
}

char** buildFiles(const char* indexFile, unsigned int size){
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
        fileList[fileCount] = malloc(strlen(line) + 1);
        printf("%s\n",line);
        strncpy(fileList[fileCount], line+2, strlen(line) - 2);
        printf("%s\n",fileList[fileCount]);
    }
  }
  fclose(file);
  return fileList;
}

void andSearch (char* line) {
}

void orSearch(char* line){
}

struct wordnode*  getFileList(char* word) {
  return NULL;
}

struct wordnode* buildWordList(const char* indexFile) {
  return NULL;
}
