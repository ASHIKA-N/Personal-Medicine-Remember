#include "med.hpp"
#include <string>
#include <queue>

struct date{
  int d,m,y;
};

struct time{
  int h,m;
};

class med{
  string name;
  int qty;
  struct date exp;
  struct time* freq;
  public:
  med(){
    name='';
    qty=0;
}
