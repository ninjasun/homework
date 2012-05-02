#include "mayancalc.h"

GregorianDate::GregorianDate() {
  day = 8;
  month = 11;
  year = -3113;
}

GregorianDate::GregorianDate(int d, int m, int y) {
  day = d;
  month = m;
  year = y;
}

string GregorianDate::toString() {
  stringstream s;
  if (month < 10)
    s << "0";
  s << month << "/";
  if (day < 10)
    s << "0";
  s << day << "/" ;
  int y = year > 0 ? year : -year;
  if (year < 0)
    s << "-";
  if (y < 10)
    s << "000";
  else if (y < 100)
    s << "00";
  else if (y < 1000)
    s << "0";
  s << y;
  return s.str();
}

unsigned int GregorianDate::toDays() {
  unsigned int dayCount = 0;
  int d = 11;
  int m = 8;
  int y = -3113;

  int months[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  while (y != year || m < month || d < day) {
    int dayLimit = (m == 2 && isLeap(y)) ? 29 : months[m-1];
    dayCount = dayCount+1;
    if (d < dayLimit) {
      d = d+1;
    }
    else {
      d=1;
      if (m == 12) {
        y = y+1;
        m = 1;
      }
      else {
        m = m+1;
      }
    }
  }
  return dayCount;
}

GregorianDate toGreg(unsigned int days) {
  unsigned int dayCount = days;
  int months[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  unsigned int d = 11;
  unsigned int m = 8;
  unsigned int y = -3113;

  while (dayCount > 0){
    int dayLimit = (m == 2 && isLeap(y)) ? 29 : months[m-1];
    if(d < dayLimit) 
      d = d + 1;
    else {
      d = 1;
      if (m == 12) {
        m = 1;
        y++;
      }
      else
        m++;
    }
    dayCount--;
  }
  return GregorianDate(d, m, y);
}

GregorianDate yearify(unsigned int days) {
  unsigned int dayCount = days;
  int months[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  unsigned int d = 0;
  unsigned int m = 0;
  unsigned int y = 0;

  while (dayCount > 0){
    int dayLimit = (m == 1 && isLeap(y)) ? 29 : months[m];
    if(d < dayLimit)
      d = d + 1;
    else {
      d = 1;
      if (m == 11) {
        m = 1;
        y++;
      }
      else
        m++;
    }
    dayCount--;
  }
  cout << "Extra Credit: " << y << " year(s), " << m << " month(s), and " << d << " day(s)\n";
}
