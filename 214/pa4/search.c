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

void andSearch (wordNode *head, char* line) {
   strncpy(line, line + 2);
   char* token;
   token = strtok(line, " ");
   fileNode fileHead = NULL;
   while (token != NULL) {
      ptr = head;
      while (ptr != NULL) {
         if (strcmp(ptr.word, token) == 0) {
            if (fileHead == NULL) {
               fileHead = malloc(sizeof(struct fileNode*) + 1);
               fileNode tmpPtr2;
               fileNode tmpPtr;
               tmpPtr = ptr.files;
               tmpPtr2 = fileHead;
               while (tmpPtr != NULL) {
                  tmpPtr2.fileName = tmpPtr.fileName;
                  tmpPtr2.next = malloc(sizeof(fileNode*) + 1);
                  tmpPtr2 = tmpPtr2.next;
               }
            }
            else {
               fileNode tmpPtr = fileHead;
               fileNode prev = tmpPtr;
               fileNode tmpPtr2 = ptr.files;
               int found = 0;
               while (tmpPtr != NULL) {
                  while (tmpPtr2 != NULL) {
                     if (strcmp(tmpPtr.fileName,tmpPtr2.fileName) == 0){
                        found = 1;
                        break;
                     }
                     tmpPtr2 = tmpPtr2.next;
                  }
                  if (found == 0){
                     if (strcmp(prev.fileName,tmpPtr.fileName) == 0){
                        fileHead = fileHead.next;
                        free(prev);
                        tmpPtr = fileHead;
                     }
                     else {
                        prev.next = tmpPtr.next;
                        free(tmpPtr);
                        tmpPtr = prev.next;
                     }
                  }
                  else {
                     prev = tmpPtr;
                     tmpPtr = tmpPtr.next;
                  }
                  found = 0;
               }
            }
         }
      }
      token = strtok(NULL, " ");
   }
   struct filenode tmp = fileHead;
   while (tmp!= NULL){
      printf("%s\n", tmp.fileName);
   }
}

void orSearch(wordNode *head, char* line){
  strncpy(line, line + 2);
  char* token;
  token = strtok(line, " ");
  fileNode fileHead = NULL;
  struct filenode tail = NULL;
  while (token != NULL) {
      ptr = head;
      while (ptr != NULL) {
         if (strcmp(ptr.word, token) == 0) {
            if (filehead == NULL) {
               fileHead = malloc(sizeof(struct filenode*) + 1);
               struct filenode tmpPtr;
               struct filenode tmpPtr2;
               tmpPtr = ptr.files;
               tmpPtr2 = fileHead;
               while (tmpPtr != NULL) {
                  tmpPtr2.fileName = tmpPtr.fileName;
                  tmpPtr2.next = malloc(sizeof(struct filenode*) + 1);
                  tail = tmpPtr2;
                  tmpPtr2 = tmpPtr2.next;
               }
            }
            else {
               struct filenode tmpPtr = fileHead;
               struct filenode prev = tmpPtr;
               struct filenode tmpPtr2 = ptr.files;
               int found = 0;
               while (tmpPtr2 != NULL) {
                  while (tmpPtr != NULL) {
                     if (strcmp(tmpPtr.fileName, tmpPtr2.fileName) == 0){
                        found = 1;
                     }
                  }
                  if (found == 0) {
                     tail.next = malloc(sizeof(struct filenode*) + 1);
                     tail = tail.next;
                     tail.fileName = tmpPtr2.fileName;
                  }
               }
            }
         }
      }
  }
  struct filenode tmp = fileHead;
  while (tmp != NULL) {
     printf("%s\n",tmp.fileName);
     tmp = tmp.next;
  }
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
