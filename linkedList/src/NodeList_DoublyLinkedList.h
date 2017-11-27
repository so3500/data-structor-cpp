#ifndef _NODE_LIST_DOUBLY_LINKED_LIST_H_
#define _NODE_LIST_DOUBLY_LINKED_LIST_H_
#include <iostream>
using namespace std;

class RuntimeException;
class InvalidPositionException;
class BoundaryViolationException;
class EmptyContainerException;



template <typename Object>
class NodeList {
protected:
     // Node class의 정의
     class Node{
     public:
          Node(Object e = Object(), Node* p = NULL, Node* n = NULL){
               element = e;
               prev = p;
               next = n;
          }
          
          Object element;
          Node* prev;
          Node* next;      
     };
     //typedef Node* NodePtr;

public:
     // Position class의 정의
     class Position{
     private:
          Node* nodePtr;
     public:
          Position(Node* n = NULL){
               nodePtr = n;
          }
          Object& element() const throw (InvalidPositionException) {
               if (nodePtr == NULL)
                    throw InvalidPositionException("Null position");

               return nodePtr->element;
          }
          bool isNull() const {
               return nodePtr == NULL;
          }
          friend class NodeList<Object>; // NodeList 클래스가 Position의 nodePtr에 접근 가능하도록 함
     };

protected:
     // Position을 노드 포인터로 변환하는 활용함수
     Node* nodePtr(Position& p) const throw(InvalidPositionException) {
          if (p.nodePtr == NULL)
               throw InvalidPositionException("Attempt to use null position");
          else
               return p.nodePtr;
     }
     // NodeList의 멤버 변수
     Node* head;            // head 의 앞 노드
     Node* tail;            // tail 의 뒤 노드
     int list_size;
     

public:
     // NodeList의 멤버 함수
     NodeList(){
          head = new Node();
          tail = new Node();
          head->next = tail;       // head의 앞과 tail의 뒤는 선언 당시 NULL로 초기화 되어있음
          tail->prev = head;
          list_size = 0;           // NodeList클래스형 객체 생성당시 요소 개수는 0개
     }
     
     // 책에 있는 함수명
     /*
     // 질의 함수
     int size() const;
     bool isEmpty() const;
     bool isFirst(const Position& p) const throw(InvalidPositionException); // call by Reference인 이유. call by value 일때 함수 내에서 p를 이용한 연산을 하면 그 결과가 기존의 p에 반영이 안되므로.., 같은 내용을 가진 p를 복사하여 함수의 매개변수로 넘긴다. 그리고 함수가 끝나면 함수관련 스택이 해제되므로 복사된 p도 같이 소멸(어셈블리어)
     bool isLast(const Position& p) const throw(InvalidPositionException);

     // 접근 함수
     Position first() const throw(InvalidPositionException);
     Position last() const throw(InvalidPositionException);
     Position before(const Position& p) const throw(InvalidPositionException, BoundaryViolationException);
     Position after(const Position& p) const throw(InvalidPositionException, BoundaryViolationException);
     */

     // 질의 함수
     int size() const;
     bool isEmpty();
     // 수정함수
     Position insertFront(Object& element);
     Position insertBack(Object& element);
     Position insert(Position& p, Object& element) const throw(InvalidPositionException); // 앞에 넣는걸로
     void RemoveFront() const throw(EmptyContainerException);
     void RemoveBack() const throw(EmptyContainerException);
     void remove(Position& p) const throw(InvalidPositionException);
     // 접근함수
     Position begin() const throw(EmptyContainerException);
     Position end() const throw(EmptyContainerException);

     void printAll();

};
template <typename Object>
void NodeList<Object>::printAll() {
     Node* n = head->next;
     while (n->next != NULL) {
          cout << n->element << " > ";
          n = n->next;
     }
}

template <typename Object>
int NodeList<Object>::size() const {
     return list_size;
}

template <typename Object>
bool NodeList<Object>::isEmpty() {
     return list_size == 0 ? true : false; 
};

template <typename Object>
typename NodeList<Object>::Position NodeList<Object>::insertFront(Object& element) {
     // Node* n = new Node(element, head, head->next); // 내용은 element 앞은 head, 뒤는 head의 뒤인 노드 선언
     Node* n = new Node();
     n->element = element;
     n->prev = head;
     n->next = head->next; // 걸기
     head->next->prev = n;
     head->next = n;
     list_size++;
     return Position(n);
}

template <typename Object>
typename NodeList<Object>::Position NodeList<Object>::insertBack(Object& element) {
     // Node* n = new Node(element, tail->prev, tail); // 내용은 element 앞은 tail의 앞, 뒤는 tail 인 노드 선언
     Node* n = new Node();
     n->element = element;
     n->prev = tail->prev;
     n->next = tail;
     tail->prev->next = n;
     tail->preve = n;
     list_size++;
     return Position(n);
}

// p앞이라고 생각
template <typename Object>
typename NodeList<Object>::Position NodeList<Object>::insert(Position& p, Object& element) const throw(InvalidPositionException) {
     Node* n = new Node();
     Node* tempPoint = nodePtr(p); // p가 가리키는 노드의 주소 반환
     n->element = element;
     n->prev = tempPoint->prev;
     n->next = tempPoint;          // 걸기
     tempPoint->prev->next = n;
     tempPoint->prev = n;
     //list_size++;
     return Position(n);           // 새로 생성된 노드 n의 주소를 멤버변수로 가지는 Position 객체 반환
     
}

template <typename Object>
void NodeList<Object>::RemoveFront() const throw(EmptyContainerException) {
     if (isEmpty() == NULL)
          throw EmptyContainerException("there is no Front node");
     
     Node* tempPoint = head->next;
     head->next = tempPoint->next;
     head->next->next->prev = head; // 해제
     cout << "맨 앞의 노드 : " << tempPoint->element << " 삭제 완료" << endl << endl;
     //list_size--;
     delete tempPoint;
}

template <typename Object>
void NodeList<Object>::RemoveBack() const throw(EmptyContainerException) {
     if (list_size == 0)
          throw EmptyContainerException("there is no Back node");

     Node* tempPoint = tail->prev;
     tail->prev = tempPoint->prev;
     tail->prev->prev->next = tail;
     cout << "맨 뒤의 노드 : " << tempPoint->element << " 삭제 완료" << endl << endl;
     //list_size--;
     delete tempPoint;
}

template <typename Object>
void NodeList<Object>::remove(Position& p) const throw(InvalidPositionException) {
     if (nodePtr(p) == NULL)
          throw InvalidPositionException("there is no element!");

     Node* tempPoint = nodePtr(p);
     tempPoint->prev->next = tempPoint->next;
     tempPoint->next->prev = tempPoint->prev;
     cout << " 노드 : " << tempPoint->element << " 삭제 완료 " << endl << endl;
     delete tempPoint;
     list_size--;
}
// 접근함수
// 가장 앞 노드에 대한 position 객체 반환
template <typename Object>
typename NodeList<Object>::Position NodeList<Object>::begin() const throw(EmptyContainerException) {
     if (isEmpty())
          throw EmptyContainerException("List is Empty");
     return Position(head->next);
}
// 가장 뒤 노드에 대한 position 객체 반환
template <typename Object>
typename NodeList<Object>::Position NodeList<Object>::end() const throw(EmptyContainerException) {
     if (isEmpty())
          throw EmptyContainerException("List is Empty");
     return Position(tail->prev);
}

// 예외 클래스
class RuntimeException {
private:
     string errorMsg;
public:
     RuntimeException(const string& err) { errorMsg = err; }
     string getMessage() const{ return errorMsg; }

};
class InvalidPositionException : public RuntimeException {
public:
     InvalidPositionException(const string& err) : RuntimeException(err){}
};

class EmptyContainerException : public RuntimeException {
public:
     EmptyContainerException(const string& err) : RuntimeException(err){}
};

// 경계 침입 예외, before(p) 에서 p가 맨앞일 때, if(p->prev == head)
class BoundaryViolationException : public RuntimeException {
public:
     BoundaryViolationException(const string& err) : RuntimeException(err){}
};



inline std::ostream& operator << (std::ostream& out, const RuntimeException& e)
{
     return out << e.getMessage();
}


#else
#endif