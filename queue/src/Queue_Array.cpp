#include<iostream>
#include<string>
#include<iomanip>
using namespace std;

class Element{
public:
     string name;
     int num;
};

class Queue_Array{
public:
     Queue_Array(){
          index_front = 0;
          index_rear = 0;
          n = 0;
          N = 30;
     }
     void enqueue(Element E);
          void dequeue() throw(const char*);
          Element front() throw(const char*);
          int size();
          bool isEmpty();
          void printAll();

private:
     Element eArray[30];
     int index_front; // 가장 앞 요소의 인덱스
     int index_rear;  // 가장 뒤 요소의 인덱스
     int n;           // 큐 안에 있는 요소의 개수
     int N;           // 배열의 크기
     Element *pE;
};


int main(){
     bool goStop = true;
     int menuNum = 0;
     Queue_Array mQueue;
     Element tempE;
     while (goStop){
          cout << "메뉴를 입력하세요" << endl;
          cout << "1.enqueue" << setw(5) << "  2.dequeue" << setw(5) << "  3.isEmpty" << setw(5) << "  4.size" << setw(5) << "  5.printAll" << setw(5) << "  6.Exit" << endl;
          cin >> menuNum;
          try{
               switch (menuNum){

               case 1:
                    cout << "이름입력 : ";
                    cin >> tempE.name;
                    mQueue.enqueue(tempE);
                    break;
               case 2:
                    mQueue.dequeue();
                    break;
               case 3:
                    cout << mQueue.isEmpty() << endl;
                    break;
               case 4:
                    cout << mQueue.size() << endl;
                    break;
               case 5:
                    mQueue.printAll();
                    break;
               case 6:
                    goStop = false;
                    break;

               }
          }
          catch (const char* ab){
               cout << ab << endl;
          }
     }



     return 0;
}

void Queue_Array::enqueue(Element E){
     if (size() == N)
          //throw "QueueFullExeption";
          throw 1;

     eArray[index_rear] = E;
     index_rear = (index_rear+1)%N;
     n++;

}

void Queue_Array::dequeue() throw(const char*){
     if (isEmpty() == true)
          throw "QueueEmpty";

     index_front = (index_front+1)%N;
     n--;

}

Element Queue_Array::front() throw(const char*){
     if (isEmpty() == true)
          throw "QueueEmpty";

     return eArray[index_front];
}

int Queue_Array::size(){
     return n;
}

bool Queue_Array::isEmpty(){
     if (n != 0){
          return false;
     }
     else{
          return true;
     }
}

void Queue_Array::printAll(){
     int index_temp = index_front;
     while (index_front != (index_rear+1)%N){
          cout << eArray[index_front].name << " / " << &eArray[index_front] << setw(5);
          index_front = (index_front + 1) % N;
          
     }
     cout << endl;
     index_front = index_temp;
}