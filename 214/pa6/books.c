#include "books.h"

int main(int argc, char** argv) {

  if (argc != 4) {
    printf("Invalid number of arguments");
    return 1;
  }

  char* db = argv[1];
  char* orders = argv[2];
  char* categoryList = argv[3];


  pthread_t producer, consumer;
}
