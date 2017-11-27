#ifndef _DOUBLE_LINKED_LIST_H_
#define _DOUBLE_LINKED_LIST_H_


#include<iostream>
#include<string>
using namespace std;

class Node{
public:
     string txt;
     Node *before;
     Node *next;
};

class LinkedList{
public:
     Node *tempPoint;
     Node *LinkHead;
     Node *LinkTail;

     LinkedList(){
          LinkHead = NULL;
          LinkTail = NULL;
     }
     void insertToHead(string txt);
     void insertToTail(string txt);
     void deleteFromHead();
     void deleteFromTail();
     void printFromHead();
     void printFromTail();
};

void LinkedList::insertToHead(string txt){
     Node *temp = new Node();
     temp->txt = txt;

     if (LinkHead == NULL && LinkTail == NULL){
          LinkHead = temp;
          LinkTail = temp;
          temp->before = NULL;
          temp->next = NULL;
     }
     else{
          tempPoint = LinkHead;
          tempPoint->before = temp;
          LinkHead = temp;              // ��� ����
          LinkHead->before = NULL;
          LinkHead->next = tempPoint;    // ���ο� ����� �����Ϳ� ���� ���
     }
}
void LinkedList::insertToTail(string txt){
     Node *temp = new Node();
     temp->txt = txt;

     if (LinkHead == NULL && LinkTail == NULL){
          LinkHead = temp;
          LinkTail = temp;
          temp->before = NULL;
          temp->next = NULL;
     }
     else{
          tempPoint = LinkTail;      // ������ ���� ����
          tempPoint->next = temp;    // ������ ������ ���ο� ��� �߰�
          temp->before = tempPoint;  // �߰��� ���ο� ����� �ճ��� ������ ���� ����
          temp->next = NULL;         // ���ο� ����� ������ ��
          LinkTail = temp;           // ������ ���� �߰��� ���� �ٲ�

     }
}
void LinkedList::deleteFromHead(){
     if (LinkHead != NULL){
          tempPoint = LinkHead->next; // �Ӹ��� ���� ��� �ּ�����
          LinkHead->next = NULL;      // �Ӹ��� ����Ʈ�κ��� ����
          free(LinkHead);             // ������ �Ӹ� ����
          LinkHead = tempPoint;       // �Ӹ� ���� ��带 ���ο� �Ӹ��� ����
          LinkHead->before = NULL;
     }
     else{
          cout << "������ ��尡 �����ϴ�" << endl;
     }
}
void LinkedList::deleteFromTail(){
     if (LinkTail != NULL){
          tempPoint = LinkTail->before; // ������ �� ��� �ּ� ����
          LinkTail->before = NULL;      // ���� ��带 ����Ʈ�κ��� ����
          free(LinkTail);               // ������ ���� ����
          LinkTail = tempPoint;         // ������ �� ��带 ������ ����
          LinkTail->next = NULL;
     }
     else {
          cout << "������ ��尡 �����ϴ�" << endl;
     }
}
void LinkedList::printFromHead(){
     if (LinkHead != NULL){
          tempPoint = LinkHead;
          while (tempPoint->next != NULL){
               cout << tempPoint->txt << " -> ";
               tempPoint = tempPoint->next;
          }
          cout << tempPoint->txt << endl << endl;
     }
     else{
          cout << "����� ��尡 �����ϴ�" << endl;
     }
}
void LinkedList::printFromTail(){
     if (LinkTail != NULL){
          tempPoint = LinkTail;
          while (tempPoint->before != NULL){
               cout << tempPoint->txt << " -> ";
               tempPoint = tempPoint->before;
          }
          cout << tempPoint->txt << endl << endl;
     }
     else{
          cout << "����� ��尡 �����ϴ�" << endl;
     }
}






#else
#endif