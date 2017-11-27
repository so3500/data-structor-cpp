#include<iostream>
#include<string>
using namespace std;

class Node{
public:
     Node *next; 
     string txt;
};

class S_LinkedList{
public:
     S_LinkedList(){
          tempPoint = NULL;
          e_num = 0;
     }

     Node* deleteFromHead(){
          tempPoint = top;
          top = top->next;
          tempPoint->next = NULL;
          e_num--;
          return tempPoint;
     }

     void insertToHead(Node* E){
          tempPoint = E;
          tempPoint->next = top;
          top = tempPoint;
          e_num++;
     }

     bool isEmpty(){
          if (top == NULL){
               return true;
          }
          else{
               return false;
          }
     }

     int size_(){
          return e_num;
     }

     void printAll(){
          tempPoint = top;
          while (tempPoint != NULL){
               cout << tempPoint->txt << "  ";
               tempPoint = tempPoint->next;
          }
     }


private:
     Node *tempPoint;
     Node *top;
     int e_num;
};

class Stack_LinkedList{
public:
     void push(Node *N){
          l_list.insertToHead(N);
     }
     void pop(){
          l_list.deleteFromHead();
     }
     void isEmpty(){
          cout << l_list.isEmpty() << endl;
     }
     void size_(){
          cout << l_list.size_() << endl;
     }
     void printAll(){
          l_list.printAll();
     }

private:
     S_LinkedList l_list;

};

int main(){
     Stack_LinkedList stack_;
     Node *E;
     bool goStop = true;
     int a = 0;
     string inputName;
     while (goStop){
          cout << "메뉴입력 1.push  2.pop 3.size 4.empty 5.printAll 6. 그만 " << endl;
          cin >> a;
          switch (a){
          case 1:
               E = new Node();
               cout << "문자 입력 : ";
               cin >> inputName;
               E->txt = inputName;
               stack_.push(E);
               break;
          case 2:
               stack_.pop();
               cout << endl;
               break;
          case 3:
               stack_.size_();
               break;
          case 4:
               stack_.isEmpty();
               break;
          case 5:
               stack_.printAll();
               break;
          case 6:
               goStop = false;
               break;
          }
     }

     return 0;
}