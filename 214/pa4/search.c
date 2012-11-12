#include "search.h"

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("Invalid input. Please enter the name of an index.\n");
    return 1;
  }
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
    else if (inFile) {
      count += 1;
    }
  }
  return count;
}

char** buildFiles(const char* indexFile){
  int counter = 0;
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
        counter++;
    }
  }

}