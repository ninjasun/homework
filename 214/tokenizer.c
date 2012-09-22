/*
 * tokenizer.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokenizer.h"


/*
 * Tokenizer type.  You need to fill in the type as part of your implementation.
 */

/*
 * TKCreate creates a new TokenizerT object for a given set of separator
 * characters (given as a string) and a token stream (given as a string).
 *
 * TKCreate should copy the two arguments so that it is not dependent on
 * them staying immutable after returning.  (In the future, this may change
 * to increase efficiency.)
 *
 * If the function succeeds, it returns a non-NULL TokenizerT.
 * Else it returns NULL.
 *
 * You need to fill in this function as part of your implementation.
 */

TokenizerT *TKCreate(char *separators, char *ts) {
  /* Allocate memory */
  TokenizerT *tk = malloc(sizeof(TokenizerT));
  tk->delims = malloc(sizeof(char*) * strlen(separators) + 1);
  tk->stream = malloc(sizeof(char*) * strlen(ts) + 1);

  strcpy(tk->delims, separators);
  strcpy(tk->stream, ts);

  return tk;
}

/*
 * TKDestroy destroys a TokenizerT object.  It should free all dynamically
 * allocated memory that is part of the object being destroyed.
 *
 * You need to fill in this function as part of your implementation.
 */

void TKDestroy(TokenizerT *tk) {
  free(tk->delims);
  free(tk->stream);
  free(tk);

  return;
}

/*
 * TKGetNextToken returns the next token from the token stream as a
 * character string.  Space for the returned token should be dynamically
 * allocated.  The caller is responsible for freeing the space once it is
 * no longer needed.
 *
 * If the function succeeds, it returns a C string (delimited by '\0')
 * containing the token.  Else it returns 0.
 *
 * You need to fill in this function as part of your implementation.
 */

char *TKGetNextToken(TokenizerT *tk) {
  while (tk->stream != NULL && strpbrk(tk->stream, tk->delims) == tk->stream){
    tk->stream += 1;
  }

  if (tk->stream == NULL) {
    return NULL;
  }

  char *endOfToken = strpbrk(tk->stream, tk->delims);
  if (endOfToken == NULL){
    char *wholeWord = malloc(sizeof(char *) * strlen(tk->stream) + 1);
    strcpy(wholeWord, tk->stream);
    tk->stream = NULL;
    return wholeWord;
  }

  char *ptr = tk->stream;
  int i = 0;
  while(ptr != endOfToken) {
    ptr++;
    i++;
  }
  char *token = malloc(sizeof(char *) * 512 );
  int tokenLength = ( ((int)(endOfToken - ptr))+i);
  /*printf("LENGTH: %d\n ", tokenLength);*/
  strncpy(token, tk->stream, tokenLength);


  tk->stream = tk->stream + strlen(token);

  return token;
}

/*
 * main will have two string arguments (in argv[1] and argv[2]).
 * The first string contains the separator characters.
 * The second string contains the tokens.
 * Print out the tokens in the second string in left-to-right order.
 * Each token should be printed on a separate line.
 */

int main(int argc, char **argv) {
  if (argc != 3) {
    printf("Invalid input. Two arguments are required\n");
    return 1;
  }

  char *delimiters  = argv[1];
  char *original = argv[2];

  TokenizerT *tk = TKCreate(delimiters, original);
  char *currToken;
  int i = 0;
  while ( (currToken = TKGetNextToken(tk)) != NULL ) {
    printf("%s\n", currToken);
    free(currToken);
    i++;
    if (i > 8){
      break;
    }
  }

  TKDestroy(tk);

  return 0;
}
