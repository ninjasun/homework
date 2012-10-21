#include "indexer.h"

int main(int argc, char **argv) {

  if (argc != 3) {
    printf("Invalid input. Two arguments are required\n");
    return 1;
  }

  traverser(NULL, argv[2]);

  return 0;
}

int traverser(void* list, char* filename){
  struct stat s;
  if( stat(filename, &s) == 0 )
  {
    if( s.st_mode & S_IFDIR )
    {
      //it's a directory
      puts("Directory");
    }
    else if( s.st_mode & S_IFREG )
    {
      //it's a file
      puts("File");
    }
    else
    {
      puts("WTF");
      //something else
    }
  }
  else
  {
    puts("Error, file not found");
    return 0;
  }

}
