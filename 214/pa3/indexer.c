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
      puts("Directory");

      int len;
      struct dirent *pDirent;
      DIR *pDir;
      pDir = opendir(filename);
      if (pDir == NULL) {
        printf ("Cannot open directory '%s'\n", filename);
        return 0;
      }
      while((pDirent = readdir(pDir)) != NULL){
        if(strcmp(pDirent->d_name, ".") == 0 || strcmp(pDirent->d_name, "..") == 0){
          continue;
        }
        printf("%s/%s\n",filename, pDirent->d_name);
      }
      closedir(pDir);
    }
    else if( s.st_mode & S_IFREG )
    {
      puts("File");
    }
    else
    {
      puts("WTF");
    }
  }
  else
  {
    puts("Error, file not found");
    return 0;
  }

}
