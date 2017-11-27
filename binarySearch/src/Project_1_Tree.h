#ifndef _PROJECT_1_TREE_H_
#define _PROJECT_1_TREE_H_

#include<iostream>
using namespace std;

// 트리에서 사용하는 노드 클래스
class Node{
public:
     Node(){
          parent = NULL;
          child = NULL;
          sibiling = NULL;
     }
     Node* parent; // 내부데이터 : 부모, 자식, 형제 포인터, 데이터
     Node* child;
     Node* sibiling;
     int element;
};

// 트리에서 사용하는 포지션 클래스
class Position{
public:
     Node* nodePtr; // 내부 데이터 : 노드포인터
     int nodeNum; // p가 가리키는 노드번호값
     Position(Node* po = NULL, int n = -1){
          nodePtr = po;
          nodeNum = n;
     }
     int& element(){
          return nodePtr->element;
     }
};

class Tree{
public:
     Tree(){
          rootPosition = NULL;
          rootNode = NULL;
          size = 0;
     }

     Position* root();
     Position* insert(Position* p, int nodeNum, int siblingOrder);
     bool isInternal(Position* v);
     bool isExternal(Position* v);
     bool isRoot(Position* v);
     void preorder(Node* v);
     void postorder(Node* v);

private:
     Position* rootPosition;  // 루트 노드를 멤버 변수로 가지고 있는 포지션
     Node* rootNode;          // 루트 노드포인터
     int size;                // 트리 내에서 노드의 개수

};

Position* Tree::root(){
     return rootPosition;
}

bool Tree::isInternal(Position* v){
     return (v->nodePtr->child != NULL ? true : false); // 자식 노드가 있으면 true 리턴
}

bool Tree::isExternal(Position* v){
     return (v->nodePtr->child == NULL ? true : false); // 자식 노드가 없으면 true 리턴
}

bool Tree::isRoot(Position* v){
     return  (v->nodePtr->parent == NULL ? true : false); // 부모 노드가 없으면 true 리턴
     
}

Position* Tree::insert(Position* p,int nodeNum, int siblingOrder){
     Node* n = new Node;                           // 노드 생성
     //=========1. 루트노드 삽입 시 =========
     if (p == NULL){                               // 루트노드 삽입 시 부모노드의 포지션이 NULL인 경우에 동작
          n->element = nodeNum;
          size++;
          rootNode = n;                            // n을 루트 노드로 설정
          rootPosition = new Position(n, nodeNum); // root노드의 Position객체 생성
          return rootPosition;
     }

     Node* tempParent = p->nodePtr;                // p가 가리키는 노드의 주소 복사
     Node* tempChild = tempParent->child;
     Node* tempSibling = NULL;

     //========= 2. 삽입될 노드의 부모노드의 자식이 없을경우, 첫번째 자식으로 삽입 =========
     if (tempParent->child == NULL && siblingOrder == 1){   
          n->element = nodeNum;                             // 삽입될 노드의 번호 설정
          tempParent->child = n;                            // 
          n->parent = tempParent;
          size++;                                           // 추가되는 새로운 노드를 반영하여 트리가 가지고 있는 노드의 개수 업데이트
          return new Position(n, nodeNum);                  // 삽입된 노드의 번호와 주소를 가지는 포지션 객체 반환
     }
     //========= 3. 기존에 첫번째 자식이 있는데 그 자리에 삽입하는 경우 =========
     if (siblingOrder == 1){
          n->element = nodeNum;                        // 삽입될 노드의 번호 설정
          tempChild = tempParent->child;               // 기존의 첫번째 자식 주소 복사
          n->parent = tempParent;                      // 삽입될 노드의 부모 지정
          n->sibiling = tempChild;                     // 삽입될 노드의 형제 지정
          tempParent->child = n;
          size++;
          return new Position(n, nodeNum);
     }

     //========= 4. 2번째 이후의 자식으로 삽입하는 경우 =========
     tempSibling = tempChild;                          // 기존의 첫번째 자식 복사
     for (int currentOrder = 1; currentOrder < siblingOrder-1; currentOrder++){
          // 기존에 있는 자식보다 더 뒤의 순위를 입력 받을 경우
          if (tempSibling->sibiling == NULL)
               break;
          // n번째 형제 노드가 되기위해 n-1번째의 형제 노드를 구하는 과정
          tempSibling = tempSibling->sibiling;
     }
     n->element = nodeNum;
     n->sibiling = tempSibling->sibiling;              // 삽입될 노드의 뒤 형제노드 지정
     n->parent = tempSibling->parent;                  // 삽입될 노드의 부모노드 지정
     tempSibling->sibiling = n;                        // 삽입될 노드의 앞 노드의 형제노드를 삽입되는 노드로 지정
     size++;
     return new Position(n, nodeNum);


}

void Tree::preorder(Node* v){
     cout << v->element << " "; // 부모->자식->형제 처리, 전위순회
     if (v->child != NULL)
          preorder(v->child);
     if (v->sibiling != NULL)
          preorder(v->sibiling);
     
}

void Tree::postorder(Node* v){
     if (v->child != NULL)  // 자식->형제->부모 처리, 후위순회
          postorder(v->child);
     cout << v->element << " ";
     if (v->sibiling != NULL)
          postorder(v->sibiling);

}



#else
#endif