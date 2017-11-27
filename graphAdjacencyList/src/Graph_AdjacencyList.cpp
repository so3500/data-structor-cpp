
#include "Graph_AdjacencyList.h"

// �л� ����Ʈ�� ��尡 ����Ű�� �л� ����
Vertex* VertexPtr::element_V(){ return mVertex; }

// 1. �л��߰�
void G::insertVertex(int stuId, string eMail){
     Vertex* tempVertex = new Vertex(stuId, eMail);         // �л� ��ü 
     VertexPtr* tempVertexPtr = new VertexPtr(tempVertex);  // �л� ��ü�� �����ϴ� ������ ��ü
     tempVertex->mVertexPtr = tempVertexPtr;                // �л� ��ü�� ������ ��ü�� ����

     List_VP.insertVertexPtr(tempVertexPtr);                // ������ ��ü�� ����Ʈ�� �߰�
     numOfStu++;                                            // �л� �� +1
     cout << numOfStu << endl;                              // �л� �� ���
}
// �л� ��ü �������� ����Ʈ�� �߰�
void VertexPtrList::insertVertexPtr(VertexPtr* vertexPtr){
     // ��ü�� ó������ �߰��ϴ� ���
     if (head == NULL){
          vertexPtr->prev = NULL;
          vertexPtr->next = NULL;
          head = vertexPtr;
          tail = vertexPtr;
     }
     // ������ ����Ʈ�� ��ü�� �߰��ϴ� ���(�������� �߰�)
     else{
          tail->next = vertexPtr;
          vertexPtr->prev = tail;
          vertexPtr->next = NULL;
          tail = vertexPtr;
     }

}
// =======================================================================================
// 2. �л� ���� ���
void G::printStuInfo(int stuId){
     VertexPtr* tempVertexPtr = List_VP.getVertexPtr(stuId);          // �л� ��ü ������ ���
     // �л��� ã�� ���� ���
     if (tempVertexPtr == NULL){
          cout << "Not found" << endl;
     }
     // �л��� ã�� ��� �л� ���� ���
     else { 
          Vertex* tempVertex = tempVertexPtr->element_V();              // �л� ��ü ���
          cout << tempVertex->eMail << " " << tempVertex->degree << endl;
     }
          
}
// �л� ��ü ������ ����Ʈ���� �־��� �й��� ��ġ�ϴ� �л� ��ü�� Ž��
VertexPtr* VertexPtrList::getVertexPtr(int stuId){
     VertexPtr* tempVertexPtr = this->head;
     // head�������� Ž�� ����
     while (tempVertexPtr != NULL){
          if (tempVertexPtr->mVertex->stuId == stuId){
               return tempVertexPtr;
          }
          tempVertexPtr = tempVertexPtr->next;
     }
     // �й��� �ش��ϴ� �л� ��ü�� ã�� ���� ��� NULL ��ȯ
     return NULL;
}
// ========================================================================================
// 3. ���� �߰�
void G::insertEdge(int roadId, int startStuId, int destStuId){
     VertexPtr* tempVertexPtr_s = List_VP.getVertexPtr(startStuId);
     VertexPtr* tempVertexPtr_d = List_VP.getVertexPtr(destStuId);
     
     // �л� ��ü�� �׷����� �������� �ʴ� ���
     if (tempVertexPtr_s == NULL || tempVertexPtr_d == NULL){
          cout << numOfLoad << " Not found" << endl;
          return;
     }
     Vertex* startVertex = tempVertexPtr_s->element_V(); // ������� �л� ��ü ����
     Vertex* destVertex = tempVertexPtr_d->element_V();  // ��ǥ���� �л� ��ü ����

     Edge* tempEdge = new Edge(roadId, startVertex, destVertex); // ���� ��ü ����

     // ���� ��ü�� ���� ������ ��ü�� ���� ���� �ϴ°���
     EdgePtr* tempEdgePtr = new EdgePtr(tempEdge);
     tempEdge->mEdgePtr = tempEdgePtr;
     // ���� ������ ��ü�� ���� ����Ʈ�� �߰�
     List_EP.insertEdgePtr(tempEdgePtr);
     // �� �л� ��ü�� ���� degree ��ü ���� 
     // -> degree�� edge�� ����
     // -> edge�� degree�� ����
     // -> �� degree�� �� degree����Ʈ�� �߰�
     Degree* startVertexDegree = new Degree(tempEdge);
     Degree* destVertexDegree = new Degree(tempEdge);
     tempEdge->startD = startVertexDegree;
     tempEdge->destD = destVertexDegree;

     // �� �л����� ó������ ���θ� �߰��ϴ� ��� (= ó������ degree List�� �߰��ϴ� ���)
     if (startVertex->mDegList == NULL){
          startVertex->mDegList = new DegList;
     }
     if (destVertex->mDegList == NULL){
          destVertex->mDegList = new DegList;
     }
     // ������ degree List�� degree�� �߰�
     startVertex->mDegList->insertDeg(startVertexDegree);
     destVertex->mDegList->insertDeg(destVertexDegree);

     startVertex->degree++; // �л��� degree +1
     destVertex->degree++; 
     numOfLoad++;  // ���� �� +1

     cout << numOfLoad << endl;

}
// degree ��ü�� degree ����Ʈ�� �߰�
void DegList::insertDeg(Degree* degree){
     // ��ü�� ó������ �߰��ϴ� ���
     if (head == NULL){
          degree->prev = NULL;
          degree->next = NULL;
          head = degree;
          tail = degree;
     }
     // ������ ����Ʈ�� ��ü�� �߰��ϴ� ���(�������� �߰�)
     else{
          tail->next = degree;
          degree->prev = tail;
          degree->next = NULL;
          tail = degree;
     }
}
// ���� ��ü �������� ���� ����Ʈ�� �߰�
void EdgePtrList::insertEdgePtr(EdgePtr* edgePtr){
     // ��ü�� ó������ �߰��ϴ� ���
     if (head == NULL){
          edgePtr->prev = NULL;
          edgePtr->next = NULL;
          head = edgePtr;
          tail = edgePtr;
     }
     // ������ ����Ʈ�� ��ü�� �߰��ϴ� ���(�������� �߰�)
     else{
          tail->next = edgePtr;
          edgePtr->prev = tail;
          edgePtr->next = NULL;
          tail = edgePtr;
     }
}
// ========================================================================================
// 4. �л� ����
void G::deleteVertex(int stuId){
     // Vertex ��������
     // EdgePtr���� -> degree���� -> Edge���� -> Vertex ����-> vertexPtr ����
     VertexPtr* tempVertexPtr = List_VP.getVertexPtr(stuId);       // �л� ��ü ������ ����
     
     
     // �л��� ã�� ���� ���
     if (tempVertexPtr == NULL){
          cout << numOfStu << " " << numOfLoad << " Not found" << endl;
          return;
     }
     Vertex* tempVertex = tempVertexPtr->element_V();              // �л� ��ü ����
     DegList* tempDegList = tempVertex->mDegList;  // �л� ��ü�� degree ����Ʈ ����

     // �л� ��ü�� degree�� 0�ΰ��, ���õ� edge, degree�� �����Ƿ� �л���ü�� �ٷ� ���� ����
     if (tempDegList == NULL){
          List_VP.deleteVertexPtr(tempVertexPtr);
          delete tempVertex;
          numOfStu--;
          cout << numOfStu << " " << numOfLoad << endl;
          return;
     }

     Degree* tempDegree = tempDegList->head;       // dgree ����Ʈ�� head ����
     
     // ������ �л� ��ü�� degree�� �ش��ϴ� ��� ���θ� �����ϴ� ����
     while (tempDegree != NULL){
          Edge* tempEdge = tempDegree->edge;
          List_EP.deleteEdgePtr(tempEdge->mEdgePtr); // EdgePtr����
          
          // �����Ϸ��� ���� �ݴ����� �л� ��ü�� �����Ͽ� �ش� degree��ü ����
          if (tempEdge->startD != tempDegree){
               // degree ����Ʈ���� ���� degree��ü ����, ������ �����ϰ��ִ� degree��ü ����
               tempDegree = tempDegree->next; 
               tempEdge->startV->mDegList->deleteDeg(tempEdge->startD);
               tempEdge->startV->degree--;
               // ���� �������� degree List������ degree����
               tempEdge->destV->mDegList->deleteDeg(tempEdge->destD);
               tempEdge->destV->degree--;
          }
          else{
               tempDegree = tempDegree->next;
               tempEdge->destV->mDegList->deleteDeg(tempEdge->destD);
               tempEdge->destV->degree--;
               // ���� �������� degree List������ degree����
               tempEdge->startV->mDegList->deleteDeg(tempEdge->startD);
               tempEdge->startV->degree--;
          }

          delete tempEdge;   // Edge ����
          numOfLoad--;       // ���� ���� -1
     }

     delete tempVertex; // Vertex����
     List_VP.deleteVertexPtr(tempVertexPtr); // VertexPtr����
     numOfStu--;             // �л� ���� -1

     cout << numOfStu << " " << numOfLoad << endl;
     
}
// �л� ��ü ���� �� �ش� ������ ��ü ����
void VertexPtrList::deleteVertexPtr(VertexPtr* vertexPtr){
     // ������ �л� ������ ��ü�� ��ũ�� ������ �� �ش� ��ü ����
     // ������ �л� ������ ��ü�� �ϳ����� ���
     if (head == vertexPtr && tail == vertexPtr){
          head = NULL;
          tail = NULL;
     }
     // ������ �л� ������ ��ü�� head�� ���
     else if (head == vertexPtr){
          head = vertexPtr->next;
          head->prev = NULL;
     }
     // ������ �л� ������ ��ü�� tail�� ���
     else if (tail == vertexPtr){
          tail = vertexPtr->prev;
          tail->next = NULL;
     }
     // ������ �л� ������ ��ü�� List���� �߰��� ��ġ�� ���
     else{
          // ������ �л� ������ ��ü�� ��ũ�� ������ �� �ش� �л� ������ ��ü ����
          VertexPtr* tempVertexPtrPrev = vertexPtr->prev;
          vertexPtr->prev->next = vertexPtr->next;
          vertexPtr->next->prev = tempVertexPtrPrev;
     }
     delete vertexPtr;
}

// Degree ����Ʈ���� degree ��ü ����
void DegList::deleteDeg(Degree* degree){    
     // ������ degree ��ü�� �ϳ����� ���
     if (head == degree && tail == degree){
          head = NULL;
          tail = NULL;
     }
     // ������ degree ��ü�� head�� ���
     else if (head == degree){
          head = degree->next;
          head->prev = NULL;
     }
     // ������ degree ��ü�� tail�� ���
     else if (tail == degree){
          tail = degree->prev;
          tail->next = NULL;
     }
     // ������ degree ��ü�� List���� �߰��� ��ġ�� ���
     else{
          // ������ degree ��ü�� ��ũ�� ������ �� �ش� degree ��ü ����
          Degree* tempDegreePrev = degree->prev;
          degree->prev->next = degree->next;
          degree->next->prev = tempDegreePrev;
     }
     delete degree;
}
// ���� ����Ʈ���� ���� ������ ��ü ���� 
// **�л� ��ü ������ ���� �������� ��ġ�� ����ð� ���� ���ٰ���**
void EdgePtrList::deleteEdgePtr(EdgePtr* edgePtr){
     // ������ ���� ������ ��ü�� ��ũ�� ������ �� �ش� ��ü ����
     // ������ ���� ������ ��ü�� �ϳ����� ���
     if (head == edgePtr && tail == edgePtr){
          head = NULL;
          tail = NULL;
     }
     // ������ ���� ������ ��ü�� head�� ���
     else if (head == edgePtr){
          head = edgePtr->next;
          head->prev = NULL;
     }
     // ������ ���� ������ ��ü�� tail�� ���
     else if (tail == edgePtr){
          tail = edgePtr->prev;
          tail->next = NULL;
     }
     // ������ ���� ������ ��ü�� List���� �߰��� ��ġ�� ���
     else{
          // ������ ���� ������ ��ü�� ��ũ�� ������ �� �ش� ��ü ����
          EdgePtr* tempEdgePtrPrev = edgePtr->prev;
          edgePtr->prev->next = edgePtr->next;
          edgePtr->next->prev = tempEdgePtrPrev;
     }
     delete edgePtr;
     
}

// ========================================================================================
// 5. ���� ����
void G::deleteEdge(int roadId){
     // EdgePtr���� -> degree���� -> Edge���� -> Vertex ����-> vertexPtr ����
     EdgePtr* tempEdgePtr = List_EP.getEdgePtr(roadId);       // ���� ��ü ������ ����
     
     // ���θ� ã�� ���� ���
     if (tempEdgePtr == NULL){
          cout << numOfLoad << " Not found" << endl;
          return;
     }
     Edge* tempEdge = tempEdgePtr->element_E();               // ���� ��ü ����

     DegList* startDegreeList = tempEdge->startV->mDegList;  // ���� �л� ��ü�� degree ����Ʈ ����
     Degree* startDegree = tempEdge->startD;                 // ���� ���� �л� ��ü�� degree
     DegList* destDegreeList = tempEdge->destV->mDegList;    // ���� �л� ��ü�� degree ����Ʈ ����
     Degree* destDegree = tempEdge->destD;                   // ���� ���� �л� ��ü�� degree

     startDegreeList->deleteDeg(startDegree); // �л� ��ü�� degree List���� degree����
     destDegreeList->deleteDeg(destDegree);
     tempEdge->startV->degree--;              // �л� ��ü�� degree ���� -1
     tempEdge->destV->degree--;

     numOfLoad--;        // ���� ���� -1
     cout << numOfLoad << endl;
}

EdgePtr* EdgePtrList::getEdgePtr(int roadId){
     EdgePtr* tempEdgePtr = this->head;
     // head�������� Ž�� ����
     while (tempEdgePtr != NULL){
          if (tempEdgePtr->mEdge->roadId == roadId){
               return tempEdgePtr;
          }
          tempEdgePtr = tempEdgePtr->next;
     }
     // �й��� �ش��ϴ� ���� ��ü�� ã�� ���� ��� NULL ��ȯ
     return NULL;
}
// ========================================================================================
// 6. ����� ���� ���
void G::incidentEdges(int stuId){
     VertexPtr* tempVertexPtr = List_VP.getVertexPtr(stuId);

     // �־��� �й��� �ش��ϴ� �л� ������ ��ü�� ���� ���
     if (tempVertexPtr == NULL){
          cout << "Not found" << endl;
          return;
     }
     Vertex* tempVertex = tempVertexPtr->element_V();
     DegList* tempDegList = tempVertex->mDegList;
     Degree* tempDegree = tempDegList->head;

     // Degree List���� Degree���� ���
     cout << tempVertex->degree;
     // Degree List���� Degree�� �ش��ϴ� ���ι�ȣ Edge->roadId �� ���
     while (tempDegree != NULL){
          cout << " " << tempDegree->edge->roadId;
          tempDegree = tempDegree->next;
     }
     cout << endl;
}

// ========================================================================================
// 7. ���� ���� ��� 1
void G::endVertices(int roadId){
     EdgePtr* tempEdgePtr = List_EP.getEdgePtr(roadId);

     // �־��� ���ι�ȣ�� �ش��ϴ� ���� ������ ��ü�� ���� ���
     if (tempEdgePtr == NULL){
          cout << "Not found" << endl;
          return;
     }

     int stuId_1 = 0;
     int stuId_2 = 0;
     Edge* tempEdge = tempEdgePtr->element_E();

     // ���ΰ� ����Ű�� �л��� �й� ���
     stuId_1 = tempEdge->startV->stuId;
     stuId_2 = tempEdge->destV->stuId;

     // �й��� ���� �л��� �й��� ���� ���
     if (stuId_1 > stuId_2){
          cout << stuId_2 << " " << stuId_1 << endl;
     }
     else{
          cout << stuId_1 << " " << stuId_2 << endl;
     }
     
}
// ========================================================================================
// 8. ���� ���� ��� 2
void G::opposite(int stuId, int roadId){
     VertexPtr* tempVertexPtr = List_VP.getVertexPtr(stuId);
     EdgePtr* tempEdgePtr = List_EP.getEdgePtr(roadId);

     // �л��̳� ���θ� ã�� ���� ���
     if (tempVertexPtr == NULL || tempEdgePtr == NULL){
          cout << "Not available" << endl;
          return;
     }

     Vertex* tempVertx = tempVertexPtr->element_V();
     Edge* tempEdge = tempEdgePtr->element_E();

     // edge�� ���� �� �ϳ��� vertex�� ��� �ݴ� vertex�� �й� ���
     if (tempEdge->startV == tempVertx){
          cout << tempEdge->destV->stuId << endl;
     }
     else if (tempEdge->destV == tempVertx){
          cout << tempEdge->startV->stuId << endl;
     }
     // edge�� ���� �߿� vertex�� ���� ���
     else{
          cout << "Not available" << endl;
     }
     
}
// ========================================================================================
// 9. �������� ���� Ȯ��
void G::isAdjacentTo(int stuId_1, int stuId_2){
     VertexPtr* startVertexPtr = List_VP.getVertexPtr(stuId_1);
     VertexPtr* destVertexPtr = List_VP.getVertexPtr(stuId_2);
     // �־��� �й��� �ش��ϴ� �л� ������ ��ü�� ã�� ���� ���
     if (startVertexPtr == NULL || destVertexPtr == NULL){
          cout << "Not found" << endl;
          return;
     }
     Vertex* startVertex = startVertexPtr->element_V();
     Vertex* destVertex = destVertexPtr->element_V();
     // �־��� �й��� �ش��ϴ� �л���ü�� ���θ� ������ ���� ���� ���
     if (startVertex->degree == 0 || destVertex->degree == 0){
          cout << "Not found" << endl;
          return;
     }
     DegList* startDegList = startVertex->mDegList;
     DegList* destDegList = destVertex->mDegList;
     Degree* startDegree = startDegList->head;
     Degree* destDegree = destDegList->head;

     // �� �л� Vertex���� ���� ���� degree���� ���� �л� degree List���� Ž���� ����
     if (startVertex->degree > destVertex->degree){
          while (destDegree != NULL){
               // �������� �л� degree���� �������� �л� degree�� �� �� �ִ� ���
               if (destDegree->edge->startV == startVertex || destDegree->edge->destV == startVertex){
                    cout << destDegree->edge->roadId << endl;
                    return;
               }
               // Ž���� ������ ��� �� Degree List���� ���� degree�� �Ѿ��
               else{
                    destDegree = destDegree->next;
               }
          }
     }
     // ------------------ ���� ���� �����̳� Ž���� �����ϴ� �л� vertex�� �ٸ� ------
     else {
          while (startDegree != NULL){
               // �������� �л� degree���� �������� �л� degree�� �� �� �ִ� ���
               if (startDegree->edge->startV == destVertex || startDegree->edge->destV == destVertex){
                    cout << startDegree->edge->roadId << endl;
                    return;
               }
               // Ž���� ������ ��� �� Degree List���� ���� degree�� �Ѿ��
               else{
                    startDegree = startDegree->next;
               }
          }
     }

     // �� degree List�� ��� Ž���������� �ұ��ϰ� �� �л� ������ ���θ� �߰����� ���� ���
     cout << "Not found" << endl;

}

// ========================================================================================
// a. db�κ��� �л� �߰�
void G::insertVertex_db(int stuId, string eMail){
     Vertex* tempVertex = new Vertex(stuId, eMail);         // �л� ��ü 
     VertexPtr* tempVertexPtr = new VertexPtr(tempVertex);  // �л� ��ü�� �����ϴ� ������ ��ü
     tempVertex->mVertexPtr = tempVertexPtr;                // �л� ��ü�� ������ ��ü�� ����

     List_VP.insertVertexPtr(tempVertexPtr);                // ������ ��ü�� ����Ʈ�� �߰�
     numOfStu++;                                            // �л� �� +1
}
// b. db�κ��� ���� �߰�
void G::insertEdge_db(int roadId, int startStuId, int destStuId){
     VertexPtr* tempVertexPtr_s = List_VP.getVertexPtr(startStuId);
     VertexPtr* tempVertexPtr_d = List_VP.getVertexPtr(destStuId);

     // �л� ��ü�� �׷����� �������� �ʴ� ���
     if (tempVertexPtr_s == NULL || tempVertexPtr_d == NULL){
          cout << numOfLoad << " Not found" << endl;
          return;
     }
     Vertex* startVertex = tempVertexPtr_s->element_V(); // ������� �л� ��ü ����
     Vertex* destVertex = tempVertexPtr_d->element_V();  // ��ǥ���� �л� ��ü ����

     Edge* tempEdge = new Edge(roadId, startVertex, destVertex); // ���� ��ü ����

     // ���� ��ü�� ���� ������ ��ü�� ���� ���� �ϴ°���
     EdgePtr* tempEdgePtr = new EdgePtr(tempEdge);
     tempEdge->mEdgePtr = tempEdgePtr;
     // ���� ������ ��ü�� ���� ����Ʈ�� �߰�
     List_EP.insertEdgePtr(tempEdgePtr);
     // �� �л� ��ü�� ���� degree ��ü ���� 
     // -> degree�� edge�� ����
     // -> edge�� degree�� ����
     // -> �� degree�� �� degree����Ʈ�� �߰�
     Degree* startVertexDegree = new Degree(tempEdge);
     Degree* destVertexDegree = new Degree(tempEdge);
     tempEdge->startD = startVertexDegree;
     tempEdge->destD = destVertexDegree;

     // �� �л����� ó������ ���θ� �߰��ϴ� ��� (= ó������ degree List�� �߰��ϴ� ���)
     if (startVertex->mDegList == NULL){
          startVertex->mDegList = new DegList;
     }
     if (destVertex->mDegList == NULL){
          destVertex->mDegList = new DegList;
     }
     // ������ degree List�� degree�� �߰�
     startVertex->mDegList->insertDeg(startVertexDegree);
     destVertex->mDegList->insertDeg(destVertexDegree);

     startVertex->degree++; // �л��� degree +1
     destVertex->degree++;
     numOfLoad++;  // ���� �� +1
}



// --------------------------------------
/*


*/