#include <iostream>
#include "../include/DS.hpp"
using namespace std;

void menu(){
  cout<<"\n===Personal Medication Reminder===\n";
  cout<<"Choices\n";
  cout<<"1.View Med Schedule\n";
  cout<<"2.Insert New Med\n";
  cout<<"3.Delete a Med\n";
  cout<<"4.Alter a Med\n";
  cout<<"5.Search for a Med\n";
  cout<<"6.Exit\n";
}

int main(){
  int ch;
  while(1){
    menu();
    cin<<ch;
    switch(ch){
      case 1:
      break;
      case 2:
      break;
      case 3:
      break;
      case 4:
      break;
      case 5:
      break;
      case 6:
      return 0;
      default:
      cout<<"Invalid Choice, Try Again";
    }
  }
}
