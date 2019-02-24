#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

const int NAME_SIZE = 32;

enum MENU { NONE, INSERT, DELETE, SEARCH, PRINT, EXIT };

struct Student {
  int id;
  char name[NAME_SIZE];
  int kor, eng, math;
  int sum;
  float avg;
};

struct Node {
  Student datum;
  Node* pNext;
};

struct List {
  Node* pHead;
  Node* pTail;
  int size;
};

void initList(List* pList) {
  pList->pHead = NULL;
  pList->pTail = NULL;
  pList->size = 0;
}

void clearList(List* pList) {
  Node* pNode = pList->pHead;
  
  while (pNode != NULL) {
    Node* pNext = pNode->pNext;
    delete pNode;
    pNode = pNext;
  }
  pList->pHead = NULL;
  pList->pTail = NULL;
  pList->size = 0;
}

int inputInt() {
  int ipt;
  while (true) {
    cin >> ipt;
    if (cin.fail()) {
      cin.clear();
      cin.ignore(1024, '\n');
      continue;
    }
    break;
  }
  
  return ipt;
}

void insertStudent(List* pList, int& cntStudentID) {
  // 이름, 점수는 입력 받고 학번, 총점, 평균은 계산
  Student student = { };
  cout << "이름: ";
  cin.ignore(1024, '\n');
  cin.getline(student.name, NAME_SIZE - 1);
  cout << "국어: ";
  student.kor = inputInt();
  cout << "영어: ";
  student.eng = inputInt();
  cout << "수학: ";
  student.math = inputInt();
  student.id = cntStudentID;
  student.sum = student.kor + student.eng + student.math;
  student.avg = student.sum / 3.f;
  ++cntStudentID;
  
  Node* pNode = new Node;
  pNode->datum = student;
  pNode->pNext = NULL;
  if (pList->pHead == NULL)
    pList->pHead = pNode;
  else pList->pTail->pNext = pNode;
  pList->pTail = pNode;
  ++pList->size;
}

void deleteStudent(List* pList) {
  cout << "=====< 학생 삭제 >=====\n";
  cout << "삭제할 이름을 입력하세요: ";
  char searchName[NAME_SIZE];
  cin.ignore(1024, '\n');
  cin.getline(searchName, NAME_SIZE - 1);
  
  Node* pNode = pList->pHead;
  Node* pPrev = NULL;
  while (pNode != NULL) {
    if (strcmp(pNode->datum.name, searchName) == 0) {
      Node* pNext = pNode->pNext;
      delete pNode;
      
      if (pPrev == NULL) {  // 처음 노드 삭제 시
        pList->pHead = pNext;
        if (pNext == NULL)  // 유일한 노드 삭제 시
          pList->pTail = NULL;
      }
      else {
        pPrev->pNext = pNext;
        if (pNext == NULL)  // 마지막 노드 삭제 시
          pList->pTail = pPrev;
      }
      
      --pList->size;
      cout << "학생을 삭제했습니다.\n";
      return;
    }
    pPrev = pNode;
    pNode = pNode->pNext;
  }
  
  cout << "삭제할 학생을 찾을 수 없습니다.\n";
}

void printStudent(const Student* pStudent) {
  cout << "학번: " << pStudent->id << '\n';
  cout << "이름: " << pStudent->name << '\n';
  cout << "국어: " << pStudent->kor << '\n';
  cout << "영어: " << pStudent->eng << '\n';
  cout << "수학: " << pStudent->math << '\n';
  cout << "총점: " << pStudent->sum << '\n';
  cout << "평균: " << pStudent->avg << '\n';
  cout << '\n';
}

void search(List* pList) {
  cout << "=====< 학생 검색 >=====\n";
  cout << "검색할 이름을 입력하세요: ";
  char searchName[NAME_SIZE];
  cin.ignore(1024, '\n');
  cin.getline(searchName, NAME_SIZE - 1);
  
  Node* pNode = pList->pHead;
  while (pNode != NULL) {
    if (strcmp(pNode->datum.name, searchName) == 0) {
      printStudent(&pNode->datum);
      return;
    }
    pNode = pNode->pNext;
  }
  
  cout << "검색 결과가 없습니다.\n";
}

void print(List* pList) {
  cout << "=====< 학생 목록 >=====\n";
  cout << "학생 수: " << pList->size << '\n';
  
  Node* pNode = pList->pHead;
  while (pNode != NULL) {
    printStudent(&pNode->datum);
    pNode = pNode->pNext;
  }
}

int main() {
  List list;
  int cntStudentID = 1;
  int ipt;
  
  initList(&list);
  
  while (true) {
    cout << "1. 등록 / 2. 삭제 / 3. 검색 / 4. 출력 / 5. 종료\n";
    cout << "메뉴를 선택하세요: ";
    ipt = inputInt();
    
    if (ipt == EXIT) exit(0);
    switch (ipt) {
      case INSERT:
        insertStudent(&list, cntStudentID);
        break;  // break case INSERT
        
      case DELETE:
        deleteStudent(&list);
        break;
        
      case SEARCH:
        search(&list);
        break;
        
      case PRINT:
        print(&list);
        break;
        
      default:
        cout << "잘못 입력했습니다.\n";
        break;
    }  // end of switch (ipt)
  }  // end of while (true)
  
  clearList(&list);
  return 0;
}  // end of main()
