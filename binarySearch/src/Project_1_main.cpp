#include "Project_1_Tree.h"
#include "Project_1_BinaryTree.h"


int main(){
     Tree mTree;                     // 삽입, 전위순회, 후위순회 기능이 있는 트리(1)
     Position* mPosition[10000];     // 트리(1)의 노드를 가리키는 포지션 포인터 배열

     int mPositionIndex = 0;
     char operation = ' ';
     int nodeNum = 0;
     int nodeNumParent = 0;
     int siblingOrder = 0;
     bool stop = false;
     bool findPosition = false;

     BinaryTree mBinaryTree;         // 좌표출력 기능이 있는 이진트리
     Position_B* mPosition_B[10000]; // 이진트리의 노드를 가리키는 포지션 포인터 배열

     while (!stop){
          Position* tempPosition = NULL;
          Position_B* tempPosition_B = NULL;
          cin >> operation;        // 삽입 질의를 나타내는 기호
          switch (operation){
          case 'I':
          case 'i':  // insert 연산
               cin >> nodeNum;          // 삽입될 노드의 번호
               cin >> nodeNumParent;    // 삽입될 노드의 부모노드 번호
               cin >> siblingOrder; // 삽입될 노드의 형제노드들 사이에서의 순서

               // 최초 노드인 루트 노드를 삽입할 경우
               if (nodeNumParent == -1 && siblingOrder == -1){
                    Position* p = NULL;
                    Position_B* p_B = NULL;
                    mPosition[mPositionIndex] = mTree.insert(p, nodeNum, siblingOrder);              // 기본 트리 삽입
                    mPosition_B[mPositionIndex] = mBinaryTree.insert(p_B, nodeNum, siblingOrder);    // 이진 트리 삽입
                    mPositionIndex++;    
               }
               // 트리(1) ==== 루트 노드가 아닌 노드를 삽입할 경우
               else{
                    
                    int index = 0;
                    findPosition = false;

                    // Position 객체 포인터 배열에서 삽입될 노드의 부모노드 번호와 일치하는 노드를 찾을 때 까지
                    while (!findPosition){
                         if (mPosition[index]->nodeNum != nodeNumParent){
                              index++;    
                         } else{
                              // 삽입될 노드의 부모노드를 찾으면 해당 인덱스에 있는 포지션객체로 설정
                              tempPosition = mPosition[index];
                              tempPosition_B = mPosition_B[index];
                              findPosition = true;
                         }
                    }
                    // insert함수의 결과로 포지션이 반환되고 그 포지션은 배열의 해당 인덱스에 저장
                    mPosition[mPositionIndex] = mTree.insert(tempPosition, nodeNum, siblingOrder);                // 트리 삽입함수
                    mPosition_B[mPositionIndex] = mBinaryTree.insert(tempPosition_B, nodeNum, siblingOrder);      // 이진트리 삽입함수
                    mPositionIndex++;
               }
  
               break;
          case 'P':  // 전위 순회(Preorder Traversal)
          case 'p': 
               tempPosition = mPosition[0]; // 루트 노드의 포지션 받기
               mTree.preorder(tempPosition->nodePtr);
               cout << endl;
               break;
               
          case 'T':  // 후위 순회(Postorder Traversal)
          case 't':
               tempPosition = mPosition[0]; // 루트 노드의 포지션 받기
               mTree.postorder(tempPosition->nodePtr);
               cout << endl;
               break;

          case 'C': // 좌표 출력
          case 'c':
               cin >> nodeNum;     // 좌표를 출력할 노드의 번호 입력
               mBinaryTree.printPositionXY(nodeNum);
               cout << endl;
               break;

          case 'q': // 종료
          case 'Q':
               stop = true;
               cout << endl;
               break;
          }
     }



     

     return 0;
}