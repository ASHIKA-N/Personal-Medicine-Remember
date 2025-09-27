#include <string>
#include "Struct.hpp"
using namespace std;

struct Time{
  int h,m;
  int toMinutes() const {
    return h * 60 + m;
  }
};

struct med {
  string name;
  string dosage;
  Time t;
med(string& n,string& d, int hour, int min) {
    name = n;
    dosage = d;
    t.h = hour;
    t.m = min;
  }
};
  
