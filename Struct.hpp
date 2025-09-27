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

  med(string& n,string& d, int h, int m) {
    name = n;
    dosage = d;
    t.h = h;
    t.m = m;
  }
};
  
