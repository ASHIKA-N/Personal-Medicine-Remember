#include <iostream>
#include <vector>
#include "Struct.hpp"
#include <string>
using namespace std;

class Stack{
  vector<Med> a;
  public:
  Stack(int s=0){
    if(s>0) a.reserve(s);
  }

  void push(Med v){
    a.push_back(v);
  }

  Med pop(){
    if(isEmpty()){
      cout<<"Stack Underflow\n";
      return {"", "", {0, 0},{0,0,0},0};
    }
    Med v=a.back();
    a.pop_back();
    return v;
  }

  Med peek(){
    if(isEmpty()){
      cout<<"Stack Underflow\n";
      return {"", "", {0, 0},{0,0,0},0};
    }
    return a.back();
  }

  bool isEmpty(){
    return size()==0;
  }

  int size(){
    return a.size();
  }
};

class Queue{
  vector<Med> a;
  public:
  Queue(int s=0){
    if(s>0) a.reserve(s);
  }

  void enqueue(Med v){
    a.push_back(v);
  }

  Med dequeue(){
    if(isEmpty()){
      cout<<"Queue Underflow\n";
      return {"", "", {0, 0},{0,0,0},0};
    }
    Med v=a.front();
    a.erase(a.begin());
    return v;
  }

  Med peek(){
    if(isEmpty()){
      cout<<"Queue Underflow\n";
      return {"", "", {0, 0},{0,0,0},0};
    }
    return a.front();
  }

  bool isEmpty(){
    return size()==0;
  }

  int size(){
    return a.size();
  }
};

struct Node{
  Med a;
  Node *next;
};

struct LinkedList {
  Node* head;
  unordered_map<string, vector<Node*>> hash;

  LinkedList() { head = nullptr; } 

  void insert() {
    Node* t = new Node;
    cin.ignore();
    cout << "Enter Name: ";
    getline(cin, t->a.name);
    cout << "Enter Dosage: ";
    getline(cin, t->a.dosage);
    cout << "Time (HH MM): ";
    cin >> t->a.t.h >> t->a.t.m;
    cout<<"Expiry Date (DD MM YYYY):";
    cin>>t->a.exp.d>>t->a.exp.m>>t->a.exp.y;
    cout << "Frequency per week: ";
    cin >> t->a.fpw;
    t->next = nullptr;
    if (head == nullptr || t->a.t < head->a.t) {
      t->next=head;
      head=t;
      return;   
    }
    Node* r = head;
    while (r->next && !(t->a.t < r->next->a.t)) {
      r = r->next;
    }
    t->next = r->next;
    r->next = t;  
    hash[t->a.name].push_back(t);
  }

  void disp() {
    Node* r = head;
    if (!r) {
      cout << "No medicines in the list.\n";
      return;
    }
    while (r != nullptr) {
      cout << "Name: " << r->a.name
             << ", Dosage: " << r->a.dosage
             << ", Time: ";
      r->a.t.disp();

      cout<<", Expiry Date: ";
      r->a.exp.print();
      cout<< ", FPW: " << r->a.fpw << "\n";
      r = r->next;
    }
  }

  void del(const string& medName, const Time& t) {
    if (!head) {
      cout << "List is empty!\n";
      return;
    }

    if (head->a.name == medName && !(t < head->a.t) && !(head->a.t < t)) {
      Node* temp = head;
      head = head->next;
      delete temp;
      cout << medName << " at ";
      t.disp();
      cout << " deleted.\n";
      return;
    }

    Node* r = head;
    while (r->next && !(r->next->a.name == medName &&
           !(t < r->next->a.t) && !(r->next->a.t < t))) {
      r = r->next;
    }

    if (r->next) {
      Node* temp = r->next;
      r->next = r->next->next;
      delete temp;
      cout << medName << " at ";
      t.disp();
      cout << " deleted.\n";
    } else {
      cout << medName << " at ";
      t.disp();
      cout << " not found.\n";
    }
  }

    void delAll(const string& medName) {
    while (head && head->a.name == medName) {
      Node* temp = head;
      head = head->next;
      delete temp;
    }

    Node* r = head;
    while (r && r->next) {
      if (r->next->a.name == medName) {
        Node* temp = r->next;
        r->next = r->next->next;
        delete temp;
      } else {
        r = r->next;
      }
    }
  }

  void search(const string& name) {
    if (hash.find(name) == hash.end()) {
      cout << "No medicine named \"" << name << "\" found.\n";
      return ;
    }
    for (Node* n : hash[name]) {
      cout << "Found: " << n->a.name
           << " | Dosage: " << n->a.dosage
           << " | Time: " << n->a.t.h << ":" << n->a.t.m
           << " | Expiry Date: "<<n->a.exp.d<<"/"<<n->a.exp.m<<"/"<<n->a.exp.y
           << " | Freq/week: " << n->a.fpw << endl;
    }
  }
  bool find(const string& name){
    if (hash.find(name) == hash.end()) {
      cout << "No medicine named \"" << name << "\" found.\n";
      return false ;
    }
    else{
      return true;
    }
  }
  Node* findmed_name(const string& name){
    Node *r= head;
    if(!r){
      return head;
    }
    
    while(r!=nullptr ){
      if(r->a.name!=name){
        return r;
      }
      r=r->next;
    }
    
  }
void altermed(){
  while(1){
    char op;
    string old_med,new_med;
    cout<<"Enter old medicine name : ";
    cin.ignore();
    getline(cin,old_name);
    if(!L.find(old_med)){
      cout<<"Medicine not found";
      break;
    }
    cout<<"Do you want to change medicine name(y/n): ";
    cin>>op;
    if(op=='y' || op=='Y'){
      cout<<"Enter new medicine name: ";
      getline(cin,new_med);
      L.altermed_name(old_med,new_med);
    }
    cout<<"Do you want to change medicine time(y/n): ";
    cin>>op;
    if(op=='y' || op=='Y'){
      int h,m;
      cout<<"Enter medicine time: \n";
      cout<<"Enter hour: ";
      cin>>h;
      cout<<"Enter min: ";
      cin>>m;
      L.altermed_time(old_name,h,m);
    }
    cout<<"Do you want to change dosage amount(y/n): ";
    cin>>op;
    if(op=='y'|| op=='Y'){
      string dosag;
      cout<<"Enter dosage amount: ";
      cin.ignore();
      getline(cin,dosag);
      L.altermed_dosage(old_name,dosag);
    }
    /* cout<<"Do you want to change number of days in a week(yes/no): ";
    cin.ignore();
    cin>>op;
    if(op=="yes"){
      cout<<"Enter number of days: ";
      cin>>fpw;
      L.altermed_days(old_name,fpw);
    } */
    cout<<"Do u want to alter other medicine(y/n):";
    cin>>op;
    if(op!='y' || op!='Y')
      break;
  }
}

void altermed_name(const string& o_name,const string& n_name){
  if (hash.find(o_name) == hash.end()) {
    cout << "No medicine named \"" << o_name << "\" found.\n";
    return ;
  }
  for (Node* n : hash[o_name]) 
    n->a.name=n_name;
}

void altermed_time(const string& med_name,int hour,int min){
  char o;
  if (hash.find(med_name) == hash.end()) {
    cout << "No medicine named \"" << med_name << "\" found.\n";
    return ;
  }
  cout<<hash[med_name].size()<<" Meds found\n";
  for (Node* n : hash[med_name]){
    cout<<"Do you want to change this time? (y/n)\n";
    n->a.t.disp();
    cin>>o;
    if(o=='y' || o=='Y'){
      n->a.t.h=h;
      n->a.t.m=m;
      return;
    }
  }
}

void altermed_dosage(const string& med_name,const string& dos){
  char o;
  if (hash.find(med_name) == hash.end()) {
    cout << "No medicine named \"" << med_name << "\" found.\n";
    return ;
  }
  cout<<hash[med_name].size()<<" Meds found\n";
  for (Node* n : hash[med_name]){
    cout<<"Do you want to change this dosage? (y/n)\n";
    n->a.dosage;
    cin>>o;
    if(o=='y' || o=='Y')
      n->a.dosage=dos;
  }   
}

/* void altermed_days(const string& med_name,int days){
     Node *found=findmed_name(med_name);
    if(found!=nullptr){
    found->a.fpw=days;
    }
  } */
};


    
    
    
