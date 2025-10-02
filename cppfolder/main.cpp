#include <iostream>
#include <cstdio>

#include "../include/DS.hpp"
#include "../include/Struct.hpp"

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
  cout<<"3.Alter Dosage\n";
  cout<<"4.Alter medicine and medicine time\n";
  cout<<"5.Alter medcine and dosage\n";
  cout<<"6.Alter medicine time and dosage\n";
  cout<<"7.Alter medicine , medicine time and dosage\n";
}

int main(){
  int ch,ch1;
  LinkedList L;
  Queue SC;
  Time t;
  Med m;
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
        cin.ignore();
        getline(cin,old_med);
        if(!L.find(old_med)){
          cout<<"Medicine not found";
          break;
        }
        cout<<"Enter new medicine name: ";
        getline(cin,new_med);
        L.altermed_name(old_med,new_med);
        break;
        case 2:
        string med_name;
        int h,m;
          
        cout<<"Enter medicine name: \n";
        cin.ignore();
        getline(cin,med_name);
        if(!L.find(med_name)){
          cout<<"Medicine not found";
          break;
        }
        cout<<"Enter medicine time: \n";
        cout<<"Enter hour: ";
          cin>>h;
          cout<<"Enter min: ";
          cin>>m;
          t.Time(h,m);
          L.altermed_time(med_name,h,m);
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
