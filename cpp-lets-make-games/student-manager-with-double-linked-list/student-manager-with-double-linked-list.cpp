#include "pch.h"
#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

const int NAME_SIZE = 32;

enum MENU { NONE, INSERT, DELETE, SEARCH, PRINT, SORT, EXIT };

struct Student {
	int id;
	char name[NAME_SIZE];
	int kor, eng, math;
	int sum;
	float avg;
};

struct Node {
	Student datum;
	Node* pPrev;
	Node* pNext;
};

struct List {
	// pHead, pTail은 명시적으로 처음과 끝을 의미하며 데이터는 갖지 않음
	Node* pHead;
	Node* pTail;
	int size;
};

void initList(List* pList) {
	pList->pHead = new Node;
	pList->pTail = new Node;
	pList->pHead->pPrev = NULL;
	pList->pHead->pNext = pList->pTail;
	pList->pTail->pPrev = pList->pHead;
	pList->pTail->pNext = NULL;
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
	// 새 노드는 pTail->pPrev와 pTail 사이에 추가
	Node* pPrev = pList->pTail->pPrev;
	pPrev->pNext = pNode;
	pNode->pPrev = pPrev;
	pNode->pNext = pList->pTail;
	pList->pTail->pPrev = pNode;
	++pList->size;
}

void deleteStudent(List* pList) {
	cout << "=====< 학생 삭제 >=====\n";
	cout << "삭제할 이름을 입력하세요: ";
	char searchName[NAME_SIZE];
	cin.ignore(1024, '\n');
	cin.getline(searchName, NAME_SIZE - 1);

	Node* pNode = pList->pHead->pNext;
	while (pNode != pList->pTail) {
		if (strcmp(pNode->datum.name, searchName) == 0) {
			Node* pPrev = pNode->pPrev;
			Node* pNext = pNode->pNext;
			delete pNode;
			pPrev->pNext = pNext;
			pNext->pPrev = pPrev;
			--pList->size;

			cout << "학생을 삭제했습니다.\n";
			return;
		}
		pNode = pNode->pNext;
	}

	cout << "삭제할 학생을 찾을 수 없습니다.\n";
}

void printStudent(const Student* pStudent) {
	cout << "학번: " << pStudent->id << '\t';
	cout << "이름: " << pStudent->name << '\n';
	cout << "국어: " << pStudent->kor << '\t';
	cout << "영어: " << pStudent->eng << '\t';
	cout << "수학: " << pStudent->math << '\n';
	cout << "총점: " << pStudent->sum << '\t';
	cout << "평균: " << pStudent->avg << '\n';
	cout << '\n';
}

void search(List* pList) {
	cout << "=====< 학생 검색 >=====\n";
	cout << "검색할 이름을 입력하세요: ";
	char searchName[NAME_SIZE];
	cin.ignore(1024, '\n');
	cin.getline(searchName, NAME_SIZE - 1);

	Node* pNode = pList->pHead->pNext;
	while (pNode != pList->pTail) {
		if (strcmp(pNode->datum.name, searchName) == 0) {
			printStudent(&pNode->datum);
			return;
		}
		pNode = pNode->pNext;
	}

	cout << "검색 결과가 없습니다.\n";
}

void print(List* pList, bool reversed = false) {
	cout << "=====< 학생 목록 >=====\n";
	cout << "학생 수: " << pList->size << '\n';

	if (!reversed) {  // 정방향 출력
		Node* pNode = pList->pHead->pNext;
		while (pNode != pList->pTail) {
			printStudent(&pNode->datum);
			pNode = pNode->pNext;
		}
	}
	else {  // 역방향 출력
		Node* pNode = pList->pTail->pPrev;
		while (pNode != pList->pHead) {
			printStudent(&pNode->datum);
			pNode = pNode->pPrev;
		}
	}
}

void sort(List* pList, bool byID = true) {
	bool needSwap, isSorted = false;

	// 버블 정렬 (학번은 오름차순, 총점은 내림차순)
	while (!isSorted) {
		isSorted = true;
		Node* pFirst = pList->pHead->pNext;
		Node* pSecond = pFirst->pNext;
		while (pSecond != pList->pTail) {
			needSwap = (byID) ?
				(pFirst->datum.id > pSecond->datum.id) :
				(pFirst->datum.sum < pSecond->datum.sum);
			if (needSwap) {
				isSorted = false;
				// 이웃 노드 처리
				pFirst->pPrev->pNext = pSecond;
				pSecond->pNext->pPrev = pFirst;
				// pFirst, pSecond 교체
				pSecond->pPrev = pFirst->pPrev;
				pFirst->pNext = pSecond->pNext;
				pSecond->pNext = pFirst;
				pFirst->pPrev = pSecond;
			}

			pFirst = pSecond;
			pSecond = pSecond->pNext;
		}
	}

	cout << "정렬이 완료되었습니다.\n";
}

int main() {
	List list;
	int cntStudentID = 1;
	int ipt;

	initList(&list);

	while (true) {
		cout << "1. 등록 / 2. 삭제 / 3. 검색 / 4. 출력 / 5. 정렬 / 6. 종료\n";
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
			while (true) {
				cout << "1. 정방향 / 2. 역방향\n";
				cout << "출력 방향을 선택하세요: ";
				ipt = inputInt();
				if (ipt == 1 || ipt == 2) break;
			}
			print(&list, ipt - 1);
			break;

		case SORT:
			while (true) {
				cout << "1. 총점 내림차순 / 2. 학번 오름차순\n";
				cout << "정렬 기준을 선택하세요: ";
				ipt = inputInt();
				if (ipt == 1 || ipt == 2) break;
			}
			sort(&list, ipt - 1);
			break;

		default:
			cout << "잘못 입력했습니다.\n";
			break;
		}  // end of switch (ipt)
	}  // end of while (true)

	clearList(&list);
	return 0;
}  // end of main()
