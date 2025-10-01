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
      return;
    }
    for (Node* n : hash[name]) {
      cout << "Found: " << n->a.name
           << " | Dosage: " << n->a.dosage
           << " | Time: " << n->a.t.h << ":" << n->a.t.m
           << " | Freq/week: " << n->a.fpw << endl;
    }
  }
};


    
    
    
