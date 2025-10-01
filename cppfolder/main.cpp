#include <iostream>
#include <cstdio>
#include<ctime>
#include "../include/DS.hpp"
using namespace std;

void menu(){
  cout<<"\n===Personal Medication Reminder===\n";
  cout<<"Choices\n";
  cout<<"1.View Med Schedule\n";
  cout<<"2.Insert New Med\n";
  cout<<"3.Delete a Med by Name and Time\n";
  cout<<"4.Delete all Meds of a Particular Name\n";
  cout<<"5.Alter a Med\n";
  cout<<"6.Search for a Med\n";
  cout<<"7.Exit\n";
}
void altermed(){
cout<<"Choices\n";
cout<<"1.Change medicine\n";
cout<<"2.Change medicine time\n";
}
int main(){
  int ch,ch1;
  LinkedList L;
  while(1){
    menu();
    cin<<ch;
    switch(ch){
      case 1:
      L.disp();
      break;
      case 2:
      L.insert();
      break;
      case 3:
      string n;
      Time te;
      cout<<"Enter Name and Time(H M):";
      cin.ignore();
      getline(cin,n);
      cin>>te.h>>te.m;
      L.del(n,te);
      break;
      case 4:
      string na;
      cout<<"Enter Name:";
      cin.ignore();
      getline(cin,na);
      L.delAll(na);
      break;
      case 5:
        altermed();
        cin>>ch1;
        switch(ch1){
        case 1:
        string old_med,new_med;
        cout<<"Enter old medicine name : ";
        cin>>old_med;
        cout<<"Enter new medicine name: ";
        cin>>new_med;
        string res=rename(old_med.c_str(),new_med.c_str());
          break;
        case 2:
          string med;
          time_t upd_time;
          cout<<"Enter medicine name: \n";
          cin>>med_name;
          cout<<"Enter medicine time: \n";
          cin>>upd_time;
          break;
        }
      break;
      case 6:
      string ns;
      cout << "Enter Name to Search: ";
      cin.ignore();
      getline(cin, ns);
      L.search(ns);     
      break;
      case 7:
      return 0;
      default:
      cout<<"Invalid Choice, Try Again";
    }
  }
}
