#ifndef __MAYANCALC_H 
#define __MAYANCALC_H 

#include <iostream> 

/*Day Chart
Days              Long Count period    Long Count unit
1                 -                    1 Kin
20                20 Kin               1 Uinal
360               18 Uinal             1 Tun
7,200             20 Tun               1 Ka'tun
144,000           20 Ka'tun            1 Bak'tun
*/

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
    MayanDate*        operator++();
    int               operator-( const MayanDate & ) const;
    MayanDate         operator+( unsigned int ) const;
    MayanDate         operator-( unsigned int ) const;
    bool              operator==( const MayanDate & ) const;
    bool              operator!=( const MayanDate & m ) const;
    void              get_string( char *, unsigned int ) const;
    unsigned int      toDays();
    char*            toString();
    static MayanDate*  toMayan(unsigned int);
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
