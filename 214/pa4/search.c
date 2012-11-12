#include "search.h"

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

void andSearch (struct wordnode *head, char* line) {
   strncpy(line, line + 2, strlen(line));
   char* token;
   token = strtok(line, " ");
   struct filenode* fileHead = NULL;
   while (token != NULL) {
      struct wordnode* ptr = head;
      while (ptr != NULL) {
         if (strcmp(ptr->word, token) == 0) {
            if (fileHead == NULL) {
               fileHead = malloc(sizeof(struct filenode*) + 1);
               struct filenode* tmpPtr2;
               struct filenode* tmpPtr;
               tmpPtr = ptr->files;
               tmpPtr2 = fileHead;
               while (tmpPtr != NULL) {
                  tmpPtr2->fileName = tmpPtr->fileName;
                  tmpPtr2->next = malloc(sizeof(struct filenode*) + 1);
                  tmpPtr2 = tmpPtr2->next;
               }
            }
            else {
               struct filenode* tmpPtr = fileHead;
               struct filenode* prev = tmpPtr;
               struct filenode* tmpPtr2 = ptr->files;
               int found = 0;
               while (tmpPtr != NULL) {
                  while (tmpPtr2 != NULL) {
                     if (strcmp(tmpPtr->fileName,tmpPtr2->fileName) == 0){
                        found = 1;
                        break;
                     }
                     tmpPtr2 = tmpPtr2->next;
                  }
                  if (found == 0){
                     if (strcmp(prev->fileName,tmpPtr->fileName) == 0){
                        fileHead = fileHead->next;
                        free(prev);
                        tmpPtr = fileHead;
                     }
                     else {
                        prev->next = tmpPtr->next;
                        free(tmpPtr);
                        tmpPtr = prev->next;
                     }
                  }
                  else {
                     prev = tmpPtr;
                     tmpPtr = tmpPtr->next;
                  }
                  found = 0;
               }
            }
         }
      }
      token = strtok(NULL, " ");
   }
   struct filenode* tmp = fileHead;
   while (tmp!= NULL){
      printf("%s\n", tmp->fileName);
   }
}

void orSearch(struct wordnode *head, char* line){
  strncpy(line, line + 2, strlen(line));
  char* token;
  token = strtok(line, " ");
  struct filenode* fileHead = NULL;
  struct filenode* tail = NULL;
  while (token != NULL) {
      struct wordnode* ptr = head;
      while (ptr != NULL) {
         if (strcmp(ptr->word, token) == 0) {
            if (fileHead == NULL) {
               fileHead = malloc(sizeof(struct filenode*) + 1);
               struct filenode* tmpPtr;
               struct filenode* tmpPtr2;
               tmpPtr = ptr->files;
               tmpPtr2 = fileHead;
               while (tmpPtr != NULL) {
                  tmpPtr2->fileName = tmpPtr->fileName;
                  tmpPtr2->next = malloc(sizeof(struct filenode*) + 1);
                  tail = tmpPtr2;
                  tmpPtr2 = tmpPtr2->next;
               }
            }
            else {
               struct filenode* tmpPtr = fileHead;
               struct filenode* prev = tmpPtr;
               struct filenode* tmpPtr2 = ptr->files;
               int found = 0;
               while (tmpPtr2 != NULL) {
                  while (tmpPtr != NULL) {
                     if (strcmp(tmpPtr->fileName, tmpPtr2->fileName) == 0){
                        found = 1;
                     }
                  }
                  if (found == 0) {
                     tail->next = malloc(sizeof(struct filenode**) + 1);
                     tail = tail->next;
                     tail->fileName = tmpPtr2->fileName;
                  }
               }
            }
         }
      }
  }
  struct filenode* tmp = fileHead;
  while (tmp != NULL) {
     printf("%s\n",tmp->fileName);
     tmp = tmp->next;
  }
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
