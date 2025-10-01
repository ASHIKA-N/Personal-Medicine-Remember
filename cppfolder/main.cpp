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
cout<<"1.Alter medicine\n";
cout<<"2.Alter medicine time\n";
cout<<"3.Alter medicine and time\n";

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
        getline(cin,old_med);
        cout<<"Enter new medicine name: ";
        getline(cin,new_med);
        string res=rename(old_med.c_str(),new_med.c_str());
          break;
        case 2:
          string med_name,date_time;
          time_t upd_time;
          struct tm tmStruct={};
          cout<<"Enter medicine name: \n";
          cin>>med_name;
          cout<<"Enter medicine time: \n";
          getline(cin,date_ime);
          strptime(date_time.c_str(),"%Y-%m-%d %H:%M:%S",&tmStruct);
          upd_time=mktime(&tmStruct);
          break;
          case 3:
          string ol_med,ne_med;
        cout<<"Enter old medicine name : ";
        getline(cin,ol_med);
        cout<<"Enter new medicine name: ";
        getline(cin,ne_med);
        string resu=rename(ol_med.c_str(),ne_med.c_str());
        string dat_time;
          time_t up_time;
          struct tm tmStruct={};
          cout<<"Enter medicine time: \n";
          getline(cin,dat_ime);
          strptime(dat_time.c_str(),"%Y-%m-%d %H:%M:%S",&tmStruct);
          up_time=mktime(&tmStruct);
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
