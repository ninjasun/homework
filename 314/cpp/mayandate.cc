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

MayanDate & MayanDate::operator++() {

}

unsigned int MayanDate::toDays() {
  unsigned int days = kin + uinal * 20 + tun * 360 + katun * 7200 + baktun * 144000;
  return days;
}

static MayanDate::toMayan(int days) {

}




//stringstream s;
//s << "sample" << " piece";
//return s.str();


