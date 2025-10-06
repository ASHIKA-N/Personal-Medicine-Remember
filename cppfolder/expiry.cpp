#include <iostream>
#include "../hppfolder/DS.hpp"
using namespace std;

void expiry(LinkedList* L,int e){
  using namespace std::chrono;
  auto today = floor<days>(system_clock::now());
  year_month_day ymd{today};
  Date currentDate;
  currentDate.day   = static_cast<unsigned>(ymd.day());
  currentDate.month = static_cast<unsigned>(ymd.month());
  currentDate.year  = static_cast<int>(ymd.year());
  Node* n=L->head;
  while(n){
    if(n->a.exp-currentDate<=0){
      cout<<"\nMedicine expired and removed:\n";
      cout<<"Name:"<<n->a.name<<endl;
      n->a.t.disp();
      L->del(n->a.name,n->a.t);
    }
    else if(n->a.exp-currentDate<=e){
      cout<<"\nMedicine will expire in "<<e<<" days\n";
      cout<<"Name:"<<n->a.name<<endl;
      n->a.t.disp();
    }
    n=n->next;
  }
}

  


  
