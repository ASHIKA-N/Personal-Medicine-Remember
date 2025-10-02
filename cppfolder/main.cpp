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

int main(){
  int ch;
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
      while(1){
        string op;
        int h,m;
        string old_med,new_med;
        cout<<"Enter old medicine name : ";
        cin.ignore();
        getline(cin,old_name);
        if(!L.find(old_med)){
          cout<<"Medicine not found";
          break;
        }
        cout<<"Do you want to change medicine name(yes/no): ";
        cin.ignore();
        getline(cin,op);
        if(op=="yes"){
        cout<<"Enter new medicine name: ";
        getline(cin,new_med);
        L.altermed_name(old_med,new_med);
        }
        
          
          cout<<"Do you want to change medicine time(yes/no): ";
          cin>>op;
          if(op=="yes"){
          cout<<"Enter medicine time: \n";
          cout<<"Enter hour: ";
          cin>>h;
          cout<<"Enter min: ";
          cin>>m;
          te.Time(h,m);
          L.altermed_time(old_name,h,m);
        }

}
 cout<<"Do you want to change dosage amount(yes/no): ";
        cin.ignore();
        cin>>op;
        if(op=="yes"){
        cout<<"Enter  dosage amount: ";
        cin.ignore();
        getline(cin,dosag);
        L.altermed_dosage(old_name,dosag);
      }
      cout<<"Do you want to change number of days in a week(yes/no): ";
        cin.ignore();
        cin>>op;
        if(op=="yes"){
        cout<<"Enter number of days: ";
        cin>>fpw;
        L.altermed_days(old_name,fpw);
      }
      cout<<"Do u want to alter other medicine(yes/no):";
      cin>>op;
      if(op=="no"){
          break;
        }
    }
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
