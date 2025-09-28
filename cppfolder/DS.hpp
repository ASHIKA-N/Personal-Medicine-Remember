#include <iostream>
#include <vector>
#include "../hppfolder/Struct.hpp"
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
  Node* next,*prev;
  Node(Med m) : data(m), next(nullptr), prev(nullptr) {}
};
  
/*
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


    
    
    
