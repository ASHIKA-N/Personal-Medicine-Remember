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

struct Med {
  string name;
  string dosage;
  Time t;
  int fpw;

  Med(const string& n,const string& d, int hour, int min,int f) {
    name = n;
    dosage = d;
    t.h = hour;
    t.m = min;
    if(f<1 || f>7)
      f=7;
    fpw=f;
  }

  void disp(){
    cout<<"Name:"<<name<<"\nDosage:"<<dosage<<"\nIntake ";
    t.disp();
    cout<<"Frequency per week:"<<fpw<<endl;
  }
};
  
