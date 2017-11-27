#include "Tree_TripleLinkedList.h"

int main(){
     Tree_FourLinkedList<Node<string>> mTree; // string type만 받는 Node type만 받는 기본트리
     mTree.root->child = new Node<string>("2");
     mTree.root->child->parent = mTree.root;
     // 노드안에 다른 노드를 가리키는 주소값이 있다.
     // 그 주소값 즉 포인터 변수는 통일..?
     mTree.root->child->rightSibling = new Node<string>("33");
     mTree.root->child->rightSibling->leftSibling = mTree.root->child; // 역 참조
     mTree.root->child->rightSibling->parent = mTree.root; // 부모를 가리킴

     mTree.root->child->child = new Node<string>("55");
     mTree.root->child->child->parent = mTree.root->child; // 역 참조
     cout << mTree.root->txt << endl;
     cout << mTree.root->child->txt << endl;
     mTree.preOrder(mTree.root);
     cout << endl;
     mTree.postOrder(mTree.root);
     cout << endl;
     cout << "============" << endl;
     cout << "isEmpty() : " << mTree.isEmpty() << endl;

     
     delete mTree.root->child->rightSibling;
     delete mTree.root->child->child;
     delete mTree.root->child;
     delete mTree.root;
     return 0;
}