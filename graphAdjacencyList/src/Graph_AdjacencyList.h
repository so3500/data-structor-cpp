#ifndef _GRAPH_ADJACENEYLIST_H_
#define _GRAPH_ADJACENEYLIST_H_

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// 클래스 전방선언
class Vertex;
class VertexPtr;
class VertexPtrList;
class Degree;
class DegList;
class Edge;
class EdgePtr;
class EdgePtrList;

// 학생
class Vertex{
public:
     Vertex(int stuId = 0 ,string eMail = "",
          VertexPtr* mVertexPtr = NULL){
          this->stuId = stuId;
          this->eMail = eMail;
          this->mVertexPtr = mVertexPtr;
          this->degree = 0;
     }

     int stuId;               // 학번
     string eMail;            // 이메일
     int degree;              // degree 수
     VertexPtr* mVertexPtr;   // 학생을 가리키는 포지션에 대한 포인터
     DegList* mDegList;       // degree List
};
// 학생을 가리키는 포지션 < POSITION POSITION POSITION POSITION POSITION POSITION POSITION POSITION >
class VertexPtr{
public:
     VertexPtr(Vertex* mVertex = NULL){
          this->mVertex = mVertex;
          this->next = NULL;
          this->prev = NULL;

     }

     Vertex* mVertex;         // 학생을 가리키는 포인터
     VertexPtr* next;         // 학생리스트의 다음 학생을 가리키는 포인터
     VertexPtr* prev;         // 학생리스트의 이전 학생을 가리키는 포인터
     Vertex* element_V();     // 학생 리스트의 노드가 가리키는 학생 리턴

};
// 학생을 가리키는 포지션 리스트  < LIST LIST LIST LIST LIST LIST LIST LIST LIST LIST >
class VertexPtrList{
public:
     VertexPtrList(){
          head = NULL;
          tail = NULL;
     }
     void insertVertexPtr(VertexPtr* edgePtr);     // 학생 포지션 객체 추가
     void deleteVertexPtr(VertexPtr* vertexPtr);   // 학생 객체 삭제 시 해당 포지션 객체 삭제
     VertexPtr* getVertexPtr(int stuId);           // 해당 학번을 가진 학생 포지션 객체 반환

     VertexPtr* head;    // head 포지션
     VertexPtr* tail;    // tail 포지션
};
// 학생으로부터 뻗어나가는 도로 degree
class Degree{
public:
     Degree(Edge* edge = NULL){
          this->edge = edge;
          this->next = NULL;
          this->prev = NULL;
     }
     Edge* element_E(){
          return edge;
     }

     Edge* edge;        // degree가 가리키는 도로
     Degree* next;      // 다음 degree
     Degree* prev;      // 이전 degree
};
// 학생으로부터 뻗어나가는 도로의 리스트(degree) < LIST LIST LIST LIST LIST LIST LIST LIST LIST LIST >
class DegList{
public:
     DegList(){
          this->head = NULL;
          this->tail = NULL;
     }

     void insertDeg(Degree* degree);  // Degree추가
     void deleteDeg(Degree* degree);  // 학생 객체 삭제 시 해당 다른 학생의 degree 삭제

     Degree* head;        // degreeList의 head
     Degree* tail;        // degreeList의 tail
     
     
};

// 학생을 연결하는 도로
class Edge{
public:
     // 도로는 두 명의 학생으로 정의된다
     Edge(int roadId = 0, Vertex* startV = NULL, Vertex* endV = NULL){
          this->roadId = roadId;
          this->startV = startV;
          this->destV = endV;
          this->startD = NULL;
          this->destD = NULL;
          this->mEdgePtr = NULL;

     }

     int roadId;           // 도로 번호

     Vertex* startV;       // 시작점 학생
     Vertex* destV;        // 도착점 학생
     Degree* startD;       // 시작점 학생의 Degree
     Degree* destD;        // 도착점 학생의 Degree
     EdgePtr* mEdgePtr;    // 도로를 가리키는 노드를 가리키는 포인터

};
// 도로를 가리키는 포지션 < POSITION POSITION POSITION POSITION POSITION POSITION POSITION POSITION > 
class EdgePtr{
public:
     EdgePtr(Edge* mEdge = NULL){
          this->mEdge = mEdge;
     }
     // 도로 리스트의 노드가 가리키는 도로 리턴
     Edge* element_E(){
          return mEdge;
     }

     Edge* mEdge;          // 도로를 가리키는 포인터
     EdgePtr* next;        // 도로리스트의 다음 도로을 가리키는 포인터
     EdgePtr* prev;        // 도로리스트의 이전 도로을 가리키는 포인터

};
// 도로를 가리키는 포지션 리스트 < LIST LIST LIST LIST LIST LIST LIST LIST LIST LIST >
class EdgePtrList{
public:
     EdgePtrList(){
          this->head = NULL;
          this->tail = NULL;
     }
     void insertEdgePtr(EdgePtr* edgePtr);        // 도로 포지션 객체 추가
     void deleteEdgePtr(EdgePtr* edgePtr);        // 학생 객체 삭제 시 관련 도로 포지션 객체 삭제
     EdgePtr* getEdgePtr(int roadId);             // 해당 번호를 가진 도로 포지션 객체 반환

     EdgePtr* head;
     EdgePtr* tail;
};

// 인접 리스트로 구현한 그래프
class G{
public:
     G(){
          numOfStu = 0;
          numOfLoad = 0;
     }
     
     void insertVertex_db(int stuId, string eMail);  // 학생 추가 from data.txt
     void insertEdge_db(int roadId, int startStuId, int destStuId); // 도로 추가 from data.txt

     void insertVertex(int stuId, string eMail);      // 학생 추가
     void printStuInfo(int stuId);      // 학생의 정보 출력
     void insertEdge(int roadId, int startStuId, int destStuId); // 도로 추가
     void deleteVertex(int stuId);      // 학생 삭제
     void deleteEdge(int roadId);       // 도로 삭제
     void incidentEdges(int stuId);     // 학생에 연결된 도로 리스트 리턴 incidentEdges
     void endVertices(int roadId);      // 해당 도로번호 끝에 있는 학생의 학번 출력
     void opposite(int stuId, int roadId); // 학생의 위치에서 도로로 갈 수 있는 반대쪽 학생의 학번 출력
     void isAdjacentTo(int stuId_1, int stuId_2); // 두 학생간의 도로 정보 출력
     


     int numOfStu;                  // 그래프의 총 학생 수
     int numOfLoad;                 // 그래프의 총 도로 수
     VertexPtrList List_VP;         // 학생 포지션 리스트
     EdgePtrList List_EP;           // 도로 포지션 리스트

};

#else
#endif
