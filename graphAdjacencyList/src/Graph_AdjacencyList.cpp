
#include "Graph_AdjacencyList.h"

// 학생 리스트의 노드가 가리키는 학생 리턴
Vertex* VertexPtr::element_V(){ return mVertex; }

// 1. 학생추가
void G::insertVertex(int stuId, string eMail){
     Vertex* tempVertex = new Vertex(stuId, eMail);         // 학생 객체 
     VertexPtr* tempVertexPtr = new VertexPtr(tempVertex);  // 학생 객체를 참조하는 포지션 객체
     tempVertex->mVertexPtr = tempVertexPtr;                // 학생 객체가 포지션 객체를 참조

     List_VP.insertVertexPtr(tempVertexPtr);                // 포지션 객체를 리스트에 추가
     numOfStu++;                                            // 학생 수 +1
     cout << numOfStu << endl;                              // 학생 수 출력
}
// 학생 객체 포지션을 리스트에 추가
void VertexPtrList::insertVertexPtr(VertexPtr* vertexPtr){
     // 객체를 처음으로 추가하는 경우
     if (head == NULL){
          vertexPtr->prev = NULL;
          vertexPtr->next = NULL;
          head = vertexPtr;
          tail = vertexPtr;
     }
     // 기존의 리스트에 객체를 추가하는 경우(꼬리에서 추가)
     else{
          tail->next = vertexPtr;
          vertexPtr->prev = tail;
          vertexPtr->next = NULL;
          tail = vertexPtr;
     }

}
// =======================================================================================
// 2. 학생 정보 출력
void G::printStuInfo(int stuId){
     VertexPtr* tempVertexPtr = List_VP.getVertexPtr(stuId);          // 학생 객체 포지션 얻기
     // 학생을 찾지 못한 경우
     if (tempVertexPtr == NULL){
          cout << "Not found" << endl;
     }
     // 학생을 찾은 경우 학생 정보 출력
     else { 
          Vertex* tempVertex = tempVertexPtr->element_V();              // 학생 객체 얻기
          cout << tempVertex->eMail << " " << tempVertex->degree << endl;
     }
          
}
// 학생 객체 포지션 리스트에서 주어진 학번과 일치하는 학생 객체를 탐색
VertexPtr* VertexPtrList::getVertexPtr(int stuId){
     VertexPtr* tempVertexPtr = this->head;
     // head에서부터 탐색 시작
     while (tempVertexPtr != NULL){
          if (tempVertexPtr->mVertex->stuId == stuId){
               return tempVertexPtr;
          }
          tempVertexPtr = tempVertexPtr->next;
     }
     // 학번에 해당하는 학생 객체를 찾지 못한 경우 NULL 반환
     return NULL;
}
// ========================================================================================
// 3. 도로 추가
void G::insertEdge(int roadId, int startStuId, int destStuId){
     VertexPtr* tempVertexPtr_s = List_VP.getVertexPtr(startStuId);
     VertexPtr* tempVertexPtr_d = List_VP.getVertexPtr(destStuId);
     
     // 학생 객체가 그래프에 존재하지 않는 경우
     if (tempVertexPtr_s == NULL || tempVertexPtr_d == NULL){
          cout << numOfLoad << " Not found" << endl;
          return;
     }
     Vertex* startVertex = tempVertexPtr_s->element_V(); // 출발지점 학생 객체 참조
     Vertex* destVertex = tempVertexPtr_d->element_V();  // 목표지점 학생 객체 참조

     Edge* tempEdge = new Edge(roadId, startVertex, destVertex); // 도로 객체 생성

     // 도로 객체와 도로 포지선 객체가 서로 참조 하는과정
     EdgePtr* tempEdgePtr = new EdgePtr(tempEdge);
     tempEdge->mEdgePtr = tempEdgePtr;
     // 도로 포지션 객체를 도로 리스트에 추가
     List_EP.insertEdgePtr(tempEdgePtr);
     // 각 학생 객체에 대한 degree 객체 생성 
     // -> degree가 edge를 참조
     // -> edge도 degree를 참조
     // -> 그 degree를 각 degree리스트에 추가
     Degree* startVertexDegree = new Degree(tempEdge);
     Degree* destVertexDegree = new Degree(tempEdge);
     tempEdge->startD = startVertexDegree;
     tempEdge->destD = destVertexDegree;

     // 각 학생들이 처음으로 도로를 추가하는 경우 (= 처음으로 degree List를 추가하는 경우)
     if (startVertex->mDegList == NULL){
          startVertex->mDegList = new DegList;
     }
     if (destVertex->mDegList == NULL){
          destVertex->mDegList = new DegList;
     }
     // 기존의 degree List에 degree를 추가
     startVertex->mDegList->insertDeg(startVertexDegree);
     destVertex->mDegList->insertDeg(destVertexDegree);

     startVertex->degree++; // 학생의 degree +1
     destVertex->degree++; 
     numOfLoad++;  // 도로 수 +1

     cout << numOfLoad << endl;

}
// degree 객체를 degree 리스트에 추가
void DegList::insertDeg(Degree* degree){
     // 객체를 처음으로 추가하는 경우
     if (head == NULL){
          degree->prev = NULL;
          degree->next = NULL;
          head = degree;
          tail = degree;
     }
     // 기존의 리스트에 객체를 추가하는 경우(꼬리에서 추가)
     else{
          tail->next = degree;
          degree->prev = tail;
          degree->next = NULL;
          tail = degree;
     }
}
// 도로 객체 포지션을 도로 리스트에 추가
void EdgePtrList::insertEdgePtr(EdgePtr* edgePtr){
     // 객체를 처음으로 추가하는 경우
     if (head == NULL){
          edgePtr->prev = NULL;
          edgePtr->next = NULL;
          head = edgePtr;
          tail = edgePtr;
     }
     // 기존의 리스트에 객체를 추가하는 경우(꼬리에서 추가)
     else{
          tail->next = edgePtr;
          edgePtr->prev = tail;
          edgePtr->next = NULL;
          tail = edgePtr;
     }
}
// ========================================================================================
// 4. 학생 삭제
void G::deleteVertex(int stuId){
     // Vertex 삭제순서
     // EdgePtr삭제 -> degree삭제 -> Edge삭제 -> Vertex 삭제-> vertexPtr 삭제
     VertexPtr* tempVertexPtr = List_VP.getVertexPtr(stuId);       // 학생 객체 포지션 참조
     
     
     // 학생을 찾지 못한 경우
     if (tempVertexPtr == NULL){
          cout << numOfStu << " " << numOfLoad << " Not found" << endl;
          return;
     }
     Vertex* tempVertex = tempVertexPtr->element_V();              // 학생 객체 참조
     DegList* tempDegList = tempVertex->mDegList;  // 학생 객체의 degree 리스트 참조

     // 학생 객체가 degree가 0인경우, 관련된 edge, degree가 없으므로 학생객체를 바로 삭제 가능
     if (tempDegList == NULL){
          List_VP.deleteVertexPtr(tempVertexPtr);
          delete tempVertex;
          numOfStu--;
          cout << numOfStu << " " << numOfLoad << endl;
          return;
     }

     Degree* tempDegree = tempDegList->head;       // dgree 리스트의 head 참조
     
     // 삭제할 학생 객체의 degree에 해당하는 모든 도로를 삭제하는 과정
     while (tempDegree != NULL){
          Edge* tempEdge = tempDegree->edge;
          List_EP.deleteEdgePtr(tempEdge->mEdgePtr); // EdgePtr삭제
          
          // 삭제하려는 도로 반대편의 학생 객체로 접근하여 해당 degree객체 삭제
          if (tempEdge->startD != tempDegree){
               // degree 리스트에서 다음 degree객체 참조, 이전에 참조하고있던 degree객체 삭제
               tempDegree = tempDegree->next; 
               tempEdge->startV->mDegList->deleteDeg(tempEdge->startD);
               tempEdge->startV->degree--;
               // 현재 접근중인 degree List에서도 degree삭제
               tempEdge->destV->mDegList->deleteDeg(tempEdge->destD);
               tempEdge->destV->degree--;
          }
          else{
               tempDegree = tempDegree->next;
               tempEdge->destV->mDegList->deleteDeg(tempEdge->destD);
               tempEdge->destV->degree--;
               // 현재 접근중인 degree List에서도 degree삭제
               tempEdge->startV->mDegList->deleteDeg(tempEdge->startD);
               tempEdge->startV->degree--;
          }

          delete tempEdge;   // Edge 삭제
          numOfLoad--;       // 도로 개수 -1
     }

     delete tempVertex; // Vertex삭제
     List_VP.deleteVertexPtr(tempVertexPtr); // VertexPtr삭제
     numOfStu--;             // 학생 개수 -1

     cout << numOfStu << " " << numOfLoad << endl;
     
}
// 학생 객체 삭제 시 해당 포지션 객체 삭제
void VertexPtrList::deleteVertexPtr(VertexPtr* vertexPtr){
     // 삭제할 학생 포지션 객체의 링크를 해제한 뒤 해당 객체 삭제
     // 삭제할 학생 포지션 객체가 하나뿐인 경우
     if (head == vertexPtr && tail == vertexPtr){
          head = NULL;
          tail = NULL;
     }
     // 삭제할 학생 포지션 객체가 head인 경우
     else if (head == vertexPtr){
          head = vertexPtr->next;
          head->prev = NULL;
     }
     // 삭제할 학생 포지션 객체가 tail인 경우
     else if (tail == vertexPtr){
          tail = vertexPtr->prev;
          tail->next = NULL;
     }
     // 삭제할 학생 포지션 객체가 List에서 중간에 위치한 경우
     else{
          // 삭제할 학생 포지션 객체의 링크를 해제한 뒤 해당 학생 포지션 객체 삭제
          VertexPtr* tempVertexPtrPrev = vertexPtr->prev;
          vertexPtr->prev->next = vertexPtr->next;
          vertexPtr->next->prev = tempVertexPtrPrev;
     }
     delete vertexPtr;
}

// Degree 리스트에서 degree 객체 삭제
void DegList::deleteDeg(Degree* degree){    
     // 삭제할 degree 객체가 하나뿐인 경우
     if (head == degree && tail == degree){
          head = NULL;
          tail = NULL;
     }
     // 삭제할 degree 객체가 head인 경우
     else if (head == degree){
          head = degree->next;
          head->prev = NULL;
     }
     // 삭제할 degree 객체가 tail인 경우
     else if (tail == degree){
          tail = degree->prev;
          tail->next = NULL;
     }
     // 삭제할 degree 객체가 List에서 중간에 위치한 경우
     else{
          // 삭제할 degree 객체의 링크를 해제한 뒤 해당 degree 객체 삭제
          Degree* tempDegreePrev = degree->prev;
          degree->prev->next = degree->next;
          degree->next->prev = tempDegreePrev;
     }
     delete degree;
}
// 도로 리스트에서 도로 포지션 객체 삭제 
// **학생 객체 삭제시 도로 포지션의 위치에 상수시간 내에 접근가능**
void EdgePtrList::deleteEdgePtr(EdgePtr* edgePtr){
     // 삭제할 도로 포지션 객체의 링크를 해제한 뒤 해당 객체 삭제
     // 삭제할 도로 포지션 객체가 하나뿐인 경우
     if (head == edgePtr && tail == edgePtr){
          head = NULL;
          tail = NULL;
     }
     // 삭제할 도로 포지션 객체가 head인 경우
     else if (head == edgePtr){
          head = edgePtr->next;
          head->prev = NULL;
     }
     // 삭제할 도로 포지션 객체가 tail인 경우
     else if (tail == edgePtr){
          tail = edgePtr->prev;
          tail->next = NULL;
     }
     // 삭제할 도로 포지션 객체가 List에서 중간에 위치한 경우
     else{
          // 삭제할 도로 포지션 객체의 링크를 해제한 뒤 해당 객체 삭제
          EdgePtr* tempEdgePtrPrev = edgePtr->prev;
          edgePtr->prev->next = edgePtr->next;
          edgePtr->next->prev = tempEdgePtrPrev;
     }
     delete edgePtr;
     
}

// ========================================================================================
// 5. 도로 삭제
void G::deleteEdge(int roadId){
     // EdgePtr삭제 -> degree삭제 -> Edge삭제 -> Vertex 삭제-> vertexPtr 삭제
     EdgePtr* tempEdgePtr = List_EP.getEdgePtr(roadId);       // 도로 객체 포지션 참조
     
     // 도로를 찾지 못한 경우
     if (tempEdgePtr == NULL){
          cout << numOfLoad << " Not found" << endl;
          return;
     }
     Edge* tempEdge = tempEdgePtr->element_E();               // 도로 객체 참조

     DegList* startDegreeList = tempEdge->startV->mDegList;  // 시작 학생 객체의 degree 리스트 참조
     Degree* startDegree = tempEdge->startD;                 // 시작 지점 학생 객체의 degree
     DegList* destDegreeList = tempEdge->destV->mDegList;    // 종점 학생 객체의 degree 리스트 참조
     Degree* destDegree = tempEdge->destD;                   // 종점 지점 학생 객체의 degree

     startDegreeList->deleteDeg(startDegree); // 학생 객체의 degree List에서 degree삭제
     destDegreeList->deleteDeg(destDegree);
     tempEdge->startV->degree--;              // 학생 객체의 degree 개수 -1
     tempEdge->destV->degree--;

     numOfLoad--;        // 도로 개수 -1
     cout << numOfLoad << endl;
}

EdgePtr* EdgePtrList::getEdgePtr(int roadId){
     EdgePtr* tempEdgePtr = this->head;
     // head에서부터 탐색 시작
     while (tempEdgePtr != NULL){
          if (tempEdgePtr->mEdge->roadId == roadId){
               return tempEdgePtr;
          }
          tempEdgePtr = tempEdgePtr->next;
     }
     // 학번에 해당하는 도로 객체를 찾지 못한 경우 NULL 반환
     return NULL;
}
// ========================================================================================
// 6. 연결된 도로 출력
void G::incidentEdges(int stuId){
     VertexPtr* tempVertexPtr = List_VP.getVertexPtr(stuId);

     // 주어진 학번에 해당하는 학생 포지션 객체가 없을 경우
     if (tempVertexPtr == NULL){
          cout << "Not found" << endl;
          return;
     }
     Vertex* tempVertex = tempVertexPtr->element_V();
     DegList* tempDegList = tempVertex->mDegList;
     Degree* tempDegree = tempDegList->head;

     // Degree List내의 Degree개수 출력
     cout << tempVertex->degree;
     // Degree List내의 Degree에 해당하는 도로번호 Edge->roadId 를 출력
     while (tempDegree != NULL){
          cout << " " << tempDegree->edge->roadId;
          tempDegree = tempDegree->next;
     }
     cout << endl;
}

// ========================================================================================
// 7. 도로 정보 출력 1
void G::endVertices(int roadId){
     EdgePtr* tempEdgePtr = List_EP.getEdgePtr(roadId);

     // 주어진 도로번호에 해당하는 도로 포지션 객체가 없을 경우
     if (tempEdgePtr == NULL){
          cout << "Not found" << endl;
          return;
     }

     int stuId_1 = 0;
     int stuId_2 = 0;
     Edge* tempEdge = tempEdgePtr->element_E();

     // 도로가 가리키는 학생의 학번 얻기
     stuId_1 = tempEdge->startV->stuId;
     stuId_2 = tempEdge->destV->stuId;

     // 학번이 작은 학생의 학번을 먼저 출력
     if (stuId_1 > stuId_2){
          cout << stuId_2 << " " << stuId_1 << endl;
     }
     else{
          cout << stuId_1 << " " << stuId_2 << endl;
     }
     
}
// ========================================================================================
// 8. 도로 정보 출력 2
void G::opposite(int stuId, int roadId){
     VertexPtr* tempVertexPtr = List_VP.getVertexPtr(stuId);
     EdgePtr* tempEdgePtr = List_EP.getEdgePtr(roadId);

     // 학생이나 도로를 찾지 못한 경우
     if (tempVertexPtr == NULL || tempEdgePtr == NULL){
          cout << "Not available" << endl;
          return;
     }

     Vertex* tempVertx = tempVertexPtr->element_V();
     Edge* tempEdge = tempEdgePtr->element_E();

     // edge의 종점 중 하나가 vertex인 경우 반대 vertex의 학번 출력
     if (tempEdge->startV == tempVertx){
          cout << tempEdge->destV->stuId << endl;
     }
     else if (tempEdge->destV == tempVertx){
          cout << tempEdge->startV->stuId << endl;
     }
     // edge의 종점 중에 vertex가 없는 경우
     else{
          cout << "Not available" << endl;
     }
     
}
// ========================================================================================
// 9. 도로존재 여부 확인
void G::isAdjacentTo(int stuId_1, int stuId_2){
     VertexPtr* startVertexPtr = List_VP.getVertexPtr(stuId_1);
     VertexPtr* destVertexPtr = List_VP.getVertexPtr(stuId_2);
     // 주어진 학번에 해당하는 학생 포지션 객체를 찾지 못한 경우
     if (startVertexPtr == NULL || destVertexPtr == NULL){
          cout << "Not found" << endl;
          return;
     }
     Vertex* startVertex = startVertexPtr->element_V();
     Vertex* destVertex = destVertexPtr->element_V();
     // 주어진 학번에 해당하는 학생객체가 도로를 가지고 있지 않은 경우
     if (startVertex->degree == 0 || destVertex->degree == 0){
          cout << "Not found" << endl;
          return;
     }
     DegList* startDegList = startVertex->mDegList;
     DegList* destDegList = destVertex->mDegList;
     Degree* startDegree = startDegList->head;
     Degree* destDegree = destDegList->head;

     // 두 학생 Vertex에서 작은 수의 degree값을 가진 학생 degree List에서 탐색을 수행
     if (startVertex->degree > destVertex->degree){
          while (destDegree != NULL){
               // 도착지점 학생 degree에서 시작지점 학생 degree로 갈 수 있는 경우
               if (destDegree->edge->startV == startVertex || destDegree->edge->destV == startVertex){
                    cout << destDegree->edge->roadId << endl;
                    return;
               }
               // 탐색에 실패한 경우 각 Degree List에서 다음 degree로 넘어간다
               else{
                    destDegree = destDegree->next;
               }
          }
     }
     // ------------------ 위와 같은 과정이나 탐색을 수행하는 학생 vertex가 다름 ------
     else {
          while (startDegree != NULL){
               // 도착지점 학생 degree에서 시작지점 학생 degree로 갈 수 있는 경우
               if (startDegree->edge->startV == destVertex || startDegree->edge->destV == destVertex){
                    cout << startDegree->edge->roadId << endl;
                    return;
               }
               // 탐색에 실패한 경우 각 Degree List에서 다음 degree로 넘어간다
               else{
                    startDegree = startDegree->next;
               }
          }
     }

     // 각 degree List를 모두 탐색했음에도 불구하고 두 학생 사이의 도로를 발견하지 못한 경우
     cout << "Not found" << endl;

}

// ========================================================================================
// a. db로부터 학생 추가
void G::insertVertex_db(int stuId, string eMail){
     Vertex* tempVertex = new Vertex(stuId, eMail);         // 학생 객체 
     VertexPtr* tempVertexPtr = new VertexPtr(tempVertex);  // 학생 객체를 참조하는 포지션 객체
     tempVertex->mVertexPtr = tempVertexPtr;                // 학생 객체가 포지션 객체를 참조

     List_VP.insertVertexPtr(tempVertexPtr);                // 포지션 객체를 리스트에 추가
     numOfStu++;                                            // 학생 수 +1
}
// b. db로부터 도로 추가
void G::insertEdge_db(int roadId, int startStuId, int destStuId){
     VertexPtr* tempVertexPtr_s = List_VP.getVertexPtr(startStuId);
     VertexPtr* tempVertexPtr_d = List_VP.getVertexPtr(destStuId);

     // 학생 객체가 그래프에 존재하지 않는 경우
     if (tempVertexPtr_s == NULL || tempVertexPtr_d == NULL){
          cout << numOfLoad << " Not found" << endl;
          return;
     }
     Vertex* startVertex = tempVertexPtr_s->element_V(); // 출발지점 학생 객체 참조
     Vertex* destVertex = tempVertexPtr_d->element_V();  // 목표지점 학생 객체 참조

     Edge* tempEdge = new Edge(roadId, startVertex, destVertex); // 도로 객체 생성

     // 도로 객체와 도로 포지선 객체가 서로 참조 하는과정
     EdgePtr* tempEdgePtr = new EdgePtr(tempEdge);
     tempEdge->mEdgePtr = tempEdgePtr;
     // 도로 포지션 객체를 도로 리스트에 추가
     List_EP.insertEdgePtr(tempEdgePtr);
     // 각 학생 객체에 대한 degree 객체 생성 
     // -> degree가 edge를 참조
     // -> edge도 degree를 참조
     // -> 그 degree를 각 degree리스트에 추가
     Degree* startVertexDegree = new Degree(tempEdge);
     Degree* destVertexDegree = new Degree(tempEdge);
     tempEdge->startD = startVertexDegree;
     tempEdge->destD = destVertexDegree;

     // 각 학생들이 처음으로 도로를 추가하는 경우 (= 처음으로 degree List를 추가하는 경우)
     if (startVertex->mDegList == NULL){
          startVertex->mDegList = new DegList;
     }
     if (destVertex->mDegList == NULL){
          destVertex->mDegList = new DegList;
     }
     // 기존의 degree List에 degree를 추가
     startVertex->mDegList->insertDeg(startVertexDegree);
     destVertex->mDegList->insertDeg(destVertexDegree);

     startVertex->degree++; // 학생의 degree +1
     destVertex->degree++;
     numOfLoad++;  // 도로 수 +1
}



// --------------------------------------
/*


*/