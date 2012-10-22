#include "indexer.h"


int main(int argc, char **argv) {

  if (argc != 3) {
    printf("Invalid input. Two arguments are required\n");
    return 1;
  }
  printf("\n");

  //Setting up globals
  delims = getDelims();
  wordList = NULL;

  ftw(argv[2], fileCallback, 1);

  printData(argv[1]);
  gundamFreedom();
  return 0;
}

void printData(char* outputFileName){
  FILE *outputFile;
  int fileExists = 0;
  if ((outputFile = fopen(outputFileName, "r")) != NULL) {
    puts("A file with this name already exists. Overwrite? [y]es, [n]o: ");
    char response;
    response = fgetc(stdin);
    if (response == 'n'){
      return;
    }
    else {
      //TODO: OVERWRITE
    }
    fclose(outputFile);
  }
  else {
    //TODO: CREATE FILE
    wordNode* wptr = wordList;
    fileNode* fptr; 
    while(wptr != NULL) {
      fprintf(stdout, "<list> %s\n", wptr->word);
      fptr = wptr->files;
      int count = 0;
      while (fptr != NULL && count < 5) {
        fprintf(stdout, "%s %d ", fptr->fileName, fptr->count);
        count++;
        fptr = fptr->next;
      }
      fprintf(stdout, "\n</list>\n");
      wptr = wptr->next;
    }
  }
}

int fileCallback(const char* pathname, const struct stat* ptr, int flag){
  if (flag == 0) {
    puts(pathname);
    char* tempPath = malloc(sizeof(char) * (strlen(pathname) + 1));

    FILE *file = fopen (pathname, "r");
    if (file != NULL)
    {
      char* line = malloc(2048); //Buffer where line is stored
      char* tempWord = malloc(sizeof(char) * 1024);
      while (fgets (line, 2048, file ) != NULL) /* read a line */
      {
        char* token;
        int i;
        for (token=strtok(line, delims); token != NULL; token=strtok(NULL, delims)) {
          for(i=0; i < strlen(token); i++){
            token[i] = tolower(token[i]);
          }
          puts(token);
          strcpy(tempWord, token);
          strcpy(tempPath, pathname);
          addCount(tempPath, tempWord);
        }
      }
      free(tempWord);
      free(line);
      fclose (file);
    }
    free(tempPath);
  }

  return 0;
}

int addCount(char* path, char* word){
  if (wordList == NULL){
    //First word to be entered
    wordList = malloc(sizeof(struct wordNode));
    wordList->word = malloc(strlen(word) + 1);
    strcpy(wordList->word, word);
    wordList->next = NULL;

    struct fileNode* firstFile = malloc(sizeof(struct fileNode));
    firstFile->fileName = malloc(strlen(path) + 1);
    firstFile->count = 1;
    strcpy(firstFile->fileName, path);
    wordList->files = firstFile;
  }
  else if (strcmp(wordList->word, word) < 0){
    // EDGE CASE OF INSERTING NEW HEAD
    wordNode* newHead = malloc(sizeof(struct wordNode));
    newHead->word = malloc(strlen(word) + 1);
    strcpy(newHead->word, word);
    newHead->next = wordList;
    wordList = newHead;

    fileNode* newFile = malloc(sizeof(struct fileNode));
    newFile->fileName = malloc(strlen(path) + 1);
    strcpy(newFile->fileName, path);
    newFile->next = NULL;
    newFile->count = 1;

    wordList->files = newFile;
  }
  else { //At least one word exists
    wordNode* wordPtr = wordList;
    int comparison = strcmp(wordPtr->word, word);
    while( (wordPtr->next != NULL) && (comparison > 0) ){
      wordPtr = wordPtr->next;
    }
    if (comparison == 0){
      // THIS WORD ALREADY EXISTS
      fileNode* filePtr = wordPtr->files;
      fileNode* prev;
      while (filePtr != NULL){
        if (strcmp (filePtr->fileName,path) == 0){
          filePtr->count++;
          while(filePtr->next != NULL){
              if (filePtr->count > filePtr->next->count){
                char* tempWord = filePtr->fileName;
                filePtr->fileName = filePtr->next->fileName;
                filePtr->next->fileName = tempWord;
                filePtr->next->count++;
                filePtr->count--;
              }
              else {
                break;
              }
              filePtr = filePtr->next;
          }
          return 0;
        }
        prev = filePtr;
        filePtr = filePtr->next;
      }
      fileNode* newHead = malloc(sizeof(fileNode));
      newHead->fileName = malloc(strlen(path) + 1);
      strcpy(newHead->fileName, path);
      newHead->count = 1;
      newHead->next = wordPtr->files;
      wordPtr->files = newHead;
    }
    else if( (wordPtr->next == NULL) || (comparison != 0) ){
      //Wordnode needs to be created
      wordNode* nextPtr = malloc(sizeof(struct wordNode));
      nextPtr->word = malloc(strlen(word) + 1);
      strcpy(nextPtr->word, word);
      nextPtr->next = wordPtr->next;
      wordPtr->next = nextPtr;

      struct fileNode* firstFile = malloc(sizeof(struct fileNode));
      firstFile->fileName = malloc(strlen(path) + 1);
      strcpy(firstFile->fileName, path);
      wordPtr->files = firstFile;
      firstFile->count = 1;
      firstFile->next = NULL;
    }
  }

  return 0;
}

char* getDelims()
{
  char *delimList = malloc(sizeof ( char)*257 );
  char *ptr = delimList;
  int i;
  for (i =1; i < 256; i++)
  {
    if (isalnum(i) == 0)
    {
      // Not an alphanumeric character
      *ptr = i;
      ptr++;
    }
  }
  *ptr = '\0';

  return delimList;
}


void gundamFreedom(){
  free(delims);
}

