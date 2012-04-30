#include "mayancalc.h"

MayanDate::MayanDate(){
  baktun = 0;
  katun = 0;
  tun = 0;
  uinal = 0;
  kin = 0;
}

MayanDate::MayanDate(unsigned int bak, unsigned int kat, unsigned int t, unsigned int ui, unsigned int k){
  baktun = bak;
  katun = kat;
  tun = t;
  uinal = ui;
  kin = k;
}

void MayanDate::set(unsigned int bak, unsigned int kat, unsigned int t, unsigned int ui, unsigned int k){
  baktun = bak;
  katun = kat;
  tun = t;
  uinal = ui;
  kin = k;
}

//MayanDate MayanDate::operator++() const{
  //unsigned int days = toDays();
  //days += 1;
  //return MayanDate::toMayan(days);
//}

//MayanDate MayanDate::operator+(unsigned int add) const {

//}

unsigned int MayanDate::toDays() const{
  unsigned int days = kin + uinal * 20 + tun * 360 + katun * 7200 + baktun * 144000;
  return days;
}

string MayanDate::toString() const{
  stringstream s;
  s << baktun << "." << katun << "." << tun << "." << uinal << "." << kin;
  return s.str();
}

