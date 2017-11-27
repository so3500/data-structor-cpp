#ifndef _CIRCUlAR_ARRAY_H_
#define _CIRCUlAR_ARRAY_H_



#include<iostream>
#include<string>
#include<iomanip>
using namespace std;

class Element{
public:
     string name;
     int num;
};

class CircularArray{
public:
     CircularArray(){
          numOfElement = 0;
          sizeOfArray = 30;
     }
     //void insertRear(Element E) throw(const char*);
     //void deleteFront() throw(const char*);
     void insert(int i, Element E) throw(const char*);
     void remove(int i) throw(const char*);
     Element at(int i) throw(const char*);
     int size();
     bool isEmpty();
     void printAll();

private:
     Element eArray[30];
     int index_front; // ���� �� ����� �ε���
     int index_rear;  // ���� �� ����� �ε���
     int numOfElement;           // ť �ȿ� �ִ� ����� ����
     int sizeOfArray;           // �迭�� ũ��
     Element *pE;
};

/*
void CircularArray::insertRear(Element E) throw(const char*) {
     if (size() == N)
          throw "QueueFullExeption";

     eArray[index_rear] = E;
     index_rear = (index_rear + 1) % N;
     n++;

}

void CircularArray::deleteFront() throw(const char*){
     if (isEmpty() == true)
          throw "there is no Element";

     index_front = (index_front + 1) % N;
     n--;

}
*/

void CircularArray::insert(int i, Element E) throw(const char*){
     
}
void CircularArray::remove(int i) throw(const char*){

}

Element CircularArray::at(int i) throw(const char*){
     if (size() == 0 || i>size())
          throw "there is no Element";

     return eArray[ (index_front + i) % sizeOfArray ];
}

int CircularArray::size(){
     return numOfElement;
}

bool CircularArray::isEmpty(){
     if (numOfElement != 0){
          return false;
     }
     else{
          return true;
     }
}

void CircularArray::printAll(){
     int index_temp = index_front;
     while (index_front != (index_rear + 1) % N){
          cout << eArray[index_front].name << " / " << &eArray[index_front] << setw(5);
          index_front = (index_front + 1) % N;

     }
     cout << endl;
     index_front = index_temp;
}


#endif