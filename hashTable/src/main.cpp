
#include "HashTable.h"

int main(){
     ifstream input;         // ������ ������ ��Ʈ��
     ifstream database;      // �����ͺ��̽��� �߰��� ��Ʈ��
     bool stop = false;      // �ݺ��� �÷���
     char operation = ' ';   // ���Ǿ�
     string fileName = "";
     int N = 0;              // �迭�� ũ��
     int M = 0;              // ����� ��
     int q = 0;              // N���� ���� �Ҽ�
     int key = 0;            // key��(=studentId)
     int score = 0;          // ����
     string eMail = "";       // �̸���
      

     cin >> fileName;
     database.open(fileName);

     database >> N;           // �迭�� ũ��
     database >> M;           // �л� ��
     database >> q;           // �迭�� ũ�⺸�� ���� �Ҽ�
     HashTable mHashTable(N, q); // �ؽ� ���̺� ����

     // database�� �ִ� ��� ������ �ؽ� ���̺� �߰��Ҷ� ���� �ݸ� ����
     while (M != 0) {
          database >> key;    // = studentId
          database >> score;
          database >> eMail;
          Node* tempNode = new Node(key, score, eMail); // �л� ������ ���� ��� ����
          mHashTable.put_db(key, tempNode);             // ��带 �ؽ� ���̺� �߰�
          M--;
     }

     database.close();

     while (!stop){

          cin >> operation;
          switch (operation){

          case 'A': // �л� �߰�
          {
               key = 0;
               eMail = "";
               cin >> key;
               cin >> eMail;
               Node* tempNode = new Node(key, 0, eMail);

               mHashTable.put(key, tempNode);
          }
          break;

          case 'U': // �������� �߰�
               key = 0;
               score = 0;
               cin >> key;
               cin >> score;

               mHashTable.addScore(key, score);
               break;

          case 'M': // �̸��� �ּ� ����
               key = 0;
               eMail = "";
               cin >> key;
               cin >> eMail;

               mHashTable.modifyEmail(key, eMail);
               break;

          case 'P': // �л����� ���
               key = 0;
               cin >> key;

               mHashTable.printStuInfo(key);
               break;

          case 'Q': // ����
               stop = true;
               break;
          }
     }


     input.close();
     return 0;
}