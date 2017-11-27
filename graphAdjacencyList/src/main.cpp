
#include "Graph_AdjacencyList.h"

int main(){
     ifstream input;    // ������ ������ ��Ʈ��
     ifstream database; // �����ͺ��̽��� �߰��� ��Ʈ��
     bool stop = false;       // �ݺ��� �÷���
     char operation = ' ';    // ���Ǿ�
     string fileName = "";

     int numOfVertex = 0; // �߰��� �л� ��
     int numOfEdge = 0;   // �߰��� ���� ��
     int stuId = 0;       // �й�
     string eMail = "";   // �̸���
     int roadId = 0;      // ���� ��ȣ
     int startStuId = 0;     // ������ ���������ִ� �л��� �й�
     int destStuId = 0;      // ������ ���������ִ� �л��� �й�

     G G;                     // ���� ����Ʈ ��� �׷��� ����

     cin >> fileName;
     database.open(fileName);

     database >> numOfVertex; // database�κ��� �л� �� �Է¹���
     database >> numOfEdge;   // database�κ��� ���� �� �Է¹���

     // database�� �ִ� �л� ������ ��� �Է¹���
     for (int i = 0; i < numOfVertex; i++){
          database >> stuId;
          database >> eMail;
          G.insertVertex_db(stuId, eMail);   // �׷��� G�� �л� vertex ����, �߰�
     }

     // database�� �ִ� ���� ������ ��� �Է¹���
     for (int j = 0; j < numOfEdge; j++){
          database >> roadId;
          database >> startStuId;
          database >> destStuId;
          G.insertEdge_db(roadId, startStuId, destStuId);
     }

     while (!stop){
          cin >> operation; // ���Ǿ� �Է�

          switch (operation){

          case 'A': // 1. �л� �߰�
               cin >> stuId;
               cin >> eMail;
               G.insertVertex(stuId, eMail);
               break;
               
          case 'P': // 2. �л����� ���
               cin >> stuId;
               G.printStuInfo(stuId);
               break;

          case 'I': // 3. ���� �߰�
               cin >> roadId;
               cin >> startStuId;
               cin >> destStuId;
               G.insertEdge(roadId, startStuId, destStuId);
               break;

          case 'X': // 4. �л� ����
               cin >> stuId;
               G.deleteVertex(stuId);
               break;

          case 'Z': // 5. ���� ����
               cin >> roadId;
               G.deleteEdge(roadId);
               break;

          case 'L': // 6. ����� ���� ���
               cin >> stuId;
               G.incidentEdges(stuId);
               break;

          case 'F': // 7. �������� ���1
               cin >> roadId;
               G.endVertices(roadId);
               break;

          case 'O': // 8. �������� ���2
               cin >> stuId;
               cin >> roadId;
               G.opposite(stuId, roadId);
               break;

          case 'K': // 9. �������� ���� Ȯ��
               cin >> startStuId;
               cin >> destStuId;
               G.isAdjacentTo(startStuId, destStuId);
               break;

          case 'Q': // 10. ���α׷� ����
               stop = true;
               break;



          }
     }



     return 0;
}