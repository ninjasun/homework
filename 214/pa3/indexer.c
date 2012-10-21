#include "indexer.h"
#include <ftw.h>

int fileCallback(const char* pathname, const struct stat* ptr, int flag){

  if (flag == 1){
  // Directory
    /*puts(pathname);*/
  }
  else if (flag == 0) {
  // File
    printf("File: %s\n", pathname);
  }

}


int main(int argc, char **argv) {

  if (argc != 3) {
    printf("Invalid input. Two arguments are required\n");
    return 1;
  }

  ftw(argv[2], fileCallback, 1);

  return 0;
}

