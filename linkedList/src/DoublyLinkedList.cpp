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
          LinkHead = temp;              // 헤드 변경
          LinkHead->before = NULL;
          LinkHead->next = tempPoint;    // 새로운 헤드의 다음것에 기존 헤드
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
          tempPoint = LinkTail;      // 현재의 꼬리 참조
          tempPoint->next = temp;    // 꼬리의 다음에 새로운 노드 추가
          temp->before = tempPoint;  // 추가한 새로운 노드의 앞노드로 기존의 꼬리 참조
          temp->next = NULL;         // 새로운 노드의 다음은 널
          LinkTail = temp;           // 꼬리를 새로 추가한 노드로 바꿈

     }
}
void LinkedList::deleteFromHead(){
     if (LinkHead != NULL){
          tempPoint = LinkHead->next; // 머리의 다음 노드 주소참조
          LinkHead->next = NULL;      // 머리를 리스트로부터 떼기
          free(LinkHead);             // 기존의 머리 삭제
          LinkHead = tempPoint;       // 머리 다음 노드를 새로운 머리로 지정
          LinkHead->before = NULL;
     }
     else{
          cout << "삭제할 노드가 없습니다" << endl;
     }
}
void LinkedList::deleteFromTail(){
     if (LinkTail != NULL){
          tempPoint = LinkTail->before; // 꼬리의 앞 노드 주소 참조
          LinkTail->before = NULL;      // 꼬리 노드를 리스트로부터 떼기
          free(LinkTail);               // 기존의 꼬리 삭제
          LinkTail = tempPoint;         // 꼬리의 앞 노드를 꼬리로 지정
          LinkTail->next = NULL;
     }
     else {
          cout << "삭제할 노드가 없습니다" << endl;
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
          cout << "출력할 노드가 없습니다" << endl;
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
          cout << "출력할 노드가 없습니다" << endl;
     }
}

int main(){
     LinkedList *DoublyLinkedList = new LinkedList();
     int control = 0;
     bool goStop = true;
     string insertString = "";
     
     while (goStop) {
          cout << "메뉴를 입력하세요. " << endl;
          cout << "1. 링크드 리스트 추가(머리부터)" << endl
               << "2. 링크드 리스트 추가(꼬리부터)" << endl
               << "3. 링크드 리스트 목록 보기(머리부터)" << endl
               << "4. 링크드 리스트 목록 보기(꼬리부터)" << endl
               << "5. 링크드 리스트 삭제(머리부터)" << endl
               << "6. 링크드 리스트 삭제(꼬리부터)" << endl
               << "7. 종료" << endl;
          cin >> control;
          switch (control){
          case 1:
               cin >> insertString;
               DoublyLinkedList->insertToHead(insertString);
               cout << endl;
               break;
          case 2:
               cin >> insertString;
               DoublyLinkedList->insertToTail(insertString);
               break;
          case 3:
               DoublyLinkedList->printFromHead();
               break;
          case 4:
               DoublyLinkedList->printFromTail();
               break;
          case 5:
               DoublyLinkedList->deleteFromHead();
               break;
          case 6:
               DoublyLinkedList->deleteFromTail();
               break;
          case 7:
               goStop = false;
               break;
          }
     }

     return 0;
}