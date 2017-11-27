
#include "HashTable.h"

int main(){
     ifstream input;         // 쿼리를 실행할 스트림
     ifstream database;      // 데이터베이스를 추가할 스트림
     bool stop = false;      // 반복문 플래그
     char operation = ' ';   // 질의어
     string fileName = "";
     int N = 0;              // 배열의 크기
     int M = 0;              // 멤버의 수
     int q = 0;              // N보다 작은 소수
     int key = 0;            // key값(=studentId)
     int score = 0;          // 학점
     string eMail = "";       // 이메일
      

     cin >> fileName;
     database.open(fileName);

     database >> N;           // 배열의 크기
     database >> M;           // 학생 수
     database >> q;           // 배열의 크기보다 작은 소수
     HashTable mHashTable(N, q); // 해시 테이블 생성

     // database에 있는 모든 정보를 해시 테이블에 추가할때 까지 반목문 실행
     while (M != 0) {
          database >> key;    // = studentId
          database >> score;
          database >> eMail;
          Node* tempNode = new Node(key, score, eMail); // 학생 정보를 가진 노드 생성
          mHashTable.put_db(key, tempNode);             // 노드를 해시 테이블에 추가
          M--;
     }

     database.close();

     while (!stop){

          cin >> operation;
          switch (operation){

          case 'A': // 학생 추가
          {
               key = 0;
               eMail = "";
               cin >> key;
               cin >> eMail;
               Node* tempNode = new Node(key, 0, eMail);

               mHashTable.put(key, tempNode);
          }
          break;

          case 'U': // 수강과목 추가
               key = 0;
               score = 0;
               cin >> key;
               cin >> score;

               mHashTable.addScore(key, score);
               break;

          case 'M': // 이메일 주소 변경
               key = 0;
               eMail = "";
               cin >> key;
               cin >> eMail;

               mHashTable.modifyEmail(key, eMail);
               break;

          case 'P': // 학생정보 출력
               key = 0;
               cin >> key;

               mHashTable.printStuInfo(key);
               break;

          case 'Q': // 종료
               stop = true;
               break;
          }
     }


     input.close();
     return 0;
}