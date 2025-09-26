#include <iostream>
using namespace std;
#include <cstdlib>

class Stack{
  int *a,size,top;
void reallc(int i=1){
  int *temp=new int[size+i];
  for(int in=0;in<size;in++)
    temp[i]=a[i];
  delete[] a;
  a=temp;
  size+=i;
}
  public:
  Stack(int s=5){
    top=-1;
    size=s;
    a=new int[s];
  }
  ~Stack(){
    delete[] a;
  }
  void push(int v){
    if(isFull())
      reallc(size);
    a[++top]=v;
  }
  int pop(){
    if(isEmpty()){
      cout<<"Stack Underflow";
      return -1;
    }
    return a[top--];
  }
  int peek(){
    if(isEmpty()){
      cout<<"Stack Underflow";
      return -1;
    }
    return a[top];
  }
  bool isFull(){
    return top==size-1;
  }

  bool isEmpty(){
    return top==-1;
  }
};

class Queue{
  int *a;
  int size;
  int front,rear,count;
  void reallc(int i=1){
    int *temp=new int[size+i];
    for(int in=0;in<size;in++)
      temp[i]=a[i];
    delete[] a;
    a=temp;
    size+=i;
  }
  public:
  Queue(int s=5){
    count=0;
    size=s;
    front=rear=-1;
    a=new int[size];
  }
  ~Queue(){
    delete[] a;
  }
  void enqueue(int v){
    if(isFull())
      reallc(size);
    a[++rear]=v;
    if(isEmpty())
      ++front;
  }
  void deque(){
    if(isEmpty()){
      cout<<"Queue Underflow";
      return -1;
    }
    if(front==rear) rear=-1;
    int v=a[front++];
    if(rear==-1) front=-1;
    return v;
  }
  int peek(){
    if(isEmpty()){
      cout<<"Stack Underflow";
      return -1;
    }
    return a[front];
  }
      
  bool isFull(){
    return front==(rear+1)%size;
  }

  bool isEmpty(){
    return front==-1;
  }
class Node{
public:
int data;
Node* next;
Node* prev;
};
class linkedlist{
  private:
Node *head;
public:
linkedlist(){
  head=NULL;
}
Node* insert(int val){
  Node* new_node=(Node*)malloc((sizeof(Node));
  new_node->data=val;
  new_node->next=NULL;
  if(head==NULL){
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
   
};


    
    
    
