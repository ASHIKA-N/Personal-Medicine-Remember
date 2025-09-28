
#include <iostream>
#include <vector>
#include "Struct.hpp"
using namespace std;
#include <string>

class Stack{
  vector<med> a;
  public:
  Stack(int s=0){
    if(s>0) a.reserve(s);
  }

  void push(med v){
    a.push_back(v);
  }

  med pop(){
    if(isEmpty()){
      cout<<"Stack Underflow\n";
      return {"", "", {0, 0}};
    }
    med v=a.back();
    a.pop_back();
    return v;
  }

  med peek(){
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
  vector<med> a;
  public:
  Queue(int s=0){
    if(s>0) a.reserve(s);
  }

  void enqueue(med v){
    a.push_back(v);
  }

  med dequeue(){
    if(isEmpty()){
      cout<<"Queue Underflow\n";
      return {"", "", {0, 0}};
    }
    med v=a.front();
    a.erase(a.begin());
    return v;
  }

  med peek(){
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

/* typedef struct Node{
   med a;
  struct Node* next,*prev;
  struct Node(med m) : data(m), next(nullptr), prev(nullptr) {}
}Node;
  
 
 class doublylinkedlist{
  private:
Node *head;
public:
doublylinkedlist():head(nullptr){};
Node* insert(int val){
  Node* new_node=(Node*)malloc((sizeof(Node));
  new_node->data=val;
  new_node->next=NULL;
  if(head==nullptr){
    return new_node;
  }
  Node* temp=head;
  while(temp!=NULL){
    temp=temp->next;
  }
  temp->next=new_node;
  return head;
}
void display(Node* head){
  if(head==NULL){
    return ;
  }
  while(head!=NULL){
  cout<<head->data<<"\t";
  head=head->next;
  }
}
   
}; */


    
    
    
