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

bool GregorianDate::isSame(int m, int d, int y) {
  return (m == month && d == day && y == year);
}

string GregorianDate::toString() {
  stringstream s;
  //s << m << "/" << d << "/" << y;
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

//TODO:
unsigned int GregorianDate::toDays() {
  unsigned int answer = 0;
  GregorianDate();
  
  return answer;
}

//TODO:
GregorianDate toGreg(unsigned int days) {
  return GregorianDate();
}
