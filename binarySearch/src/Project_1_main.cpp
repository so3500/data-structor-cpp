#include "Project_1_Tree.h"
#include "Project_1_BinaryTree.h"


int main(){
     Tree mTree;                     // ����, ������ȸ, ������ȸ ����� �ִ� Ʈ��(1)
     Position* mPosition[10000];     // Ʈ��(1)�� ��带 ����Ű�� ������ ������ �迭

     int mPositionIndex = 0;
     char operation = ' ';
     int nodeNum = 0;
     int nodeNumParent = 0;
     int siblingOrder = 0;
     bool stop = false;
     bool findPosition = false;

     BinaryTree mBinaryTree;         // ��ǥ��� ����� �ִ� ����Ʈ��
     Position_B* mPosition_B[10000]; // ����Ʈ���� ��带 ����Ű�� ������ ������ �迭

     while (!stop){
          Position* tempPosition = NULL;
          Position_B* tempPosition_B = NULL;
          cin >> operation;        // ���� ���Ǹ� ��Ÿ���� ��ȣ
          switch (operation){
          case 'I':
          case 'i':  // insert ����
               cin >> nodeNum;          // ���Ե� ����� ��ȣ
               cin >> nodeNumParent;    // ���Ե� ����� �θ��� ��ȣ
               cin >> siblingOrder; // ���Ե� ����� �������� ���̿����� ����

               // ���� ����� ��Ʈ ��带 ������ ���
               if (nodeNumParent == -1 && siblingOrder == -1){
                    Position* p = NULL;
                    Position_B* p_B = NULL;
                    mPosition[mPositionIndex] = mTree.insert(p, nodeNum, siblingOrder);              // �⺻ Ʈ�� ����
                    mPosition_B[mPositionIndex] = mBinaryTree.insert(p_B, nodeNum, siblingOrder);    // ���� Ʈ�� ����
                    mPositionIndex++;    
               }
               // Ʈ��(1) ==== ��Ʈ ��尡 �ƴ� ��带 ������ ���
               else{
                    
                    int index = 0;
                    findPosition = false;

                    // Position ��ü ������ �迭���� ���Ե� ����� �θ��� ��ȣ�� ��ġ�ϴ� ��带 ã�� �� ����
                    while (!findPosition){
                         if (mPosition[index]->nodeNum != nodeNumParent){
                              index++;    
                         } else{
                              // ���Ե� ����� �θ��带 ã���� �ش� �ε����� �ִ� �����ǰ�ü�� ����
                              tempPosition = mPosition[index];
                              tempPosition_B = mPosition_B[index];
                              findPosition = true;
                         }
                    }
                    // insert�Լ��� ����� �������� ��ȯ�ǰ� �� �������� �迭�� �ش� �ε����� ����
                    mPosition[mPositionIndex] = mTree.insert(tempPosition, nodeNum, siblingOrder);                // Ʈ�� �����Լ�
                    mPosition_B[mPositionIndex] = mBinaryTree.insert(tempPosition_B, nodeNum, siblingOrder);      // ����Ʈ�� �����Լ�
                    mPositionIndex++;
               }
  
               break;
          case 'P':  // ���� ��ȸ(Preorder Traversal)
          case 'p': 
               tempPosition = mPosition[0]; // ��Ʈ ����� ������ �ޱ�
               mTree.preorder(tempPosition->nodePtr);
               cout << endl;
               break;
               
          case 'T':  // ���� ��ȸ(Postorder Traversal)
          case 't':
               tempPosition = mPosition[0]; // ��Ʈ ����� ������ �ޱ�
               mTree.postorder(tempPosition->nodePtr);
               cout << endl;
               break;

          case 'C': // ��ǥ ���
          case 'c':
               cin >> nodeNum;     // ��ǥ�� ����� ����� ��ȣ �Է�
               mBinaryTree.printPositionXY(nodeNum);
               cout << endl;
               break;

          case 'q': // ����
          case 'Q':
               stop = true;
               cout << endl;
               break;
          }
     }



     

     return 0;
}