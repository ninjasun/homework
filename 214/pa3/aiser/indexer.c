#include <stdio.h>
#include <string.h>
#include "tokenizer.c"
#include <dirent.h>
#include <stdlib.h>
#include <ctype.h>
#include "wordstat.c"

char* fileReader (char* file){
   FILE *read;
   read = fopen (file, "r");
   char rword[256];
   char letter;
   int t = 0;
   for (t = 0; t < sizeof(rword); t++){
      rword[t]='\0';
   }
   word *head;
   int position = 0;
   head = NULL;
   if (document == NULL) {
      printf("Document could not be found\n");
      return 1;
   }
   letter = fgetc(document);
   while (letter != EOF){
      if (((letter >= 65) && (letter <= 90)) || ((letter >= 97) && (letter <= 122))) {
         rword[position] = letter;
         position++;
      }
      else if (position > 0){
         word *tempWord;
         tempWord = (word*)calloc(1,sizeof(word));
         int x = 0;
         for (x = 0; x < sizeof(rword); x++){
            tempWord->word[x]=rword[x];
         }
         if (head == NULL) {
            head = tempWord;
            head->count = 1;
         }
         int found = 0;
         word *ptr;
         ptr = head;
         while (ptr != NULL) {
            if (strcmp(ptr->word,tempWord->word) == 0){
               found = 1;
               ptr->count++;
            }
         }
         if (found = 0){
            ptr = head;
            while (ptr->next != NULL){

            }
         }
      }
   }
}


int main(int argc, char **argv) {
   printf("HAI :D -Jingfei\n");
}
