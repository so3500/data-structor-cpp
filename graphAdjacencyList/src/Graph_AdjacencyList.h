#ifndef _GRAPH_ADJACENEYLIST_H_
#define _GRAPH_ADJACENEYLIST_H_

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Ŭ���� ���漱��
class Vertex;
class VertexPtr;
class VertexPtrList;
class Degree;
class DegList;
class Edge;
class EdgePtr;
class EdgePtrList;

// �л�
class Vertex{
public:
     Vertex(int stuId = 0 ,string eMail = "",
          VertexPtr* mVertexPtr = NULL){
          this->stuId = stuId;
          this->eMail = eMail;
          this->mVertexPtr = mVertexPtr;
          this->degree = 0;
     }

     int stuId;               // �й�
     string eMail;            // �̸���
     int degree;              // degree ��
     VertexPtr* mVertexPtr;   // �л��� ����Ű�� �����ǿ� ���� ������
     DegList* mDegList;       // degree List
};
// �л��� ����Ű�� ������ < POSITION POSITION POSITION POSITION POSITION POSITION POSITION POSITION >
class VertexPtr{
public:
     VertexPtr(Vertex* mVertex = NULL){
          this->mVertex = mVertex;
          this->next = NULL;
          this->prev = NULL;

     }

     Vertex* mVertex;         // �л��� ����Ű�� ������
     VertexPtr* next;         // �л�����Ʈ�� ���� �л��� ����Ű�� ������
     VertexPtr* prev;         // �л�����Ʈ�� ���� �л��� ����Ű�� ������
     Vertex* element_V();     // �л� ����Ʈ�� ��尡 ����Ű�� �л� ����

};
// �л��� ����Ű�� ������ ����Ʈ  < LIST LIST LIST LIST LIST LIST LIST LIST LIST LIST >
class VertexPtrList{
public:
     VertexPtrList(){
          head = NULL;
          tail = NULL;
     }
     void insertVertexPtr(VertexPtr* edgePtr);     // �л� ������ ��ü �߰�
     void deleteVertexPtr(VertexPtr* vertexPtr);   // �л� ��ü ���� �� �ش� ������ ��ü ����
     VertexPtr* getVertexPtr(int stuId);           // �ش� �й��� ���� �л� ������ ��ü ��ȯ

     VertexPtr* head;    // head ������
     VertexPtr* tail;    // tail ������
};
// �л����κ��� ������� ���� degree
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

     Edge* edge;        // degree�� ����Ű�� ����
     Degree* next;      // ���� degree
     Degree* prev;      // ���� degree
};
// �л����κ��� ������� ������ ����Ʈ(degree) < LIST LIST LIST LIST LIST LIST LIST LIST LIST LIST >
class DegList{
public:
     DegList(){
          this->head = NULL;
          this->tail = NULL;
     }

     void insertDeg(Degree* degree);  // Degree�߰�
     void deleteDeg(Degree* degree);  // �л� ��ü ���� �� �ش� �ٸ� �л��� degree ����

     Degree* head;        // degreeList�� head
     Degree* tail;        // degreeList�� tail
     
     
};

// �л��� �����ϴ� ����
class Edge{
public:
     // ���δ� �� ���� �л����� ���ǵȴ�
     Edge(int roadId = 0, Vertex* startV = NULL, Vertex* endV = NULL){
          this->roadId = roadId;
          this->startV = startV;
          this->destV = endV;
          this->startD = NULL;
          this->destD = NULL;
          this->mEdgePtr = NULL;

     }

     int roadId;           // ���� ��ȣ

     Vertex* startV;       // ������ �л�
     Vertex* destV;        // ������ �л�
     Degree* startD;       // ������ �л��� Degree
     Degree* destD;        // ������ �л��� Degree
     EdgePtr* mEdgePtr;    // ���θ� ����Ű�� ��带 ����Ű�� ������

};
// ���θ� ����Ű�� ������ < POSITION POSITION POSITION POSITION POSITION POSITION POSITION POSITION > 
class EdgePtr{
public:
     EdgePtr(Edge* mEdge = NULL){
          this->mEdge = mEdge;
     }
     // ���� ����Ʈ�� ��尡 ����Ű�� ���� ����
     Edge* element_E(){
          return mEdge;
     }

     Edge* mEdge;          // ���θ� ����Ű�� ������
     EdgePtr* next;        // ���θ���Ʈ�� ���� ������ ����Ű�� ������
     EdgePtr* prev;        // ���θ���Ʈ�� ���� ������ ����Ű�� ������

};
// ���θ� ����Ű�� ������ ����Ʈ < LIST LIST LIST LIST LIST LIST LIST LIST LIST LIST >
class EdgePtrList{
public:
     EdgePtrList(){
          this->head = NULL;
          this->tail = NULL;
     }
     void insertEdgePtr(EdgePtr* edgePtr);        // ���� ������ ��ü �߰�
     void deleteEdgePtr(EdgePtr* edgePtr);        // �л� ��ü ���� �� ���� ���� ������ ��ü ����
     EdgePtr* getEdgePtr(int roadId);             // �ش� ��ȣ�� ���� ���� ������ ��ü ��ȯ

     EdgePtr* head;
     EdgePtr* tail;
};

// ���� ����Ʈ�� ������ �׷���
class G{
public:
     G(){
          numOfStu = 0;
          numOfLoad = 0;
     }
     
     void insertVertex_db(int stuId, string eMail);  // �л� �߰� from data.txt
     void insertEdge_db(int roadId, int startStuId, int destStuId); // ���� �߰� from data.txt

     void insertVertex(int stuId, string eMail);      // �л� �߰�
     void printStuInfo(int stuId);      // �л��� ���� ���
     void insertEdge(int roadId, int startStuId, int destStuId); // ���� �߰�
     void deleteVertex(int stuId);      // �л� ����
     void deleteEdge(int roadId);       // ���� ����
     void incidentEdges(int stuId);     // �л��� ����� ���� ����Ʈ ���� incidentEdges
     void endVertices(int roadId);      // �ش� ���ι�ȣ ���� �ִ� �л��� �й� ���
     void opposite(int stuId, int roadId); // �л��� ��ġ���� ���η� �� �� �ִ� �ݴ��� �л��� �й� ���
     void isAdjacentTo(int stuId_1, int stuId_2); // �� �л����� ���� ���� ���
     


     int numOfStu;                  // �׷����� �� �л� ��
     int numOfLoad;                 // �׷����� �� ���� ��
     VertexPtrList List_VP;         // �л� ������ ����Ʈ
     EdgePtrList List_EP;           // ���� ������ ����Ʈ

};

#else
#endif
