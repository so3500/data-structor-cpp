#ifndef _PROJECT_2_HASHTABLE_H_
#define _PROJECT_2_HASHTABLE_H_

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// �� ����, ��� ��, ����߾����� ������ ������� �� ��Ÿ��
enum Status{ EMPTY, USED, AVAILABLE };
// �л� ������ ������ �ִ� ���
class Node{
public:
     Node(int stuId = 0, int sco = 0, string mail = ""){
          studentId = stuId;
          score = sco;
          eMail = mail;
          //strcpy(eMail, mail);
     }
     friend class HashTable;
private:

     int studentId;    // �й�
     int score;        // ����
     string eMail;      // �̸���

};
// �л� ������ ������ �ִ� ��带 ����Ű�� ���������
class NodePointer{
public:
     NodePointer(Node* NPtr = NULL, Status st = EMPTY){
          NodePtr = NPtr;
          status = st;
     }
     friend class HashTable;
private:
     Node* NodePtr;           // ��带 ����Ű�� ���������
     Status status;           // ���¸� ��Ÿ���� ������ ����, EMPTY, USED, AVAILABLE �������� �ִ�.
};

class HashTable{
public:
     HashTable(int N, int q){
          hashTableArray = new NodePointer*[N]();
          memset(hashTableArray, NULL, sizeof(hashTableArray)); // �迭�� ��� �׸��� NULL�� �ʱ�ȭ
          numOfStudent = 0;
          sizeOfTable = N;
          primeQ = q;
     }
     void put(int key, Node* o);                  // (1) �л� �߰�
     void put_db(int key, Node* o);               // database �Է¿� 
     void addScore(int key, int score);           // (2) �������� �߰�
     void modifyEmail(int key, string eMail);      // (3) �̸��� �ּ� ����
     void printStuInfo(int key);                  // (4) �л����� ���

private:
     NodePointer** hashTableArray;  // ����� �����͹迭�� ù��°�ּҸ� ���� ������     
     int sizeOfTable;               // ���̺��� ũ��                
     int numOfStudent;              // �л� ��, �л������� �߰��ϰų� ���� �� �ֽ�ȭ     
     int primeQ;                    // ���̺��� ũ�� ���� ���� �Ҽ�, 2�� �ؽ� �Լ��� ���
};



// ================== (1) �л��߰�_fromDB ==================
void HashTable::put_db(int key, Node* o){
     int index = 0;
     int probNum = 1;
     int stop = false;

     index = key % sizeOfTable;    // 1�� �ؽ� �Լ�

     while (!stop){
          // �迭�� index�� �ش��ϴ� ������ ��������� �߰�
          if (hashTableArray[index] == NULL){
               o->studentId = key;                                    // �л� ���� ��忡 key�� �Է�
               NodePointer* tempNodePtr = new NodePointer(o, USED);   // �л� ���� ��� ������ ��ü ����
               hashTableArray[index] = tempNodePtr;                   // �ؽ� ���̺� �ش� �л� ���� ��� ������ �߰�
               numOfStudent++;                                        // ���̺��� �л� �� �ֽ�ȭ, �л� �߰��̹Ƿ� 1 ����
               stop = true;                                           // �ݺ����� stop�÷���
          }
          // �迭�� index�� �ش��ϴ� ������ ������� ���
          else {
               index = (index + (primeQ - (key%primeQ))) % sizeOfTable; // 2�� �ؽ� �Լ�
               probNum++;                                               // ���κ� Ƚ�� ����
          }
     }
}

// ================== (2) �л��߰�_fromQuery ==================
void HashTable::put(int key, Node* o){
     int index = 0;
     int probNum = 1;
     int stop = false;

     index = key % sizeOfTable;    // 1�� �ؽ� �Լ�

     while (!stop){
          // �迭�� index�� �ش��ϴ� ������ ��������� �߰�
          if (hashTableArray[index] == NULL){
               NodePointer* tempNodePtr = new NodePointer(o, USED);
               hashTableArray[index] = tempNodePtr;
               numOfStudent++;
               stop = true;
          }
          // �迭�� index�� �ش��ϴ� ������ ������� ���
          else {

               index = (index + (primeQ - (key%primeQ))) % sizeOfTable; // 2�� �ؽ� �Լ�
               probNum++;                                               // probe �� ����
          }
     }

     cout << probNum << " ";  // ���κ� Ƚ�� ���

     double tempD = (double)numOfStudent / sizeOfTable;
     tempD = tempD * 1000;
     tempD = (((int)tempD + 5) / 10);
     tempD = tempD / 100;
     
     // load factor ���
     printf("%2.2f", tempD); // %�ڸ���1.�ڸ���2f �� �ڸ���1��ŭ ��µǳ� �Ҽ��� ������ �ڸ����� �ڸ���2��ŭ ��� 
     cout << endl;

     

}

// ================== (3) �������� �߰� ==================
void HashTable::addScore(int key, int score){
     int index = 0;
     int probNum = 1;
     int stop = false;

     index = key % sizeOfTable;    // 1�� �ؽ� �Լ�

     while (!stop){
          // �ش� index������ ������� ���� ���
          if (hashTableArray[index] != NULL) {
               // �迭�� index�� �ش��ϴ� ���(�л�)�� key���� ã�� key���� ��ġ�ϴ� ���
               if (hashTableArray[index]->NodePtr->studentId == key){
                    Node* tempNode = hashTableArray[index]->NodePtr; // �ش� index�� �ִ� ����������� �ּ� ����

                    // ���� �߰��Ͽ� �ջ��� ������ 24���� �Ѵ°��, �������� �߰� ����
                    if (tempNode->score + score > 24){
                         cout << probNum << " Exceeded" << endl;
                    }
                    // 24������ ���� �ʴ� ���, �������� �߰� ����
                    else{
                         tempNode->score += score;                            // ���� �߰�
                         cout << probNum << " " << tempNode->score << endl;   // ���κ� Ƚ���� �ջ��� ���� ���
                    }
                    stop = true;
               }
               // key���� ��ġ���� �ʴ� ���
               else{
                    index = (index + (primeQ - (key%primeQ))) % sizeOfTable; // 2�� �ؽ� �Լ�
                    probNum++;                                               // probe �� ����

               }
          }
          // �ش� �ε��� ������ ����ִ� ���(NULL) ���κ� ����, �Ű������� �־��� key���� ��ġ�ϴ� ��� ã�� ����
          else{
               cout << probNum << " Not found" << endl;
               stop = true;
          }
     }
}

// ================== (4) �̸����ּ� ���� ==================
void HashTable::modifyEmail(int key, string eMail){
     int index = 0;
     int probNum = 1;
     int stop = false;

     index = key % sizeOfTable;    // 1�� �ؽ� �Լ�

     while (!stop){
          // �ش� index������ ������� ���� ���
          if (hashTableArray[index] != NULL) {
               // �迭�� index�� �ش��ϴ� ���(�л�)�� key���� ã�� key���� ��ġ�ϴ� ���
               if (hashTableArray[index]->NodePtr->studentId == key){
                    Node* tempNode = hashTableArray[index]->NodePtr;
                    tempNode->eMail = eMail;
                    //strcpy(tempNode->eMail, eMail); // �̸��� ����
                    stop = true;
                    cout << probNum << endl;
               }
               // �迭�� index�� �ش��ϴ� ���(�л�)�� �ְ�, key���� ��ġ���� �ʴ� ���
               else{
                    index = (index + (primeQ - (key%primeQ))) % sizeOfTable; // 2�� �ؽ� �Լ�
                    probNum++;                                               // probe �� ����
               }
          }
          // �ش� �ε��� ������ ����ִ� ���(NULL) ���κ� ����, �Ű������� �־��� key���� ��ġ�ϴ� ��� ã�� ����
          else{
               cout << probNum << " Not found" << endl;
               stop = true;
          }
     }
}

// ================== (5) �л����� ��� ==================
void HashTable::printStuInfo(int key){
     int index = 0;
     int probNum = 1;
     int stop = false;

     index = key % sizeOfTable;    // 1�� �ؽ� �Լ�

     while (!stop){
          // �ش� index������ ������� ���� ���
          if (hashTableArray[index] != NULL) {
               // �迭�� index�� �ش��ϴ� ���(�л�)�� key���� ã�� key���� ��ġ�ϴ� ���
               if (hashTableArray[index]->NodePtr->studentId == key){
                    Node* tempNode = hashTableArray[index]->NodePtr;

                    // �л����� ���
                    cout << probNum << " "
                         << tempNode->studentId << " "
                         << tempNode->score << " "
                         << tempNode->eMail << endl;
                    stop = true;
               }
               // �迭�� index�� �ش��ϴ� ���(�л�)�� �ְ�, key���� ��ġ���� �ʴ� ���
               else{
                    index = (index + (primeQ - (key%primeQ))) % sizeOfTable; // 2�� �ؽ� �Լ�
                    probNum++;                                               // probe Ƚ�� ����
               }
          }
          // �ش� �ε��� ������ ����ִ� ���(NULL) ���κ� ����, �Ű������� �־��� key���� ��ġ�ϴ� ��� ã�� ����
          else{
               cout << probNum << " Not found" << endl;
               stop = true;
          }
     }
}
#else
#endif
