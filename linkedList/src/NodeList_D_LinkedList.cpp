#include "NodeList_DoublyLinkedList.h"

int main(){

     try{
    NodeList<int> mNodeList;
    NodeList<int>::Position p1,p2,p3,p4;
    mNodeList.RemoveBack();

    int a = 0;
    p1 = mNodeList.insertFront(a); 
    p2 = mNodeList.insertFront(a = 3);
    p3 = mNodeList.insert(p1, a = 6);
    p4 = mNodeList.insert(p1, a = 10);
    cout << mNodeList.isEmpty() << endl;
    cout << mNodeList.size() << endl;

    mNodeList.printAll();

     }
     catch (RuntimeException &e) {
          cout << e.getMessage() << endl;
     }
     
    return 0;
}