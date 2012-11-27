#include "search.h"

int main(int argc, char **argv) {

  if (argc < 2 || argc > 4) {
    printf("Invalid number of arguments");
    return 1;
  }
  else if (argc == 4 && strcmp(argv[1], "-m") == 0)
  {
    //cache search

    index_file = argv[3];
    char * sizeCache = malloc(sizeof(argv[2]) - 2);

    strncpy(sizeCache, argv[2], sizeof(argv[2])-2);

    limit = atoi(sizeCache);

    if(strstr(argv[2],"MB") != NULL)
    {
      limit = limit * 1024;
    }
    else if(strstr(argv[2],"GB") != NULL)
    {
      limit = limit * 1048576;
    }
    //printf("%d\n", limit);
  }
  else
  {
    index_file = argv[1];
  }
  printf("%s\n", index_file);
  buildFiles();

  char* searchInput = malloc(1024);

  char* inputLine;
  char* searchOption;

  while (1 == 1) {
    printf("Search> ");
    fgets(searchInput, 1024, stdin);
    searchInput[strlen(searchInput) - 1] = '\0';

    if (searchInput[0] == 'q'){
      //puts("We got q");
      break;
    }
    else if (searchInput[0] == 's'){
      if(searchInput[1] == 'a'){
        //puts(searchInput);
        andSearch(searchInput);
      }
      if(searchInput[1] == 'o'){
        orSearch(searchInput);
      }
    }
  }

  free(theFiles);

  return 0;
}

int countFiles(){
  char* line;
  FILE *file = fopen (index_file, "r");
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

void buildFiles(){
  int fileCount = countFiles();
  char** fileList = malloc(sizeof(char*) * fileCount + 1);
  char* line;
  FILE *file = fopen (index_file, "r");
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
  theFiles = fileList;
}

struct wordnode* checkCache(char* word){
   struct wordnode* wordPtr = cache;
   struct wordnode* prev = wordPtr;
   int foundWord = 0;
   while (wordPtr != NULL) {
      if (strcmp(wordPtr->word, word) == 0){
         foundWord = 1;
         return wordPtr;
      }
      prev = wordPtr;
      wordPtr = wordPtr->next;
   }
   struct wordnode* newNode = getFileList(word);
   prev->next = newNode;
   cacheSize = cacheSize + newNode->size;
   struct wordnode* tmp;
   while ((cacheSize > limit) && (limit != 0)) {
      if (strcmp(cache->next->word, newNode->word) == 0){
         freedom(tmp);
         cache = newNode;
         cacheSize = newNode->size;
         return newNode;
      }
      cacheSize = cacheSize - cache->size;
      tmp = cache;
      cache = cache->next;
      free(tmp);
   }
   return newNode;
}

void andSearch (char* line) {
   //puts(line);
   strncpy(line, line + 2, strlen(line));
   //puts(line);
   char* token;
   token = strtok(line, " ");
   struct filenode* fileHead = NULL;
   while (token != NULL) {
      struct wordnode* ptr = checkCache(token);
      while (ptr != NULL) {
         //printf("word: %s, token: %s",ptr->word,token);
         if (strcmp(ptr->word, token) == 0) {
            if (fileHead == NULL) {
               fileHead = malloc(sizeof(struct filenode) + 1);
               struct filenode* tmpPtr2;
               struct filenode* tmpPtr;
               tmpPtr = ptr->files;
               tmpPtr2 = fileHead;
               tmpPtr2->next = NULL;
               tmpPtr2->fileName = tmpPtr->fileName;
               tmpPtr = tmpPtr->next;
               //tmpPtr2 = tmpPtr2->next;
               //tmpPtr = tmpPtr->next;
               //tmpPtr2 = tmpPtr2->next;
               while (tmpPtr != NULL) {
                  tmpPtr2->next = malloc(sizeof(struct filenode) + 1);
                  tmpPtr2->next->fileName = tmpPtr->fileName;
                  tmpPtr2->next->next = NULL;
                  tmpPtr2 = tmpPtr2->next;
                  tmpPtr = tmpPtr->next;
               }
               //fileHead->next = NULL;
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
                        prev = tmpPtr;
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
         ptr = ptr->next;
      }
      token = strtok(NULL, " ");
   }
   struct filenode* tmp = fileHead;
   struct filenode* freedom = tmp;
   while (tmp != NULL){
      printf("%s\n", tmp->fileName);
      freedom = tmp;
      tmp = tmp->next;
      free(freedom);
   }
}

void orSearch(char* line){
  strncpy(line, line + 2, strlen(line));
  char* token;
  token = strtok(line, " ");
  struct filenode* fileHead = NULL;
  struct filenode* tail = NULL;
  while (token != NULL) {
      struct wordnode* ptr = checkCache(token);
      while (ptr != NULL) {
         if (strcmp(ptr->word, token) == 0) {
            if (fileHead == NULL) {
               fileHead = malloc(sizeof(struct filenode) + 1);
               struct filenode* tmpPtr2;
               struct filenode* tmpPtr;
               tmpPtr = ptr->files;
               tmpPtr2 = fileHead;
               tmpPtr2->next = NULL;
               tmpPtr2->fileName = tmpPtr->fileName;
               tail = tmpPtr2;
               tmpPtr = tmpPtr->next;

               //tmpPtr2 = tmpPtr2->next;
               //tmpPtr = tmpPtr->next;
               //tmpPtr2 = tmpPtr2->next;
               while (tmpPtr != NULL) {
                  tmpPtr2->next = malloc(sizeof(struct filenode) + 1);
                  tmpPtr2->next->fileName = tmpPtr->fileName;
                  tmpPtr2->next->next = NULL;
                  tmpPtr2 = tmpPtr2->next;
                  tail = tmpPtr2;
                  tmpPtr = tmpPtr->next;
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
                        break;
                     }
                     tmpPtr = tmpPtr->next;
                  }
                  if (found == 0) {
                     tail->next = malloc(sizeof(struct filenode) + 1);
                     tail->next->fileName = tmpPtr2->fileName;
                     tail->next->next = NULL;
                     tail = tail->next;
                  }
                  tmpPtr2 = tmpPtr2->next;
               }
            }
         }
         ptr = ptr->next;
      }
      token = strtok(NULL, " ");
  }
  struct filenode* tmp = fileHead;
  struct filenode* freedom = tmp;
  while (tmp != NULL) {
     printf("%s\n",tmp->fileName);
     freedom = tmp;
     tmp = tmp->next;
     free(freedom);
  }
}

struct wordnode*  getFileList(char* word) {

}
