#include <stdio.h>
#include <string.h>
#include "tokenizer.c"
#include <dirent.h>
#include <stdlib.h>
#include <ctype.h>
#include "wordstat.c"
#include "indexer.h"

int fileReader (char* fileName, word* headNode){
   FILE *read;
   read = fopen (fileName, "r");
   char rword[256];
   char letter;
   int t = 0;
   for (t = 0; t < sizeof(rword); t++){
      rword[t]='\0';
   }
   word *head;
   int position = 0;
   head = headNode;
   if (read == NULL) {
      printf("Document could not be found\n");
      return 1;
   }
   letter = fgetc(read);
   while (letter != EOF){
      if (((letter >= 65) && (letter <= 90)) || ((letter >= 97) && (letter <= 122))) {
         rword[position] = letter;
         position++;
      }
      else if (position > 0){
         word *tempWord;
         file *tempFile;
         tempWord = (word*)calloc(1,sizeof(word));
         tempFile = (file*)calloc(1,sizeof(file));
         int y = 0;
         for (y = 0; y < sizeof(fileName); y++){
            tempFile->name[y]=fileName[y];
         }
         int x = 0;
         for (x = 0; x < sizeof(rword); x++){
            tempWord->word[x]=rword[x];
         }
         if (head == NULL) {
            head = tempWord;
            head->head = tempFile;
            head->head->count = 1;
         }
         int foundWord = 0;
         int foundFile = 0;
         word *ptr;
         ptr = head;
         while (ptr != NULL) {
            if (strcmp(ptr->word,tempWord->word) == 0){
               foundWord = 1;
               free(tempWord);
               file *ptr2;
               ptr2 = ptr->head;
               while (ptr2 != NULL) {
                  if (strcmp(ptr2->name,fileName) == 0){
                     foundFile = 1;
                     ptr2->count++;
                     free(tempFile);
                  }
               }
               if (foundFile == 0) {
                  ptr2->next = tempFile;
                  tempFile->count = 1;
               }
            }
            ptr = ptr->next;
         }
         if (foundWord == 0){
            ptr = head;
            while ((ptr->next != NULL) && (strcmp(ptr->word,tempWord->word) > 0)){
               ptr = ptr->next;
            }
            word *tempPtr;
            tempPtr = ptr->next;
            ptr -> next = tempWord;
            tempWord -> next = tempPtr;
         }
      }
   }
}


int main(int argc, char **argv) {
   printf("HAI :D -Jingfei\n");
   return 0;
}
