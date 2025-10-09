#include <iostream>
#include <string>
#include <vector>
#include <chrono>
using namespace std;

struct Time{
  int h,m;

  Time(int hour = 0, int min = 0) {
    if (hour >= 0 && hour < 24) h = hour;
    else {
      cout << "Invalid hour! Setting to 0.\n";
      h = 0;
    }
    if (min >= 0 && min < 60) m = min;
    else {
      cout << "Invalid minute! Setting to 0.\n";
      m = 0;
    }
  }

  int toMinutes() const {
    return h * 60 + m;
  }

  void disp(){
    cout<<"Time:"<<h<<":"<<m<<endl;
  }

  bool operator<(const Time& other) const {
    return toMinutes() < other.toMinutes();
  }
};

struct Date{
  int d,m,y;

  Date(int day=1, int month=1, int year=2000) {
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

  int operator -(const Date &dt){
    using namespace std::chrono;
    sys_days thisDate = year_month_day{year{y}, month{m}, day{d}};
    sys_days otherDate = year_month_day{year{dt.y}, month{dt.m}, day{dt.d}};
    auto diff = thisDate - otherDate;
    return diff.count();
  } 
};

struct Med {
  string name;
  string dosage;
  Time t;
  Date exp;
  vector<int> dy;

  Med() {
    name = "";
    dosage = "";
    t = {0, 0};
    exp = {1, 1, 2000};
    dy = {};
  }

  Med(const string& n,const string& d, int hour, int min,vector<int> f,int a,int b,int c) {
    name = n;
    dosage = d;
    t.h = hour;
    t.m = min;
    if (f.empty()) f = {1,2,3,4,5,6,7};
    dy=f;
    if(!Date::isValid(a,b,c)){
      a=1;
      b=1;
      c=2000;
    }
    exp.d=a;
    exp.m=b;
    exp.y=c;
  }

  void disp(){
	cout<<"Name:"<<name<<"\nDosage:"<<dosage<<"\nIntake ";
    t.disp();
    cout << "\nDays to consume: ";
	for (int d : dy) cout << d << " ";
	cout << "\nExpiry Date: "; exp.print();
  }
};

 /*struct Action{
  char act;
  int Npos;
  Med OV;
  Med NV;

  Action(){
    act='n';
    Npos=-1;
    OV=Med();
    NV=Med();
  }
}; */
  
