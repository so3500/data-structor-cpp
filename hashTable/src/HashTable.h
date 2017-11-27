#ifndef _PROJECT_2_HASHTABLE_H_
#define _PROJECT_2_HASHTABLE_H_

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// 빈 상태, 사용 중, 사용했었으나 지금은 비어있음 를 나타냄
enum Status{ EMPTY, USED, AVAILABLE };
// 학생 정보를 가지고 있는 노드
class Node{
public:
     Node(int stuId = 0, int sco = 0, string mail = ""){
          studentId = stuId;
          score = sco;
          eMail = mail;
          //strcpy(eMail, mail);
     }
     friend class HashTable;
private:

     int studentId;    // 학번
     int score;        // 학점
     string eMail;      // 이메일

};
// 학생 정보를 가지고 있는 노드를 가리키는 노드포인터
class NodePointer{
public:
     NodePointer(Node* NPtr = NULL, Status st = EMPTY){
          NodePtr = NPtr;
          status = st;
     }
     friend class HashTable;
private:
     Node* NodePtr;           // 노드를 가리키는 노드포인터
     Status status;           // 상태를 나타내는 열겨형 변수, EMPTY, USED, AVAILABLE 세가지가 있다.
};

class HashTable{
public:
     HashTable(int N, int q){
          hashTableArray = new NodePointer*[N]();
          memset(hashTableArray, NULL, sizeof(hashTableArray)); // 배열의 모든 항목을 NULL로 초기화
          numOfStudent = 0;
          sizeOfTable = N;
          primeQ = q;
     }
     void put(int key, Node* o);                  // (1) 학생 추가
     void put_db(int key, Node* o);               // database 입력용 
     void addScore(int key, int score);           // (2) 수강과목 추가
     void modifyEmail(int key, string eMail);      // (3) 이메일 주소 변경
     void printStuInfo(int key);                  // (4) 학생정보 출력

private:
     NodePointer** hashTableArray;  // 노드형 포인터배열의 첫번째주소를 가진 포인터     
     int sizeOfTable;               // 테이블의 크기                
     int numOfStudent;              // 학생 수, 학생정보를 추가하거나 삭제 시 최신화     
     int primeQ;                    // 테이블의 크기 보다 작은 소수, 2차 해시 함수에 사용
};



// ================== (1) 학생추가_fromDB ==================
void HashTable::put_db(int key, Node* o){
     int index = 0;
     int probNum = 1;
     int stop = false;

     index = key % sizeOfTable;    // 1차 해시 함수

     while (!stop){
          // 배열의 index에 해당하는 공간이 비어있으면 추가
          if (hashTableArray[index] == NULL){
               o->studentId = key;                                    // 학생 정보 노드에 key값 입력
               NodePointer* tempNodePtr = new NodePointer(o, USED);   // 학생 정보 노드 포인터 객체 생성
               hashTableArray[index] = tempNodePtr;                   // 해시 테이블에 해당 학생 정보 노드 포인터 추가
               numOfStudent++;                                        // 테이블의 학생 수 최신화, 학생 추가이므로 1 증가
               stop = true;                                           // 반복문의 stop플래그
          }
          // 배열의 index에 해당하는 공간이 사용중일 경우
          else {
               index = (index + (primeQ - (key%primeQ))) % sizeOfTable; // 2차 해시 함수
               probNum++;                                               // 프로브 횟수 증가
          }
     }
}

// ================== (2) 학생추가_fromQuery ==================
void HashTable::put(int key, Node* o){
     int index = 0;
     int probNum = 1;
     int stop = false;

     index = key % sizeOfTable;    // 1차 해시 함수

     while (!stop){
          // 배열의 index에 해당하는 공간이 비어있으면 추가
          if (hashTableArray[index] == NULL){
               NodePointer* tempNodePtr = new NodePointer(o, USED);
               hashTableArray[index] = tempNodePtr;
               numOfStudent++;
               stop = true;
          }
          // 배열의 index에 해당하는 공간이 사용중일 경우
          else {

               index = (index + (primeQ - (key%primeQ))) % sizeOfTable; // 2차 해시 함수
               probNum++;                                               // probe 수 증가
          }
     }

     cout << probNum << " ";  // 프로브 횟수 출력

     double tempD = (double)numOfStudent / sizeOfTable;
     tempD = tempD * 1000;
     tempD = (((int)tempD + 5) / 10);
     tempD = tempD / 100;
     
     // load factor 출력
     printf("%2.2f", tempD); // %자릿수1.자릿수2f 총 자릿수1만큼 출력되나 소수점 이하의 자릿수가 자릿수2만큼 출력 
     cout << endl;

     

}

// ================== (3) 수강과목 추가 ==================
void HashTable::addScore(int key, int score){
     int index = 0;
     int probNum = 1;
     int stop = false;

     index = key % sizeOfTable;    // 1차 해시 함수

     while (!stop){
          // 해당 index공간이 비어있지 않은 경우
          if (hashTableArray[index] != NULL) {
               // 배열의 index에 해당하는 노드(학생)의 key값이 찾는 key값과 일치하는 경우
               if (hashTableArray[index]->NodePtr->studentId == key){
                    Node* tempNode = hashTableArray[index]->NodePtr; // 해당 index에 있는 노드포인터의 주소 복사

                    // 새로 추가하여 합산한 학점이 24점을 넘는경우, 수강과목 추가 실패
                    if (tempNode->score + score > 24){
                         cout << probNum << " Exceeded" << endl;
                    }
                    // 24학점을 넘지 않는 경우, 수강과목 추가 성공
                    else{
                         tempNode->score += score;                            // 학점 추가
                         cout << probNum << " " << tempNode->score << endl;   // 프로브 횟수와 합산한 학점 출력
                    }
                    stop = true;
               }
               // key값이 일치하지 않는 경우
               else{
                    index = (index + (primeQ - (key%primeQ))) % sizeOfTable; // 2차 해시 함수
                    probNum++;                                               // probe 수 증가

               }
          }
          // 해당 인덱스 공간이 비어있는 경우(NULL) 프로브 중지, 매개변수로 주어진 key값과 일치하는 노드 찾기 실패
          else{
               cout << probNum << " Not found" << endl;
               stop = true;
          }
     }
}

// ================== (4) 이메일주소 변경 ==================
void HashTable::modifyEmail(int key, string eMail){
     int index = 0;
     int probNum = 1;
     int stop = false;

     index = key % sizeOfTable;    // 1차 해시 함수

     while (!stop){
          // 해당 index공간이 비어있지 않은 경우
          if (hashTableArray[index] != NULL) {
               // 배열의 index에 해당하는 노드(학생)의 key값이 찾는 key값과 일치하는 경우
               if (hashTableArray[index]->NodePtr->studentId == key){
                    Node* tempNode = hashTableArray[index]->NodePtr;
                    tempNode->eMail = eMail;
                    //strcpy(tempNode->eMail, eMail); // 이메일 변경
                    stop = true;
                    cout << probNum << endl;
               }
               // 배열의 index에 해당하는 노드(학생)가 있고, key값이 일치하지 않는 경우
               else{
                    index = (index + (primeQ - (key%primeQ))) % sizeOfTable; // 2차 해시 함수
                    probNum++;                                               // probe 수 증가
               }
          }
          // 해당 인덱스 공간이 비어있는 경우(NULL) 프로브 중지, 매개변수로 주어진 key값과 일치하는 노드 찾기 실패
          else{
               cout << probNum << " Not found" << endl;
               stop = true;
          }
     }
}

// ================== (5) 학생정보 출력 ==================
void HashTable::printStuInfo(int key){
     int index = 0;
     int probNum = 1;
     int stop = false;

     index = key % sizeOfTable;    // 1차 해시 함수

     while (!stop){
          // 해당 index공간이 비어있지 않은 경우
          if (hashTableArray[index] != NULL) {
               // 배열의 index에 해당하는 노드(학생)의 key값이 찾는 key값과 일치하는 경우
               if (hashTableArray[index]->NodePtr->studentId == key){
                    Node* tempNode = hashTableArray[index]->NodePtr;

                    // 학생정보 출력
                    cout << probNum << " "
                         << tempNode->studentId << " "
                         << tempNode->score << " "
                         << tempNode->eMail << endl;
                    stop = true;
               }
               // 배열의 index에 해당하는 노드(학생)가 있고, key값이 일치하지 않는 경우
               else{
                    index = (index + (primeQ - (key%primeQ))) % sizeOfTable; // 2차 해시 함수
                    probNum++;                                               // probe 횟수 증가
               }
          }
          // 해당 인덱스 공간이 비어있는 경우(NULL) 프로브 중지, 매개변수로 주어진 key값과 일치하는 노드 찾기 실패
          else{
               cout << probNum << " Not found" << endl;
               stop = true;
          }
     }
}
#else
#endif
