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
      return {"", "", {0, 0}};
    }
    Med v=a.back();
    a.pop_back();
    return v;
  }

  Med peek(){
    if(isEmpty()){
      cout<<"Stack Underflow\n";
      return {"", "", {0, 0}};
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
      return {"", "", {0, 0}};
    }
    Med v=a.front();
    a.erase(a.begin());
    return v;
  }

  Med peek(){
    if(isEmpty()){
      cout<<"Queue Underflow\n";
      return {"", "", {0, 0}};
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
    cout << "Frequency per week: ";
    cin >> t->a.fpw;
    t->next = nullptr;
    if (head == nullptr) {
      head = t;   
    } else {
      Node* r = head;
      while (r->next != nullptr) {
        r = r->next;
      }
      r->next = t;  
    }
  }

  void display() {
    Node* r = head;
    if (!r) {
      cout << "No medicines in the list.\n";
      return;
    }
    while (r != nullptr) {
      cout << "Name: " << r->a.name
             << ", Dosage: " << r->a.dosage
             << ", Time: " << r->a.t.h << ":" << r->a.t.m
             << ", FPW: " << r->a.fpw << "\n";
      r = r->next;
    }
  }
};


    
    
    
