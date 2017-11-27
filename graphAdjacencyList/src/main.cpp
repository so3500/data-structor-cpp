
#include "Graph_AdjacencyList.h"

int main(){
     ifstream input;    // 쿼리를 실행할 스트림
     ifstream database; // 데이터베이스를 추가할 스트림
     bool stop = false;       // 반복문 플래그
     char operation = ' ';    // 질의어
     string fileName = "";

     int numOfVertex = 0; // 추가할 학생 수
     int numOfEdge = 0;   // 추가할 도로 수
     int stuId = 0;       // 학번
     string eMail = "";   // 이메일
     int roadId = 0;      // 도로 번호
     int startStuId = 0;     // 도로의 시작점에있는 학생의 학번
     int destStuId = 0;      // 도로의 도착점에있는 학생의 학번

     G G;                     // 인접 리스트 기반 그래프 선언

     cin >> fileName;
     database.open(fileName);

     database >> numOfVertex; // database로부터 학생 수 입력받음
     database >> numOfEdge;   // database로부터 도로 수 입력받음

     // database에 있는 학생 정보를 모두 입력받음
     for (int i = 0; i < numOfVertex; i++){
          database >> stuId;
          database >> eMail;
          G.insertVertex_db(stuId, eMail);   // 그래프 G에 학생 vertex 생성, 추가
     }

     // database에 있는 도로 정보를 모두 입력받음
     for (int j = 0; j < numOfEdge; j++){
          database >> roadId;
          database >> startStuId;
          database >> destStuId;
          G.insertEdge_db(roadId, startStuId, destStuId);
     }

     while (!stop){
          cin >> operation; // 질의어 입력

          switch (operation){

          case 'A': // 1. 학생 추가
               cin >> stuId;
               cin >> eMail;
               G.insertVertex(stuId, eMail);
               break;
               
          case 'P': // 2. 학생정보 출력
               cin >> stuId;
               G.printStuInfo(stuId);
               break;

          case 'I': // 3. 도로 추가
               cin >> roadId;
               cin >> startStuId;
               cin >> destStuId;
               G.insertEdge(roadId, startStuId, destStuId);
               break;

          case 'X': // 4. 학생 삭제
               cin >> stuId;
               G.deleteVertex(stuId);
               break;

          case 'Z': // 5. 도로 삭제
               cin >> roadId;
               G.deleteEdge(roadId);
               break;

          case 'L': // 6. 연결된 도로 출력
               cin >> stuId;
               G.incidentEdges(stuId);
               break;

          case 'F': // 7. 도로정보 출력1
               cin >> roadId;
               G.endVertices(roadId);
               break;

          case 'O': // 8. 도로정보 출력2
               cin >> stuId;
               cin >> roadId;
               G.opposite(stuId, roadId);
               break;

          case 'K': // 9. 도로존재 여부 확인
               cin >> startStuId;
               cin >> destStuId;
               G.isAdjacentTo(startStuId, destStuId);
               break;

          case 'Q': // 10. 프로그램 종료
               stop = true;
               break;



          }
     }



     return 0;
}