#include "pch.h"
#include <iostream>
using namespace std;

const char *FILE_NAME = "file.txt";

int main()
{
	FILE* pFile = nullptr;

	// r: 읽기 / w: 쓰기 / a: 접근 // t: 텍스트 / b: 바이너리
	fopen_s(&pFile, FILE_NAME, "wt");
	if (pFile) {
		const char *pText = "test";

		// fwrite(메모리 주소, 메모리 크기, 개수,  스트림)
		fwrite(pText, 1, 4, pFile);

		fclose(pFile);

		cout << "성공\n";
	}

	fopen_s(&pFile, FILE_NAME, "rt");
	if (pFile) {
		char str[5] = { };

		fread(str, 1, 4, pFile);
		cout << str << '\n';

		fclose(pFile);
	}

	return 0;
}
