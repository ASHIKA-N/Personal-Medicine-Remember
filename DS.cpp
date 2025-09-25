#include <iostream>
using namespace std;
#include <cstdlib>

class Stack{
  int *a;
  int size;
void reallc(int i=1){
  a=(int*)realloc(a,(size+i)*sizeof(int));
  size+=i;
}
  public:
  Stack(int s=5){
    top=-1;
    size=s;
    a=new int[s];
  }
  void push(int v){
    if(top==size-1){
      reallc();
    }
    a[++top]=v;
  }
  int pop(){
    if(top==-1){
      cout<<"Stack Underflow";
      return -1;
    }
    return a[top--];
  }
  int peek(){
    if(top==-1){
      cout<<"Stack Underflow";
      return -1;
    }
    return a[top];
};

class Queue{
  int *a;
  int size;
  int front,rear;
  void reallc(int i=1){
    a=(int*)realloc(a,(size+i)*sizeof(int));
    size+=i;
  }
  public:
  Queue(int s=5){
    size=s;
    front=rear=-1;
    a=new int[s];
  }
  void enqueue(int v){
    if(front==(rear+1)%size){
      reallc();
      ;
    if(front==-1){
    ;
    };


    
    
    
