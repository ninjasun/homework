#ifndef __MAYANCALC_H 
#define __MAYANCALC_H 

#include <iostream> 

class MayanDate {
  // Bak'tun, Ka'tun, etc stuff ...
  private:
    unsigned int baktun;
    unsigned int katun;
    unsigned int tun;
    unsigned int uinal;
    unsigned int kin;
  public:
    MayanDate();
    MayanDate( unsigned int, unsigned int, unsigned int, unsigned int, unsigned int );
    void              set( unsigned int, unsigned int, unsigned int, unsigned int, unsigned int );
    MayanDate &       operator++();
    int               operator-( const MayanDate & ) const;
    MayanDate         operator+( unsigned int ) const;
    MayanDate         operator-( unsigned int ) const;
    bool              operator==( const MayanDate & ) const;
    bool              operator!=( const MayanDate & m ) const;
    void              get_string( char *, unsigned int ) const;
    unsigned int      toDays();
    static MayanDate  toMayan(int days);
};

class GregorianDate {
 // year, month, day data
public:
   GregorianDate();
   GregorianDate( unsigned int, unsigned int, unsigned int );
   void  set( unsigned int, unsigned int, int );
   GregorianDate & operator++();
   bool  operator==( const GregorianDate & ) const;
   bool  operator!=( const GregorianDate & g ) const;
   int  operator-( const GregorianDate & ) const;
   GregorianDate operator-( unsigned int ) const;
   GregorianDate operator+( unsigned int ) const;
   void  get_string( char *, unsigned int ) const;
};

  bool isLeap(int year);
  using namespace std;

#endif
