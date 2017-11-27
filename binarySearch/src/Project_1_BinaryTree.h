#ifndef _PROJECT_1_BINARYTREE_H_
#define _PROJECT_1_BINARYTREE_H_

#include<iostream>
using namespace std;

// Ʈ������ ����ϴ� ��� Ŭ����
class Node_B{
public:
     Node_B(){
          parent = NULL;
          leftChild = NULL;
          rightChild = NULL;
     }
     Node_B* parent; // ���ε����� : �θ�, �����ڽ�, �������ڽ�, ������
     Node_B* leftChild;
     Node_B* rightChild; // ����� ���� �θ� ������ ����
     int element;
};

// Ʈ������ ����ϴ� ������ Ŭ����
class Position_B{
public:
     Node_B* nodePtr_B;   // ���� ������ : ���������
     int nodeNum;         // p�� ����Ű�� ����ȣ��
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
     Position_B* insert(Position_B* p, int nodeNum, int siblingOrder); // ����Ʈ���� ����
     void printPositionXY(int nodeNum);  // �־��� ����ȣ�� ã�� ��ǥ�� ����ϴ� �Լ�
     bool isInternal(Position_B* v);
     bool isExternal(Position_B* v);
     bool isRoot(Position_B* v);
     void preorder(Node_B* v);
     void postorder(Node_B* v);
     void inorder(Node_B* V);           // ��ǥ���

private:
     Position_B* rootPosition_B;  // ��Ʈ ��带 ��� ������ ������ �ִ� ������
     Node_B* rootNode_B;          // ��Ʈ ���������
     Node_B* tempNode_B;          // ��ǥ��¿� ����� �ӽ� ������ ����
     int size;                    // Ʈ�� ������ ����� ����
     int xPos;                    // ����� x��ǥ
     int yPos;                    // ����� y��ǥ
     int tempNodeNum;             // ��ǥ��� �Լ����� �� ��
     bool recursionToParent;             // ��ǥ��� �Լ����� �� ����
};

Position_B* BinaryTree::root(){
     return rootPosition_B;
}

bool BinaryTree::isInternal(Position_B* v){
     return (v->nodePtr_B->leftChild != NULL ? true : false); // �ڽ� ��尡 ������ true ����
}

bool BinaryTree::isExternal(Position_B* v){
     return (v->nodePtr_B->leftChild == NULL ? true : false); // �ڽ� ��尡 ������ true ����
}

bool BinaryTree::isRoot(Position_B* v){
     return  (v->nodePtr_B->parent == NULL ? true : false); // �θ� ��尡 ������ true ����

}

Position_B* BinaryTree::insert(Position_B* p, int nodeNum, int siblingOrder) {
     Node_B* n = new Node_B;                                // ��� ����
     //=========1. ��Ʈ��� ���� �� =========
     if (p == NULL){                                        
          n->element = nodeNum;
          size++;
          rootNode_B = n;
          rootPosition_B = new Position_B(n, nodeNum);
          return rootPosition_B;
     }

     Node_B* tempParent = p->nodePtr_B;                     // p�� ����Ű�� ����� �ּ� ����
     Node_B* tempLeftChild = tempParent->leftChild;         // p�� ���� �ڽ� ����
     Node_B* tempRightChild = NULL;

     //========= 2. ���Ե� ����� �θ����� �ڽ��� �������, ù��° �ڽ����� ���� =========
     if (tempParent->leftChild == NULL && siblingOrder == 1){
          n->element = nodeNum;              // ���Ե� ����� ��ȣ ����
          tempParent->leftChild = n;
          n->parent = tempParent;
          size++;                            // �߰��Ǵ� ���ο� ��带 �ݿ��Ͽ� Ʈ���� ������ �ִ� ����� ���� ������Ʈ
          return new Position_B(n, nodeNum); // ���Ե� ����� ��ȣ�� �ּҸ� ������ ������ ��ü ��ȯ
     }
     //========= 3. ������ ù��° �ڽ��� �ִµ� �� �ڸ��� �����ϴ� ��� =========
     if (siblingOrder == 1){
          n->element = nodeNum;                        // ���Ե� ����� ��ȣ ����
          tempLeftChild = tempParent->leftChild;       // ������ ù��° �ڽ� �ּ� ����
          n->parent = tempParent;                      // ���Ե� ����� �θ� ����
          n->rightChild = tempLeftChild;               // ���Ե� ����� ������ �ڽ�(����� ����) ����
          tempParent->leftChild = n;                   // ���Ե� ��带 �θ����� �����ڽ�(ù��° �ڽ�)���� ����
          tempLeftChild->parent = n;                   // ������ ù°�ڽ��� �θ� ���� ���ԵǴ� ���� ����
          size++;
          return new Position_B(n, nodeNum);
     }

     //========= 4. 2��° ������ �ڽ����� �����ϴ� ��� =========
     tempRightChild = tempLeftChild;                   // ������ ù��° �ڽ� ����
     for (int currentOrder = 1; currentOrder < siblingOrder - 1; currentOrder++){
          // ���̿� �� ��带 ã�� ����
          tempRightChild = tempRightChild->rightChild;
     }
     n->element = nodeNum;
     n->rightChild = tempRightChild->rightChild;       // ���Ե� ����� ������ �ڽ�(����� ����) ����
     n->parent = tempRightChild;                       // ���Ե� ����� �θ��� ����(�� �ܰ��� ����)
     tempRightChild->rightChild = n;                   // ���Ե� ����� �� ����� ������ �ڽ�(����� ����)�� ���ԵǴ� ���� ����
     if (n->rightChild != NULL)
          n->rightChild->parent = n;                   // ���Ե� ����� ������ ����� �θ� ���ԵǴ� ���� ����
     size++;
     return new Position_B(n, nodeNum);
}

void BinaryTree::printPositionXY(int nodeNum) {
     // ��ǥ �ʱ�ȭ
     xPos = 1;
     yPos = 0;
     tempNodeNum = nodeNum; // ��ǥ�� ����� ����� ��ȣ ����, inorder�Լ����� �� ������ ���� ����
     inorder(rootNode_B);   // ��ǥ����� ���Ͽ� ��Ʈ ��带 �Ű������� ����

}

void BinaryTree::inorder(Node_B* v) {
     if (v->leftChild != NULL) {
          // ���� ���� ���ʿ� �ִ� ��带 ã�Ƽ� ��������
          yPos++;
          inorder(v->leftChild);
          // ��� v�� �θ�� �ö� ��� ��ǥ�� ����
          // ��� v�� �����ڽ� ���� x��ǥ���� ���ϰ�, y��ǥ���� ���鼭 �θ���� �ö�
          xPos++;
          yPos--;
     }
     // �־��� ����ȣ�� �ش��ϴ� ��带 ã���� �� ����� ��ǥ ��� �� ����
     // �ش� ��忡 ���� ó�� ���μ����� �߰��� ��ġ�ϹǷ� ������ �������ڽ��� �����ڽ��� ���� ��� �� �����ڽ��� ����Ͽ� x��ǥ ���� ����
     if (tempNodeNum == v->element) {
          cout << xPos << " " << yPos;
          return;
     }
     if (v->rightChild != NULL) {
          // ��� v�� ������ �ڽ�(����)�� �θ����� v���� x,y�� ŭ
          xPos++;
          yPos++;
          inorder(v->rightChild);
          // ��� v�� v�� ������ �ڽ�(����)���� y��ǥ�� ����
          yPos--;
     }

}

#else
#endif