#include<iostream>
#include<iomanip>
#include<string>
using namespace std;

int mod(int x, int m);

class Element{
public:
     string name;
};

class Element1{
public:
     int name;
     char n;
     int a;
     char b;
     long c;

};

typedef Element * ePtr;

// 환형배열은 따로 클래스로 구현하지 않고, 일반 배열을 환형처럼 연산하도록 하는것
class Vector_CircularArray{
public:
     Vector_CircularArray(int N){
          numOfElement = 0;
          index_front = 0;
          count = 1;
          eArray = new Element[N];
          sizeOfArray = N;
     }
     ~Vector_CircularArray(){
          delete []eArray;
     }
     Element elementAtRank(int r) throw(const char*);
     void replaceAtRank(int r, Element E) throw(const char*);
     void insertAtRank(int r, Element E) throw(const char*);
     void removeAtRank(int r) throw(const char*);
     int size();
     bool isEmpty();
     ePtr eArray;
private:
     int count;
     int index_front;               // 가장 앞 요소의 인덱스
     int index_rear;                // 가장 뒤 요소의 인덱스
     int numOfElement;              // 배열 안에 있는 요소의 개수
     int sizeOfArray;               // 배열의 크기
};

int main(){
     Vector_CircularArray mVector_CircularArray(30);
     Element tempE;
     char str = 'a';
     try{
          for (int i = 0; i < 30; i++){
               Element mE;
               mE.name = str + i;
               mVector_CircularArray.insertAtRank(i, mE);
          }
          // 나열
          for (int k = 0; k < 30; k++){
               tempE = mVector_CircularArray.elementAtRank(k);
               cout << tempE.name << setw(5);
          }
          cout << endl << "============" << endl;
          // 6번째 요소(앞에 5개의 요소가 있는 자리) 출력
          tempE = mVector_CircularArray.elementAtRank(5);
          cout << tempE.name << setw(5);
          cout << endl << "============" << endl;

          // 4번째 요소 삭제, rank는 index와 같다. 단 이 index는 순서의 개념을 포함한 index
          mVector_CircularArray.removeAtRank(3);
          // 나열
          for (int k = 0; k < 30; k++){
               tempE = mVector_CircularArray.elementAtRank(k);
               cout << tempE.name << setw(5);
          }
          cout << endl << "============" << endl;
          //

          Element tempE2;
          tempE2.name = "!";
          mVector_CircularArray.insertAtRank(0, tempE2);

          // 나열
          for (int k = 0; k < 30; k++){
               tempE = mVector_CircularArray.elementAtRank(k);
               cout << tempE.name << setw(5);
          }
          cout << endl << "============" << endl;
          //
          mVector_CircularArray.insertAtRank(0, tempE2);
          mVector_CircularArray.insertAtRank(0, tempE2);

          // 나열
          for (int k = 0; k < 30; k++){
               tempE = mVector_CircularArray.elementAtRank(k);
               cout << tempE.name << setw(5);
          }
          cout << endl << "============" << endl;
     }
     catch (char* message){
          cout << message << endl;
     }

}

Element Vector_CircularArray::elementAtRank(int r) throw(const char*) {
     if (size() == 0)
          throw "there is no Element";
     else if (r > size())
          throw ("해당 rank에 해당하는 요소가 없습니다.");
     int tempI = mod(r + count, sizeOfArray);
     return eArray[tempI];
}

void Vector_CircularArray::replaceAtRank(int r, Element E) throw(const char*) {
     // 배열의 크기를 넘어서는 접근을 할 경우
     if (numOfElement == sizeOfArray)
          throw "array overflow";
     
     cout << "기존의 요소 : " << eArray[r + count].name << endl;
     eArray[r + count] = E;
     cout << "새로운 요소 : " << eArray[r + count].name << endl << "====" << endl;


}

void Vector_CircularArray::insertAtRank(int r, Element E) throw(const char*) {
     // 배열의 용량을 초과할 경우, 기존 배열보다 크기가 2배인 배열 생성
     if (size() == sizeOfArray){
          
          Element *tempArray = new Element[2 * sizeOfArray];
          for (int i = 0; i < sizeOfArray; i++){
               tempArray[i] = eArray[i];
          }
          sizeOfArray = 2 * sizeOfArray;
          delete[] eArray;
          cout << &eArray << " " << &tempArray << endl;
          *eArray = *tempArray;                              // 주소 바꿔치기======================이렇게 하니까 됨
          cout << &eArray << " " << &tempArray << endl;
          delete []tempArray;                                // 기존의 배열 삭제
          count = 0;                                         // count 초기화. 새로운 배열에 맞는 count

          cout << "배열 길이 2배로 증가, 배열길이는 : " << sizeOfArray;
     }
     // 맨 앞에 추가할 경우(상수시간 소요)
     if (r == 0){
          count--;
          int tempInt = mod(r + count, sizeOfArray);
          eArray[tempInt] = E;                               // 마지막에 여기서 오류.............
          numOfElement++;
          return;
     }
     
     if (r >= size()){ // 맨 뒤에 추가
          //cout << "현재 요소의 개수는" << size() << "개 이고, " << size() + 1 << "번째 자리에 추가하겠음" << endl;
          eArray[(size())%sizeOfArray] = E;
          numOfElement++;
          return;
     } 

     // 중간에 추가할 경우. k는 index이므로 count로 조정
     for (int k = (size() + count) % sizeOfArray; k > r + count; k = (k - 1) % sizeOfArray){
          eArray[k % sizeOfArray] = eArray[(k - 1) % sizeOfArray];
     }
     eArray[r + count] = E;
     numOfElement++;

     


}

void Vector_CircularArray::removeAtRank(int r) throw(const char*) {
     if (size() == 0)
          throw ("there is already no Element");
     else if (r > numOfElement)
          throw ("rank r does no exist");

     for (int k = (r + count) % sizeOfArray; k < size() + count - 1; k = (k + 1) % sizeOfArray) { // 기존의 마지막 요소 앞 index까지만
          eArray[k % sizeOfArray] = eArray[(k + 1) % sizeOfArray];
          //if (k = size() + count - 1)
          //     eArray[(k + 1) % sizeOfArray];
          // 포인터 배열이면 delete해주면 되는데...
     }

     numOfElement--;
}

int Vector_CircularArray::size() {
     return numOfElement;
}

bool Vector_CircularArray::isEmpty() {
     return size() == 0; // 요소의 개수가 0이면 비어있다.
}

int mod(int x, int m) {
     int r = x%m;
     return r<0 ? r + m : r;
}