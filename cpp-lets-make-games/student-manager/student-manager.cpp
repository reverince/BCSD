#include "pch.h"
#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

const int NAME_SIZE = 32;
const int STUDENT_MAX = 10;

enum MENU { NONE, INSERT, DELETE, SEARCH, PRINT, EXIT };

struct Student {
	int id;
	char name[NAME_SIZE];
	int kor, eng, math;
	int sum;
	float avg;
};

Student students[STUDENT_MAX] = { };

void printStudent(int idx) {
	cout << "학번: " << students[idx].id << '\n';
	cout << "이름: " << students[idx].name << '\n';
	cout << "국어: " << students[idx].kor << '\n';
	cout << "영어: " << students[idx].eng << '\n';
	cout << "수학: " << students[idx].math << '\n';
	cout << "총점: " << students[idx].sum << '\n';
	cout << "평균: " << students[idx].avg << '\n';
	cout << '\n';
}

int main() {
	int cntStudent = 0, cntStudentID = 1;
	int ipt;
	char searchName[NAME_SIZE];

	while (true) {
		cout << "1. 등록 / 2. 삭제 / 3. 검색 / 4. 출력 / 5. 종료\n";
		cout << "메뉴를 선택하세요: ";
		cin >> ipt;
		if (cin.fail()) {  // 입력 오류 발생 시
			cin.clear();  // 버퍼 클리어
			cin.ignore(1024, '\n');  // 버퍼에 남은 \n 제거 (1024 바이트 탐색)
			continue;
		}

		if (ipt == EXIT) exit(0);
		switch (ipt) {
		case INSERT:
			if (cntStudent == STUDENT_MAX) {
				cout << "학생 수가 가득 찼습니다.\n";
				break;
			}
			// 이름, 점수는 입력 받고 학번, 총점, 평균은 계산
			cout << "이름: ";
			cin.ignore(1024, '\n');
			cin.getline(students[cntStudent].name, NAME_SIZE - 1);
			cout << "국어: ";
			cin >> students[cntStudent].kor;
			cout << "영어: ";
			cin >> students[cntStudent].eng;
			cout << "수학: ";
			cin >> students[cntStudent].math;
			students[cntStudent].id = cntStudentID;
			students[cntStudent].sum = students[cntStudent].kor + students[cntStudent].eng + students[cntStudent].math;
			students[cntStudent].avg = students[cntStudent].sum / 3.f;
			++cntStudent;
			++cntStudentID;
			break;

		case DELETE:
			cout << "=====< 학생 삭제 >=====\n";
			cout << "삭제할 이름을 입력하세요: ";
			cin.ignore(1024, '\n');
			cin.getline(searchName, NAME_SIZE - 1);
			for (int i = 0; i < cntStudent; ++i) {
				if (strcmp(students[i].name, searchName) == 0) {
					for (int j = i; j < cntStudent - 1; ++j) {
						students[j] = students[j + 1];
					}
					--cntStudent;
					cout << "학생을 삭제했습니다.\n";
					break;
				}
			}
			break;

		case SEARCH:
			cout << "=====< 학생 검색 >=====\n";
			cout << "검색할 이름을 입력하세요: ";
			cin.ignore(1024, '\n');
			cin.getline(searchName, NAME_SIZE - 1);
			for (int i = 0; i < cntStudent; ++i) {
				if (strcmp(students[i].name, searchName) == 0) {
					printStudent(i);
				}
			}
			break;

		case PRINT:
			cout << "=====< 학생 목록 >=====\n";
			for (int i = 0; i < cntStudent; ++i) {
				printStudent(i);
			}
			break;

		default:
			cout << "잘못 입력했습니다.\n";
			break;
		}  // end of switch (ipt)
	}  // end of while (true)

	return 0;
}  // end of main()
