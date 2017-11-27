#include<iostream>
#include<iomanip>
#include<string>
using namespace std;

class Node{
public:
     Node *next;
     string txt;
};

class Queue_LinkedList{
public:

     void enqueue(const Node *E);
     void dequeue();
     Node front();
     bool isEmpty();
     void listSize();

private:
     Node *tempPoint;
     Node *frontPoint;
     Node *rearPoint;
};




int main(){


     return 0;
}