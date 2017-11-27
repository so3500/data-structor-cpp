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

// ȯ���迭�� ���� Ŭ������ �������� �ʰ�, �Ϲ� �迭�� ȯ��ó�� �����ϵ��� �ϴ°�
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
     int index_front;               // ���� �� ����� �ε���
     int index_rear;                // ���� �� ����� �ε���
     int numOfElement;              // �迭 �ȿ� �ִ� ����� ����
     int sizeOfArray;               // �迭�� ũ��
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
          // ����
          for (int k = 0; k < 30; k++){
               tempE = mVector_CircularArray.elementAtRank(k);
               cout << tempE.name << setw(5);
          }
          cout << endl << "============" << endl;
          // 6��° ���(�տ� 5���� ��Ұ� �ִ� �ڸ�) ���
          tempE = mVector_CircularArray.elementAtRank(5);
          cout << tempE.name << setw(5);
          cout << endl << "============" << endl;

          // 4��° ��� ����, rank�� index�� ����. �� �� index�� ������ ������ ������ index
          mVector_CircularArray.removeAtRank(3);
          // ����
          for (int k = 0; k < 30; k++){
               tempE = mVector_CircularArray.elementAtRank(k);
               cout << tempE.name << setw(5);
          }
          cout << endl << "============" << endl;
          //

          Element tempE2;
          tempE2.name = "!";
          mVector_CircularArray.insertAtRank(0, tempE2);

          // ����
          for (int k = 0; k < 30; k++){
               tempE = mVector_CircularArray.elementAtRank(k);
               cout << tempE.name << setw(5);
          }
          cout << endl << "============" << endl;
          //
          mVector_CircularArray.insertAtRank(0, tempE2);
          mVector_CircularArray.insertAtRank(0, tempE2);

          // ����
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
          throw ("�ش� rank�� �ش��ϴ� ��Ұ� �����ϴ�.");
     int tempI = mod(r + count, sizeOfArray);
     return eArray[tempI];
}

void Vector_CircularArray::replaceAtRank(int r, Element E) throw(const char*) {
     // �迭�� ũ�⸦ �Ѿ�� ������ �� ���
     if (numOfElement == sizeOfArray)
          throw "array overflow";
     
     cout << "������ ��� : " << eArray[r + count].name << endl;
     eArray[r + count] = E;
     cout << "���ο� ��� : " << eArray[r + count].name << endl << "====" << endl;


}

void Vector_CircularArray::insertAtRank(int r, Element E) throw(const char*) {
     // �迭�� �뷮�� �ʰ��� ���, ���� �迭���� ũ�Ⱑ 2���� �迭 ����
     if (size() == sizeOfArray){
          
          Element *tempArray = new Element[2 * sizeOfArray];
          for (int i = 0; i < sizeOfArray; i++){
               tempArray[i] = eArray[i];
          }
          sizeOfArray = 2 * sizeOfArray;
          delete[] eArray;
          cout << &eArray << " " << &tempArray << endl;
          *eArray = *tempArray;                              // �ּ� �ٲ�ġ��======================�̷��� �ϴϱ� ��
          cout << &eArray << " " << &tempArray << endl;
          delete []tempArray;                                // ������ �迭 ����
          count = 0;                                         // count �ʱ�ȭ. ���ο� �迭�� �´� count

          cout << "�迭 ���� 2��� ����, �迭���̴� : " << sizeOfArray;
     }
     // �� �տ� �߰��� ���(����ð� �ҿ�)
     if (r == 0){
          count--;
          int tempInt = mod(r + count, sizeOfArray);
          eArray[tempInt] = E;                               // �������� ���⼭ ����.............
          numOfElement++;
          return;
     }
     
     if (r >= size()){ // �� �ڿ� �߰�
          //cout << "���� ����� ������" << size() << "�� �̰�, " << size() + 1 << "��° �ڸ��� �߰��ϰ���" << endl;
          eArray[(size())%sizeOfArray] = E;
          numOfElement++;
          return;
     } 

     // �߰��� �߰��� ���. k�� index�̹Ƿ� count�� ����
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

     for (int k = (r + count) % sizeOfArray; k < size() + count - 1; k = (k + 1) % sizeOfArray) { // ������ ������ ��� �� index������
          eArray[k % sizeOfArray] = eArray[(k + 1) % sizeOfArray];
          //if (k = size() + count - 1)
          //     eArray[(k + 1) % sizeOfArray];
          // ������ �迭�̸� delete���ָ� �Ǵµ�...
     }

     numOfElement--;
}

int Vector_CircularArray::size() {
     return numOfElement;
}

bool Vector_CircularArray::isEmpty() {
     return size() == 0; // ����� ������ 0�̸� ����ִ�.
}

int mod(int x, int m) {
     int r = x%m;
     return r<0 ? r + m : r;
}