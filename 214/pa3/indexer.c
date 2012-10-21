#include "indexer.h"
#include <ftw.h>


struct globalList{
  char* word;
} wordCount;


int fileCallback(const char* pathname, const struct stat* ptr, int flag){
  if (flag == 0) {

    FILE *file = fopen (pathname, "r");
    if (file != NULL)
    {
      char* line = malloc(1024); //Buffer where line is stored
      while ( fgets (line, 1024, file ) != NULL) /* read a line */
      {
        puts(line);
      }
      fclose (file);
      free(line);
    }
  }

  return 0;
}


int main(int argc, char **argv) {

  if (argc != 3) {
    printf("Invalid input. Two arguments are required\n");
    return 1;
  }
  printf("\n");

  ftw(argv[2], fileCallback, 1);

  return 0;
}

