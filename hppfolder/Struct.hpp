#pragma once
#include <iostream>
#include <string>
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

struct Med {
  string name;
  string dosage;
  Time t;
  Date exp;
  int fpw;

  Med(const string& n,const string& d, int hour, int min,int f,int a,int b,int c) {
    name = n;
    dosage = d;
    t.h = hour;
    t.m = min;
    if(f<1 || f>7)
      f=7;
    fpw=f;
    if(!Date::isValid(a,b,c)){
      a=1;
      b=1;
      c=200;
    }
    exp.d=a;
    exp.m=b;
    exp.y=c;
  }

  void disp(){
    cout<<"Name:"<<name<<"\nDosage:"<<dosage<<"\nIntake ";
    t.disp();
    cout<<"Frequency per week:"<<fpw<<endl;
  }
};
  
