#include "search.h"

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("Invalid input. Please enter the name of an index.\n");
    return 1;
  }

  buildWordList(argv[1]);
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
  char** fileList = malloc(sizeof(char*) * (countFiles(indexFile) + 1));
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
        fileList[counter] = malloc(strlen(line) - 2);
        strcpy(fileList[counter], line+2);
        fileCount--;
    }
  }
}


wordNode* buildWordList(const char* indexFile) {
  wordNode* wordList = malloc(sizeof(fileNode*) + 1);
  wordNode* curr = wordList;

  char* line;
  char* word = "";
  FILE *file = fopen (indexFile, "r");
  int inList = 0;

  if (file != NULL){
    line = malloc(2048); /*Buffer where line is stored*/
  }

  while (fgets(line, 2048, file ) != NULL){
    if (strstr(line, "<list>")){
      inList = 1;
      strcpy(word, line+7);
      printf("Word is: %s\n", word);
    }
    if (strstr(line, "</list>")){
      inList = 0;
      continue;
    }

  }
  return NULL;
  /*return wordList;*/
}
