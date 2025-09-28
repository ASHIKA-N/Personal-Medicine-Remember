#include "../hppfolder/DS.hpp"
#include "med.hpp"
#include <string>

struct Date{
  int d,m,y;

  Date(int day, int month, int year) {
    if (isValid(day, month, year)) {
      d = day;
      m = month;
      y = year;
    } else {
      cout << "Invalid date! Setting default 1/1/2000\n";
      d = 1;
      m = 1;
      y = 2000;
    }
  }

  static bool isValid(int day, int month, int year) {
    if (year < 1) return false;
    if (month < 1 || month > 12) return false;

    int daysInMonth[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};

    bool leap = (year % 400 == 0) || (year % 100 != 0 && year % 4 == 0);
    if (leap) daysInMonth[2] = 29;

    if (day < 1 || day > daysInMonth[month]) return false;

    return true;
  }

  void print() {
    cout << d << "/" << m << "/" << y << "\n";
  }
};


