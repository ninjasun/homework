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

unsigned int MayanDate::toDays() const{
  unsigned int days = kin + uinal * 20 + tun * 360 + katun * 7200 + baktun * 144000;
  return days;
}

string MayanDate::toString() const{
  stringstream s;
  s << baktun << "." << katun << "." << tun << "." << uinal << "." << kin;
  return s.str();
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
