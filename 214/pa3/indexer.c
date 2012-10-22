#include "indexer.h"


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
        for (token=strtok(line, delims); token != NULL; token=strtok(NULL, delims)) {
          for ( ; *token; ++token) *token = tolower(*token);
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
    strcpy(firstFile->fileName, path);
    wordList->files = firstFile;
  }
  else if (1 == 2){
    //TODO: EDGE CASE OF INSERTING NEW HEAD
  }
  else { //At least one word exists
    wordNode* wordPtr = wordList;
    int comparison = strcmp(wordPtr->word, word);
    while( (wordPtr->next != NULL) && (comparison > 0) ){
      wordPtr = wordPtr->next;
    }
    if (comparison == 0){
      //TODO: WORDNODE ALREADY EXISTS
      fileNode* filePtr = wordPtr->files;
      fileNode* prev;
      while (filePtr != NULL){
        if (strcmp (filePtr->fileName,path) == 0){
          filePtr->count++;
          if (filePtr->next != NULL) {
            if (filePtr->count > filePtr->next->count){
              prev->next = filePtr->next;
              
            }
          }
          return 0;
        }
        prev = filePtr;
        filePtr = filePtr->next;
      }
      if (foundFile == 0) {
        
      }
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

int main(int argc, char **argv) {

  if (argc != 3) {
    printf("Invalid input. Two arguments are required\n");
    return 1;
  }
  printf("\n");

  //Setting up globals
  delims = getDelims();
  /*wordList = malloc(sizeof(struct wordNode) + 1);*/
  wordList = NULL;

  ftw(argv[2], fileCallback, 1);

  free(delims);
  return 0;
}

