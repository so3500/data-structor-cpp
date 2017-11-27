#include "Tree_TripleLinkedList.h"

int main(){
     Tree_FourLinkedList<Node<string>> mTree; // string type�� �޴� Node type�� �޴� �⺻Ʈ��
     mTree.root->child = new Node<string>("2");
     mTree.root->child->parent = mTree.root;
     // ���ȿ� �ٸ� ��带 ����Ű�� �ּҰ��� �ִ�.
     // �� �ּҰ� �� ������ ������ ����..?
     mTree.root->child->rightSibling = new Node<string>("33");
     mTree.root->child->rightSibling->leftSibling = mTree.root->child; // �� ����
     mTree.root->child->rightSibling->parent = mTree.root; // �θ� ����Ŵ

     mTree.root->child->child = new Node<string>("55");
     mTree.root->child->child->parent = mTree.root->child; // �� ����
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