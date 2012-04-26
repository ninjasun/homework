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

MayanDate MayanDate::operator++() const{
  unsigned int days = toDays();
  days += 1;
  return MayanDate::toMayan(days);
}

MayanDate MayanDate::operator+(unsigned int add) const {

}

unsigned int MayanDate::toDays() const{
  unsigned int days = kin + uinal * 20 + tun * 360 + katun * 7200 + baktun * 144000;
  return days;
}

static MayanDate toMayan(unsigned int days){
  unsigned int ba = days / 144000;
  unsigned int ka = (days-ba) / 7200;
  unsigned int tu = (days-ba-ka) / 360;
  unsigned int ui = (days-ba-ka-tu) / 20;
  unsigned int ki = (days-ba-ka-tu-ui);
  MayanDate foo =  MayanDate(ba, ka, tu, ui, ki);
  return foo;
};

string MayanDate::toString() const{
  stringstream s;
  s << baktun << "." << katun << "." << tun << "." << uinal << "." << kin;
  return s.str();
}

