#ifndef __MAYANCALC_H 
#define __MAYANCALC_H 

#include <iostream> 
#include <string>
#include <sstream>
#include <string.h>
#include <stdlib.h>

class MayanDate {
  private:
    unsigned int baktun;
    unsigned int katun;
    unsigned int tun;
    unsigned int uinal;
    unsigned int kin;
  public:
    //Constructors
    MayanDate();
    MayanDate( unsigned int, unsigned int, unsigned int, unsigned int, unsigned int );

    //MayanDate methods
    unsigned int      toDays() const; //Converts MayanDate to days
    std::string       toString() const; //Converts MayanDate to a string
};

class GregorianDate {
  private:
    int day;
    int month;
    int year;
  public:
    //Constructors
     GregorianDate();
     GregorianDate(int, int, int);

     //GregorianDate methods
     std::string      toString(); //Converts GregorianDate to string
     unsigned int     toDays(); //Converts GregorianDate to days
};

  bool isLeap(int year); //Checks if year is leap year
  MayanDate toMayan(unsigned int); //Converts days to a MayanDate
  GregorianDate toGreg(unsigned int); //Converts days to a GregorianDate
  GregorianDate yearify(unsigned int); //Handles extra credit year evaluation
  using namespace std;
#endif
