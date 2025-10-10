#include <iostream>
#include "../hppfolder/DS.hpp"
#include "../hppfolder/Expiry.hpp"
#include "../hppfolder/Queue.hpp"
#include "../hppfolder/Stack.hpp"
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
  cout<<"7.Undo Last Operation\n";
  cout<<"8.Redo Last Undone Operation\n";
  cout<<"9.Exit\n";
}

int main(){
  int ch;
  LinkedList L;
  Queue todayQueue;
  Stack undo,redo;
  do{
    menu();
    cin>>ch;
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
      L.altermed();
      break;
      case 6:
      string ns;
      cout << "Enter Name to Search: ";
      cin.ignore();
      getline(cin, ns);
      L.search(ns); 
      break;
      case 7:
      break;
      case 8:
      break;
      case 9:
      int e;
      cout<<"\n---Expiry Check before Exit---\n";
      cout<<"Enter no. of days to remind before expiry:";
      cin>>e;
      while(e<0){
        cout<<"Cant be negative.Enter Again;";
        cin>>e;
      }
      expiry(&L,e);
      cout<<"Exiting\n";
      break;
      default:
      cout<<"Invalid Choice, Try Again";
    }
  }while(ch!=9);
  Queue todayQ = buildTodayQueue(L);
  reminderCheck(todayQ);
  return 0;
}