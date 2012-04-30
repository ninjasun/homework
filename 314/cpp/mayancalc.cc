#include "mayancalc.h"

int main(int argc, const char *argv[])
{
  if (argc < 3 or argc > 4) {
    cout << "Invalid number of arguments";
    return 0;
  }
  string command = argv[1];
  char* op = (char*) argv[2];
  const char* delim = ".";

  if (command.compare("m+d") == 0) {
    int count = 0;
    int units[5];
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
    int units[5];
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
    int units[5];
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
    cout << (day1 - day2) << "\n";
  }
  else if (command.compare("g=") == 0) {

  }
  else if (command.compare("m=") == 0) {

  }
  else {
    cout << "Invalid command. Please try again. \n";
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

MayanDate toMayan(unsigned int days) {
  unsigned int ba = days / 144000;
  unsigned int ka = (days-ba*144000) / 7200;
  unsigned int tu = (days-ba*144000-ka*7200) / 360;
  unsigned int ui = (days-ba*144000-ka*7200-tu*360) / 20;
  unsigned int ki = (days-ba*144000-ka*7200-tu*360-ui*20);
  MayanDate foo =  MayanDate(ba, ka, tu, ui, ki);
  return foo;
};

