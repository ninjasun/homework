#include <stdio.h>
#include <stdlib.h>

typdef struct word{
   char word[256];
   int count;
   struct word *next;
}word;
