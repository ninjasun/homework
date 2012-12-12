#include "books.h"

void producer(char* file) {
  return NULL;
}

int main(int argc, char** argv) {
  if (argc != 4) {
    puts("Invalid number of arguments");
    return 1;
  }

  char* db = argv[1];
  char* orders = argv[2];
  char* categoryList = argv[3];

  struct customer* customerList = NULL;
  struct book* bookList = NULL;
  FILE *dbFile = fopen(db, "r");
  if (dbFile != NULL) {
    char* line = malloc(2048);
    while (fgets (line, 2048, dbFile) != NULL) {
      struct customer* newCust = malloc(sizeof(struct customer) + 1);
      char* token;
      char* delims = "|";
      int i = 0;
      for (token=strtok(line, delims); token != NULL; token=strtok(NULL, delims)) {
        switch(i) {
          case 0://name
            newCust->name = token;
            break;
          case 1://id
            newCust->id = atoi(token);
            break;
          case 2://balance
            newCust->balance = atof(token);
            break;
          case 3://address
            newCust->address = token;
            break;
          case 4://state
            newCust->state = token;
            break;
          case 5://zip
            newCust->zip = token;
            break;
          default :
            break;
        }
        i++;
      }
      newCust->next = customerList;
      customerList = newCust;
    }
    free(line);
    fclose(dbFile);
  }
  else {
    puts("Database file failed to open");
    return 1;
  }

  FILE *orderFile=fopen(orders, "r");
  if (orderFile != NULL) {
     char* line = malloc(2048);
     while(fgets (line, 2048, orderFile) != NULL) {
        struct book* newBook = malloc(sizeof(struct book) + 1);
        char* token;
        char* delims = "|";
        int i = 0;
        for (token = strtok(line, delims); token != NULL; token=strtok(NULL, delims)) {
          switch(i) {
            case 0://name
               newBook->title = token;
               break;
            case 1://id
                newBook->price = atof(token);
                break;
            case 2://balance
                newBook->customerID = atoi(token);
                break;
            case 3://address
                newBook->category = token;
                break;
            default :
                break;
        }
        i++;
        }
        newBook->next= bookList;
        bookList = newBook;
     }
     free(line);
     fclose(orderFile);
  }
  /*pthread_t producer, consumer;*/

}