#ifndef _PROJECT_1_BINARYTREE_H_
#define _PROJECT_1_BINARYTREE_H_

#include<iostream>
using namespace std;

// 트리에서 사용하는 노드 클래스
class Node_B{
public:
     Node_B(){
          parent = NULL;
          leftChild = NULL;
          rightChild = NULL;
     }
     Node_B* parent; // 내부데이터 : 부모, 왼쪽자식, 오른쪽자식, 데이터
     Node_B* leftChild;
     Node_B* rightChild; // 사실은 같은 부모를 가지는 형제
     int element;
};

// 트리에서 사용하는 포지션 클래스
class Position_B{
public:
     Node_B* nodePtr_B;   // 내부 데이터 : 노드포인터
     int nodeNum;         // p가 가리키는 노드번호값
     Position_B(Node_B* po = NULL, int n = -1){
          nodePtr_B = po;
          nodeNum = n;
     }
     int& element(){
          return nodePtr_B->element;
     }
};

class BinaryTree{
public:
     BinaryTree(){
          rootPosition_B = NULL;
          rootNode_B = NULL;
          tempNode_B = NULL;
          size = 0;
          xPos = 0;
          yPos = 0;
          tempNodeNum = 0;
          recursionToParent = false;
     }
     ~BinaryTree(){
          
     }

     Position_B* root();
     Position_B* insert(Position_B* p, int nodeNum, int siblingOrder); // 이진트리의 삽입
     void printPositionXY(int nodeNum);  // 주어진 노드번호를 찾아 좌표를 출력하는 함수
     bool isInternal(Position_B* v);
     bool isExternal(Position_B* v);
     bool isRoot(Position_B* v);
     void preorder(Node_B* v);
     void postorder(Node_B* v);
     void inorder(Node_B* V);           // 좌표출력

private:
     Position_B* rootPosition_B;  // 루트 노드를 멤버 변수로 가지고 있는 포지션
     Node_B* rootNode_B;          // 루트 노드포인터
     Node_B* tempNode_B;          // 좌표출력에 사용할 임시 포인터 변수
     int size;                    // 트리 내에서 노드의 개수
     int xPos;                    // 노드의 x좌표
     int yPos;                    // 노드의 y좌표
     int tempNodeNum;             // 좌표출력 함수에서 쓸 거
     bool recursionToParent;             // 좌표출력 함수에서 쓸 조건
};

Position_B* BinaryTree::root(){
     return rootPosition_B;
}

bool BinaryTree::isInternal(Position_B* v){
     return (v->nodePtr_B->leftChild != NULL ? true : false); // 자식 노드가 있으면 true 리턴
}

bool BinaryTree::isExternal(Position_B* v){
     return (v->nodePtr_B->leftChild == NULL ? true : false); // 자식 노드가 없으면 true 리턴
}

bool BinaryTree::isRoot(Position_B* v){
     return  (v->nodePtr_B->parent == NULL ? true : false); // 부모 노드가 없으면 true 리턴

}

Position_B* BinaryTree::insert(Position_B* p, int nodeNum, int siblingOrder) {
     Node_B* n = new Node_B;                                // 노드 생성
     //=========1. 루트노드 삽입 시 =========
     if (p == NULL){                                        
          n->element = nodeNum;
          size++;
          rootNode_B = n;
          rootPosition_B = new Position_B(n, nodeNum);
          return rootPosition_B;
     }

     Node_B* tempParent = p->nodePtr_B;                     // p가 가리키는 노드의 주소 복사
     Node_B* tempLeftChild = tempParent->leftChild;         // p의 왼쪽 자식 복사
     Node_B* tempRightChild = NULL;

     //========= 2. 삽입될 노드의 부모노드의 자식이 없을경우, 첫번째 자식으로 삽입 =========
     if (tempParent->leftChild == NULL && siblingOrder == 1){
          n->element = nodeNum;              // 삽입될 노드의 번호 설정
          tempParent->leftChild = n;
          n->parent = tempParent;
          size++;                            // 추가되는 새로운 노드를 반영하여 트리가 가지고 있는 노드의 개수 업데이트
          return new Position_B(n, nodeNum); // 삽입된 노드의 번호와 주소를 가지는 포지션 객체 반환
     }
     //========= 3. 기존에 첫번째 자식이 있는데 그 자리에 삽입하는 경우 =========
     if (siblingOrder == 1){
          n->element = nodeNum;                        // 삽입될 노드의 번호 설정
          tempLeftChild = tempParent->leftChild;       // 기존의 첫번째 자식 주소 복사
          n->parent = tempParent;                      // 삽입될 노드의 부모 지정
          n->rightChild = tempLeftChild;               // 삽입될 노드의 오른쪽 자식(사실은 형제) 지정
          tempParent->leftChild = n;                   // 삽입될 노드를 부모노드의 왼쪽자식(첫번째 자식)으로 지정
          tempLeftChild->parent = n;                   // 기존의 첫째자식의 부모를 새로 삽입되는 노드로 설정
          size++;
          return new Position_B(n, nodeNum);
     }

     //========= 4. 2번째 이후의 자식으로 삽입하는 경우 =========
     tempRightChild = tempLeftChild;                   // 기존의 첫번째 자식 복사
     for (int currentOrder = 1; currentOrder < siblingOrder - 1; currentOrder++){
          // 사이에 들어갈 노드를 찾는 과정
          tempRightChild = tempRightChild->rightChild;
     }
     n->element = nodeNum;
     n->rightChild = tempRightChild->rightChild;       // 삽입될 노드의 오른쪽 자식(사실은 형제) 지정
     n->parent = tempRightChild;                       // 삽입될 노드의 부모노드 지정(전 단계의 형제)
     tempRightChild->rightChild = n;                   // 삽입될 노드의 앞 노드의 오른쪽 자식(사실은 형제)을 삽입되는 노드로 지정
     if (n->rightChild != NULL)
          n->rightChild->parent = n;                   // 삽입될 노드의 오른쪽 노드의 부모를 삽입되는 노드로 설정
     size++;
     return new Position_B(n, nodeNum);
}

void BinaryTree::printPositionXY(int nodeNum) {
     // 좌표 초기화
     xPos = 1;
     yPos = 0;
     tempNodeNum = nodeNum; // 좌표를 출력할 노드의 번호 설정, inorder함수에서 이 변수의 값을 참고
     inorder(rootNode_B);   // 좌표출력을 위하여 루트 노드를 매개변수로 전달

}

void BinaryTree::inorder(Node_B* v) {
     if (v->leftChild != NULL) {
          // 먼저 가장 왼쪽에 있는 노드를 찾아서 내려간다
          yPos++;
          inorder(v->leftChild);
          // 노드 v의 부모로 올라갈 경우 좌표값 수정
          // 노드 v의 왼쪽자식 에서 x좌표값을 더하고, y좌표값을 빼면서 부모노드로 올라감
          xPos++;
          yPos--;
     }
     // 주어진 노드번호에 해당하는 노드를 찾으면 그 노드의 좌표 출력 후 리턴
     // 해당 노드에 대한 처리 프로세스가 중간에 위치하므로 내려간 오른쪽자식이 왼쪽자식이 있을 경우 그 왼쪽자식을 고려하여 x좌표 설정 가능
     if (tempNodeNum == v->element) {
          cout << xPos << " " << yPos;
          return;
     }
     if (v->rightChild != NULL) {
          // 노드 v의 오른쪽 자식(형제)은 부모노드인 v보다 x,y가 큼
          xPos++;
          yPos++;
          inorder(v->rightChild);
          // 노드 v는 v의 오른쪽 자식(형제)보다 y좌표가 작음
          yPos--;
     }

}

#else
#endif