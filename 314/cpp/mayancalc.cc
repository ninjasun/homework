#include "mayancalc.h"

int main(int argc, const char *argv[])
{
  //Checks for valid number of arguments
  if (argc < 3 or argc > 4) {
    cout << "Invalid number of arguments";
    return 0;
  }
  string command = argv[1]; //Holds first argument
  char* op = (char*) argv[2]; //Holds second argument
  const char* delim = "."; //Default delimiter for strtok

  if (command.compare("m+d") == 0) {
    int count = 0;
    unsigned int units[5];
    char* tok = strtok(op, delim);
    while (tok != NULL){
      units[count] = atoi(tok); count ++;
      tok = strtok(NULL, delim);
    }
    MayanDate date = MayanDate(units[0],units[1],units[2],units[3], units[4]);
    unsigned int dayCount = date.toDays();
    int toAdd = atoi(argv[3]);
    cout << toMayan(dayCount + toAdd).toString() << "\n";
  }
  else if (command.compare("m-d") == 0) {
    int count = 0;
    unsigned int units[5];
    char* tok = strtok(op, delim);
    while (tok != NULL){
      units[count] = atoi(tok); count ++;
      tok = strtok(NULL, delim);
    }
    MayanDate date = MayanDate(units[0],units[1],units[2],units[3], units[4]);
    unsigned int dayCount = date.toDays();
    int toSubtract = atoi(argv[3]);
    cout << toMayan(dayCount - toSubtract).toString() << "\n";
  }
  else if (command.compare("m-m") == 0) {
    int count = 0;
    unsigned int units[5];
    char* tok = strtok(op, delim);
    while (tok != NULL){
      units[count] = atoi(tok); count ++;
      tok = strtok(NULL, delim);
    }
    MayanDate date = MayanDate(units[0],units[1],units[2],units[3], units[4]);
    unsigned int day1 = date.toDays();
    count = 0;
    op = (char*) argv[3];
    tok = strtok(op, delim);
    while (tok != NULL){
      units[count] = atoi(tok); count ++;
      tok = strtok(NULL, delim);
    }
    date = MayanDate(units[0],units[1],units[2],units[3], units[4]);
    unsigned int day2 = date.toDays();
    unsigned int dayDif = (day1 > day2) ? (day1-day2) : (day2-day1);
    cout << dayDif << " days" << "\n";
    yearify(dayDif);
  }
  else if (command.compare("g=") == 0) {
    int count = 0;
    const char* gdelim = "/";
    op = (char*) argv[2];
    char* tok = strtok(op, gdelim);
    int gunits[3];
    while (tok != NULL){
      gunits[count] = atoi(tok); 
      tok = strtok(NULL, gdelim);
      count ++;
    }
    GregorianDate date = GregorianDate(gunits[1], gunits[0], gunits[2]);
    unsigned int tempDays = date.toDays();
    cout << toMayan(tempDays).toString() << "\n";
  }
  else if (command.compare("m=") == 0) {
    int count = 0;
    unsigned int units[5];
    char* tok = strtok(op, delim);
    while (tok != NULL){
      units[count] = atoi(tok); count ++;
      tok = strtok(NULL, delim);
    }
    MayanDate date = MayanDate(units[0],units[1],units[2],units[3], units[4]);
    unsigned int dayCount = date.toDays();
    cout << toGreg(dayCount).toString() << "\n";
  }
  else 
    cout << "Invalid command. Please try again. \n";
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
