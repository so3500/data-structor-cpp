#include<iostream>
#include<string>
using namespace std;

class Element{
public:
     string name;

     Element(){
          name = "";
     }
};
class Stack{
public:
     Stack(){
          topPos = 0;
          
     }
     // t �� ä���� �� �� ���� ����Ŵ, 
     // insert(push)
     void push(Element *e){
          // if t-1 = array.size() then throw StackFull
          array[topPos] = e;
          topPos++;
          cout << "topPos : " << topPos << endl;
     }
     // delete(pop)
     void pop(){
          topPos--; // ä���� �� ���� ����Ŵ
          cout << "topPos : " << topPos << endl;
     }
     // top
     Element* top(){
          // if empty() then StackEmpty ����!
          return array[topPos-1];
     }
     // empty
     bool empty(){
          if (topPos >= 0){
               cout << "����" << endl;
               return false;
          }
          else {
               cout << "����" << endl;
               return true;
          }
     }
     // size
     int size() const{
          return topPos;
     }
     // print
     void printAll() {
          int tempPos = topPos;
          while(topPos > 0){
               topPos--;
               Element *tempEle = array[topPos];
               cout << tempEle->name << " " << " " << endl;
               
          }
          topPos = tempPos;
     }
private:
     int topPos;
     Element *array[20];
};



int main(){

     Stack mStack;
     string inputName = "";
     Element *tempEle;
     Element *mEle;
     bool goStop = true;
     int a = 0;
     while (goStop){
          cout << "�޴��Է� 1.push  2.pop 3.size 4.empty 5.printAll 6. �׸� " << endl;
          cin >> a;
          switch (a){
          case 1:
               mEle = new Element();
               cout << "���� �Է� : ";
               cin >> inputName;
               
               mEle->name = inputName;
               mStack.push(mEle);
               break;
          case 2:
               tempEle = mStack.top();
               mStack.pop();
               cout << "name of poped element : " << tempEle->name << endl;
               break;
          case 3:
               int sizeNum;
               sizeNum = mStack.size();
               cout << "sizeNum : " << sizeNum << endl;
               break;
          case 4:
               mStack.empty();
               break;
          case 5:
               mStack.printAll();
               break;
          case 6:  
               goStop = false;
               break;
          }

     }


     return 0;
}