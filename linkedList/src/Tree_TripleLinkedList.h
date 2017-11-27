#ifndef _TRIPLE_LINKED_LIST_H_
#define _TRIPLE_LINKED_LIST_H_


#include<iostream>
#include<string>
using namespace std;

template <class N>
class Node{
public:
     Node(){
          txt = "기본";
          parent = NULL;
          leftSibling = NULL;
          rightSibling = NULL;
          child = NULL;
     }
     Node(N n){
          txt = n;
          parent = NULL;
          leftSibling = NULL;
          rightSibling = NULL;
          child = NULL;
     }
     N txt;
     Node *parent;
     Node *leftSibling;
     Node *rightSibling;
     Node *child;
};

//???????????????????????
template <class P>
class Position{
public:

private:
};

template <class T>
class Tree_FourLinkedList{
public:
     Tree_FourLinkedList(){

          root = new T();
          tempPoint = NULL;
          numN = 1;
          numE = 1;
          numI = 0;
     }
     T *root;
     //T* root();
     void preOrder(T *t);
     void postOrder(T *t);
     int size();
     bool isEmpty();
     bool isRoot();
     bool isExternal();
     //void insertToChild(string txt);
     //void insertToSibling(string txt);

private:
     T *tempPoint;
     int numN;              // node의 수
     int numE;              // external node의 수
     int numI;              // internal node의 수
};

template <typename T>
void Tree_FourLinkedList<T>::preOrder(T *t){
     cout << t->txt << "->";       // visit, process에 해당
     if (t->child != NULL){
          preOrder(t->child);
     }
     if (t->rightSibling != NULL){
          preOrder(t->rightSibling);
     }

     return;
}
template <typename T>
void Tree_FourLinkedList<T>::postOrder(T *t){

     if (t->child != NULL){
          postOrder(t->child);
     }
     cout << t->txt << "->";       // visit, process에 해당
     if (t->rightSibling != NULL){
          postOrder(t->rightSibling);
     }
       
     return;
}

template <typename T>
int Tree_FourLinkedList<T>::size(){
     return numN;
}

template <typename T>
bool Tree_FourLinkedList<T>::isEmpty(){
     return root == NULL ? true : false;
}




#else
#endif