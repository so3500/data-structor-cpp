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
     // Node class�� ����
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
     // Position class�� ����
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
          friend class NodeList<Object>; // NodeList Ŭ������ Position�� nodePtr�� ���� �����ϵ��� ��
     };

protected:
     // Position�� ��� �����ͷ� ��ȯ�ϴ� Ȱ���Լ�
     Node* nodePtr(Position& p) const throw(InvalidPositionException) {
          if (p.nodePtr == NULL)
               throw InvalidPositionException("Attempt to use null position");
          else
               return p.nodePtr;
     }
     // NodeList�� ��� ����
     Node* head;            // head �� �� ���
     Node* tail;            // tail �� �� ���
     int list_size;
     

public:
     // NodeList�� ��� �Լ�
     NodeList(){
          head = new Node();
          tail = new Node();
          head->next = tail;       // head�� �հ� tail�� �ڴ� ���� ��� NULL�� �ʱ�ȭ �Ǿ�����
          tail->prev = head;
          list_size = 0;           // NodeListŬ������ ��ü ������� ��� ������ 0��
     }
     
     // å�� �ִ� �Լ���
     /*
     // ���� �Լ�
     int size() const;
     bool isEmpty() const;
     bool isFirst(const Position& p) const throw(InvalidPositionException); // call by Reference�� ����. call by value �϶� �Լ� ������ p�� �̿��� ������ �ϸ� �� ����� ������ p�� �ݿ��� �ȵǹǷ�.., ���� ������ ���� p�� �����Ͽ� �Լ��� �Ű������� �ѱ��. �׸��� �Լ��� ������ �Լ����� ������ �����ǹǷ� ����� p�� ���� �Ҹ�(�������)
     bool isLast(const Position& p) const throw(InvalidPositionException);

     // ���� �Լ�
     Position first() const throw(InvalidPositionException);
     Position last() const throw(InvalidPositionException);
     Position before(const Position& p) const throw(InvalidPositionException, BoundaryViolationException);
     Position after(const Position& p) const throw(InvalidPositionException, BoundaryViolationException);
     */

     // ���� �Լ�
     int size() const;
     bool isEmpty();
     // �����Լ�
     Position insertFront(Object& element);
     Position insertBack(Object& element);
     Position insert(Position& p, Object& element) const throw(InvalidPositionException); // �տ� �ִ°ɷ�
     void RemoveFront() const throw(EmptyContainerException);
     void RemoveBack() const throw(EmptyContainerException);
     void remove(Position& p) const throw(InvalidPositionException);
     // �����Լ�
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
     // Node* n = new Node(element, head, head->next); // ������ element ���� head, �ڴ� head�� ���� ��� ����
     Node* n = new Node();
     n->element = element;
     n->prev = head;
     n->next = head->next; // �ɱ�
     head->next->prev = n;
     head->next = n;
     list_size++;
     return Position(n);
}

template <typename Object>
typename NodeList<Object>::Position NodeList<Object>::insertBack(Object& element) {
     // Node* n = new Node(element, tail->prev, tail); // ������ element ���� tail�� ��, �ڴ� tail �� ��� ����
     Node* n = new Node();
     n->element = element;
     n->prev = tail->prev;
     n->next = tail;
     tail->prev->next = n;
     tail->preve = n;
     list_size++;
     return Position(n);
}

// p���̶�� ����
template <typename Object>
typename NodeList<Object>::Position NodeList<Object>::insert(Position& p, Object& element) const throw(InvalidPositionException) {
     Node* n = new Node();
     Node* tempPoint = nodePtr(p); // p�� ����Ű�� ����� �ּ� ��ȯ
     n->element = element;
     n->prev = tempPoint->prev;
     n->next = tempPoint;          // �ɱ�
     tempPoint->prev->next = n;
     tempPoint->prev = n;
     //list_size++;
     return Position(n);           // ���� ������ ��� n�� �ּҸ� ��������� ������ Position ��ü ��ȯ
     
}

template <typename Object>
void NodeList<Object>::RemoveFront() const throw(EmptyContainerException) {
     if (isEmpty() == NULL)
          throw EmptyContainerException("there is no Front node");
     
     Node* tempPoint = head->next;
     head->next = tempPoint->next;
     head->next->next->prev = head; // ����
     cout << "�� ���� ��� : " << tempPoint->element << " ���� �Ϸ�" << endl << endl;
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
     cout << "�� ���� ��� : " << tempPoint->element << " ���� �Ϸ�" << endl << endl;
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
     cout << " ��� : " << tempPoint->element << " ���� �Ϸ� " << endl << endl;
     delete tempPoint;
     list_size--;
}
// �����Լ�
// ���� �� ��忡 ���� position ��ü ��ȯ
template <typename Object>
typename NodeList<Object>::Position NodeList<Object>::begin() const throw(EmptyContainerException) {
     if (isEmpty())
          throw EmptyContainerException("List is Empty");
     return Position(head->next);
}
// ���� �� ��忡 ���� position ��ü ��ȯ
template <typename Object>
typename NodeList<Object>::Position NodeList<Object>::end() const throw(EmptyContainerException) {
     if (isEmpty())
          throw EmptyContainerException("List is Empty");
     return Position(tail->prev);
}

// ���� Ŭ����
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

// ��� ħ�� ����, before(p) ���� p�� �Ǿ��� ��, if(p->prev == head)
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