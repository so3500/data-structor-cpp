#ifndef _PROJECT_1_TREE_H_
#define _PROJECT_1_TREE_H_

#include<iostream>
using namespace std;

// Ʈ������ ����ϴ� ��� Ŭ����
class Node{
public:
     Node(){
          parent = NULL;
          child = NULL;
          sibiling = NULL;
     }
     Node* parent; // ���ε����� : �θ�, �ڽ�, ���� ������, ������
     Node* child;
     Node* sibiling;
     int element;
};

// Ʈ������ ����ϴ� ������ Ŭ����
class Position{
public:
     Node* nodePtr; // ���� ������ : ���������
     int nodeNum; // p�� ����Ű�� ����ȣ��
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
     Position* rootPosition;  // ��Ʈ ��带 ��� ������ ������ �ִ� ������
     Node* rootNode;          // ��Ʈ ���������
     int size;                // Ʈ�� ������ ����� ����

};

Position* Tree::root(){
     return rootPosition;
}

bool Tree::isInternal(Position* v){
     return (v->nodePtr->child != NULL ? true : false); // �ڽ� ��尡 ������ true ����
}

bool Tree::isExternal(Position* v){
     return (v->nodePtr->child == NULL ? true : false); // �ڽ� ��尡 ������ true ����
}

bool Tree::isRoot(Position* v){
     return  (v->nodePtr->parent == NULL ? true : false); // �θ� ��尡 ������ true ����
     
}

Position* Tree::insert(Position* p,int nodeNum, int siblingOrder){
     Node* n = new Node;                           // ��� ����
     //=========1. ��Ʈ��� ���� �� =========
     if (p == NULL){                               // ��Ʈ��� ���� �� �θ����� �������� NULL�� ��쿡 ����
          n->element = nodeNum;
          size++;
          rootNode = n;                            // n�� ��Ʈ ���� ����
          rootPosition = new Position(n, nodeNum); // root����� Position��ü ����
          return rootPosition;
     }

     Node* tempParent = p->nodePtr;                // p�� ����Ű�� ����� �ּ� ����
     Node* tempChild = tempParent->child;
     Node* tempSibling = NULL;

     //========= 2. ���Ե� ����� �θ����� �ڽ��� �������, ù��° �ڽ����� ���� =========
     if (tempParent->child == NULL && siblingOrder == 1){   
          n->element = nodeNum;                             // ���Ե� ����� ��ȣ ����
          tempParent->child = n;                            // 
          n->parent = tempParent;
          size++;                                           // �߰��Ǵ� ���ο� ��带 �ݿ��Ͽ� Ʈ���� ������ �ִ� ����� ���� ������Ʈ
          return new Position(n, nodeNum);                  // ���Ե� ����� ��ȣ�� �ּҸ� ������ ������ ��ü ��ȯ
     }
     //========= 3. ������ ù��° �ڽ��� �ִµ� �� �ڸ��� �����ϴ� ��� =========
     if (siblingOrder == 1){
          n->element = nodeNum;                        // ���Ե� ����� ��ȣ ����
          tempChild = tempParent->child;               // ������ ù��° �ڽ� �ּ� ����
          n->parent = tempParent;                      // ���Ե� ����� �θ� ����
          n->sibiling = tempChild;                     // ���Ե� ����� ���� ����
          tempParent->child = n;
          size++;
          return new Position(n, nodeNum);
     }

     //========= 4. 2��° ������ �ڽ����� �����ϴ� ��� =========
     tempSibling = tempChild;                          // ������ ù��° �ڽ� ����
     for (int currentOrder = 1; currentOrder < siblingOrder-1; currentOrder++){
          // ������ �ִ� �ڽĺ��� �� ���� ������ �Է� ���� ���
          if (tempSibling->sibiling == NULL)
               break;
          // n��° ���� ��尡 �Ǳ����� n-1��°�� ���� ��带 ���ϴ� ����
          tempSibling = tempSibling->sibiling;
     }
     n->element = nodeNum;
     n->sibiling = tempSibling->sibiling;              // ���Ե� ����� �� ������� ����
     n->parent = tempSibling->parent;                  // ���Ե� ����� �θ��� ����
     tempSibling->sibiling = n;                        // ���Ե� ����� �� ����� ������带 ���ԵǴ� ���� ����
     size++;
     return new Position(n, nodeNum);


}

void Tree::preorder(Node* v){
     cout << v->element << " "; // �θ�->�ڽ�->���� ó��, ������ȸ
     if (v->child != NULL)
          preorder(v->child);
     if (v->sibiling != NULL)
          preorder(v->sibiling);
     
}

void Tree::postorder(Node* v){
     if (v->child != NULL)  // �ڽ�->����->�θ� ó��, ������ȸ
          postorder(v->child);
     cout << v->element << " ";
     if (v->sibiling != NULL)
          postorder(v->sibiling);

}



#else
#endif