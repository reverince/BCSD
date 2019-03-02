#include "pch.h"
#include <iostream>
using namespace std;

/*
함수 포인터
함수의 메모리 주소를 저장하기 위한 포인터
전역함수는 함수명이 메모리 주소
*/

int add(int a, int b) {
	return a + b;
}

int subtract(int a, int b) {
	return a - b;
}

int main()
{
	int(*pFunc)(int, int) = add;

	cout << pFunc(10, 20) << '\n';

	pFunc = subtract;
	cout << pFunc(10, 20) << '\n';

	return 0;
}
