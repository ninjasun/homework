#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "wordstat.h"

char optionInput;

void printHelp()
{
  printf("usage: ./wordstat <option> <filename>\n");
  printf("<filename> is the name of the file that wordstat should process.\n");
  printf("<option> is \"h\", \"l\", \"w\", or \"p\"\n");
  printf("wordstat -h: Help for how a user can run the program and quit.\n");
  printf("wordstat -l: number of lines.\n");
  printf("wordstat -w: number of words.\n");
  printf("wordstat -p: list of palindrome words in lexicographical order, along with the number of times each word appears, and whether they are in the dictionary.\n");
}


int numberLines(char *nameOfFile)
{
  char line[256];
  int lineCount=0;
  FILE *document;
  document = fopen(nameOfFile, "r");
  if (document == NULL){
    printf("Document could not be found\n");
  } else {
    while(fgets(line, 256 ,document) != NULL){
      lineCount++;
    }
    fclose(document);
  }
  return lineCount;
}

int numberWords(char *nameOfFile)
{
  int wordCount = 0;
  int wordBool = 0;
  FILE *document;
  document = fopen(nameOfFile, "r");
  if (document == NULL){
    printf("Document could not be found");
  } else {
    char letter;
    letter = fgetc(document);
    while (letter != EOF){
      if (((letter >= 65) && (letter <= 90)) || ((letter >= 97) && (letter <= 122))){
	if (wordBool == 0){
	  wordBool = 1;
	  wordCount++;
	}
      }
      else {
	wordBool = 0;
      }
      letter = fgetc(document);
    }
    fclose(document);
  }
  return wordCount;
}

int palindrome(char *nameOfFile)
{
  FILE *document;
  document = fopen(nameOfFile, "r");
  char letter;
  char tword[256];
  int t = 0;
  for (t = 0; t < sizeof(tword); t++){
    tword[t]='\0';
  }
  normalWord *head;
  int position = 0;
  int wordBool = 1;
  head = NULL;
  if (document == NULL){
    printf("Document could not be found\n");
    return 1;
  }
  else {
    letter = fgetc(document);
    while (letter != EOF){
      if (((letter >= 65) && (letter <= 90)) || ((letter >= 97) && (letter <= 122)))
	{
	  tword[position] = letter;
	  position++;
	}
      else {
	int pal = 0;
	tword[position]='\0';
	int x = 0;
	int y = position-1;
	for (x = 0; x < sizeof(tword); x++){
	  tword[x] = toupper(tword[x]);
	}
	for (x = 0; x < position/2; x++) {
	  if (tword[x] != tword[y]){
	    pal = 1;
	  }
	  y--;
	}
	if (pal == 0){
	  if (tword[0] != '\0'){
	    normalWord *tempWord;
	    tempWord = (normalWord*)calloc(1,sizeof(normalWord));
	    for (x = 0; x < sizeof(tword); x++){
	      tempWord->word[x]=tword[x];
	    }
	    if (head == NULL) {
	      head = tempWord;
	      tempWord->count = 1;
	    }
	    else {
	      normalWord *wordPtr;
	      int inList = 1;
	      wordPtr = head;
	      while(wordPtr != NULL){
		if (strcmp(wordPtr->word,tempWord->word) == 0){
		  inList = 0;
		  wordPtr->count++;
		}
		wordPtr = wordPtr->next;
	      }
	      if (inList == 1){
		normalWord *backPtr = NULL;
		normalWord *ptr;
		normalWord *frontPtr;
		int alreadyIn;
		alreadyIn = 0;
		ptr = head;
		frontPtr = head->next;
		while((ptr != NULL) && (alreadyIn != 1)){
		  if (frontPtr != NULL){
		    if ((head == ptr) && (strcmp(tempWord->word,ptr->word) < 0)){
		      tempWord->next = ptr;
		      head = tempWord;
		      alreadyIn = 1;
		    }
		    else if ((strcmp(ptr->word,tempWord->word) < 0) && (strcmp(frontPtr->word,tempWord->word) >= 0)){
		      ptr->next = tempWord;
		      tempWord->next = frontPtr;
		      alreadyIn = 1;
		    }
		    else{
		      backPtr = ptr;
		      ptr = frontPtr;
		      frontPtr = frontPtr->next;
		    }
		  }
		  else {
		    if (strcmp(ptr->word,tempWord->word)<0){
		      ptr->next = tempWord;
		    }
		    else {
		      tempWord->next = ptr;
		      if (backPtr != NULL){
			backPtr->next = tempWord;
		      }
		      else {
			head = tempWord;
		      }
		    }
		    alreadyIn = 1;
		  }
		}
		tempWord->count = 1;
	      }
	      else{
		free(tempWord);
	      }
	    }
	    FILE *dict;
	    dict = fopen("dict.txt","r");
	    if (dict == NULL){
	      printf("Dictionary could not be found\n");
	      return 1;
	    }
	    char dictLine[256];
	    if (tempWord != NULL){
	      tempWord->inDict = 1;
	      while (fgets(dictLine , 256 , dict) != NULL){
		char *dictString;
		dictString = strtok(dictLine , "\n");
		if (strcmp(tempWord->word,dictString)==0){
		  tempWord->inDict = 0;
		}
	      }
	    }
	    fclose(dict);
	    for (x = 0; x < sizeof(tword); x++){
	      tword[x] = '\0';
	    }
	  }
	  position = 0;
	}
	else{
	  for (x = 0; x < sizeof(tword); x++){
	    tword[x] = '\0';
	  }
	  position = 0;
	}
      }
      letter = fgetc(document);
    }
  }
  normalWord *tempWord;
  normalWord *tempWord2;
  tempWord = head;
  while (tempWord != NULL){
    char dictTrue[] = "true";
    char dictFalse[] = "false";
    char *tOrF;
    if (tempWord->inDict == 0){
      tOrF = dictTrue;
    } 
    else {
      tOrF = dictFalse;
    }
    printf("Palindrome: %s  In Dictionary:  %s  Count: %d\n",tempWord->word,tOrF,tempWord->count);
    tempWord2 = tempWord;
    tempWord = tempWord->next;
    free(tempWord2);
  }
  fclose(document);
  return 0;
}

int main (int argc, char **argv)
{
  int count = 0;
  if (strcmp(argv[1],"-h") == 0){
    printHelp();
  }
  else if (strcmp(argv[1],"-l") == 0){
    count = numberLines(argv[2]);
    printf("%d\n",count);
  }
  else if (strcmp(argv[1],"-w") == 0){
    count = numberWords(argv[2]);
    printf("%d\n",count);
  }
  else if (strcmp(argv[1],"-p") == 0){
    palindrome(argv[2]);
  }
  else{
    printHelp();
  }
  return 0;
}
