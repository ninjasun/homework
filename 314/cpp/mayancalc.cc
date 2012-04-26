#include "mayancalc.h"

int main(int argc, const char *argv[])
{
  //cout << "Hello World\n"; 
  //cout << isLeap(2011); 
  if (argc < 3 or argc > 4) {
    cout << "Invalid number of arguments";
    return 0;
  }
  int i;
  const char* delim = ".";
  char* op = (char*) argv[2];
  if (strcmp(argv[1], "m+d") == 0) {
    for (i = 0; i < 5; i++) {
      tok = strtok(op, delim);
    }
  }

  return 0;
}

bool isLeap(int year)
{
  if (year%400 == 0)
    return true;
  else if (year%100 == 0)
    return false;
  else if (year%4 == 0)
    return true;
  else
    return false;
}
