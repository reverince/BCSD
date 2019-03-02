#include "pch.h"
#include <iostream>
using namespace std;

const int NAME_SIZE = 32;
const int STUDENT_MAX = 3;
const char* FILE_NAME = "students.bin";

struct Student {
	int id;
	char name[NAME_SIZE];
	int kor, eng, math;
	int sum;
	float avg;
};

void writeFile() {
	Student students[STUDENT_MAX] = { };

	for (int i = 0; i < STUDENT_MAX; ++i) {
		// 이름, 점수는 입력 받고 학번, 총점, 평균은 계산
		cout << "이름: ";
		cin >> students[i].name;
		cout << "국어: ";
		cin >> students[i].kor;
		cout << "영어: ";
		cin >> students[i].eng;
		cout << "수학: ";
		cin >> students[i].math;
		students[i].id = i + 1;
		students[i].sum = students[i].kor + students[i].eng + students[i].math;
		students[i].avg = students[i].sum / 3.f;
	}

	FILE* pFile = nullptr;
	
	fopen_s(&pFile, FILE_NAME, "wb");
	if (pFile) {
		// 학생 수 쓰기
		int studentCount = STUDENT_MAX;
		fwrite(&studentCount, sizeof(studentCount), 1, pFile);

		for (int i = 0; i < studentCount; ++i) {
			fwrite(&students[i], sizeof(Student), 1, pFile);
		}

		fclose(pFile);
	}
}

void readFile() {
	Student students[STUDENT_MAX] = { };
	FILE *pFile = nullptr;
	int studentCount = 0;

	fopen_s(&pFile, FILE_NAME, "rb");
	if (pFile) {
		// 학생 수 읽기
		fread(&studentCount, sizeof(studentCount), 1, pFile);

		for (int i = 0; i < studentCount; ++i) {
			fread(&students[i], sizeof(Student), 1, pFile);
		}

		fclose(pFile);
	}

	// 읽어온 학생 목록 출력
	for (int i = 0; i < studentCount; ++i) {
		cout << "학번: " << students[i].id << '\n';
		cout << "이름: " << students[i].name << '\n';
		cout << "국어: " << students[i].kor << '\n';
		cout << "영어: " << students[i].eng << '\n';
		cout << "수학: " << students[i].math << '\n';
		cout << "총점: " << students[i].sum << '\n';
		cout << "평균: " << students[i].avg << '\n';
		cout << '\n';
	}
}

int main()
{
	int ipt;
	cout << "1. 쓰기 / 2. 읽기\n";
	cout << "동작을 선택하세요: ";
	cin >> ipt;

	if (ipt == 1) writeFile();
	else readFile();

	return 0;
}
