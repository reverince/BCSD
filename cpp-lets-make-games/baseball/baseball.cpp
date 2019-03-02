#include "pch.h"
#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;

const int NUM_MAX = 9;
const int NUM_CNT = 3;
const int SHUFFLE_CNT = 1000;

int main() {
	srand((unsigned int)time(0));

	int nums[NUM_MAX], balls[NUM_CNT];

	// initiate
	for (int i = 0; i < NUM_MAX; ++i) {
		nums[i] = i + 1;
	}

	// shuffle
	int idx1, idx2;
	for (int i = 0; i < SHUFFLE_CNT; ++i) {
		idx1 = rand() % NUM_MAX;
		idx2 = rand() % NUM_MAX;

		swap(nums[idx1], nums[idx2]);
	}

	for (int i = 0; i < NUM_CNT; ++i) {
		balls[i] = nums[i];
	}

	int ipts[3], strike, ball;

	while (true) {
		strike = ball = 0;
		cout << "예상 숫자 세 개를 입력하세요(0은 종료): ";
		cin >> ipts[0] >> ipts[1] >> ipts[2];

		if (ipts[0] == 0 || ipts[1] == 0 || ipts[2] == 0) break;
		if (ipts[0] < 0 || ipts[0] > NUM_MAX ||
			ipts[1] < 0 || ipts[1] > NUM_MAX ||
			ipts[2] < 0 || ipts[2] > NUM_MAX) {
			cout << "잘못된 값을 입력했습니다.\n";
			continue;
		}
		if (ipts[0] == ipts[1] || ipts[0] == ipts[2] || ipts[1] == ipts[2]) {
			cout << "중복된 값을 입력했습니다.\n";
			continue;
		}

		for (int i = 0; i < NUM_CNT; ++i) {
			for (int b = 0; b < NUM_CNT; ++b) {
				if (balls[b] == ipts[i]) {
					if (b == i) ++strike;
					else ++ball;
					break;
				}
			}
		}

		if (strike == 3) {
			cout << "3 스트라이크!\n";
			break;
		}
		else if (strike == 0 && ball == 0)
			cout << "아웃!\n";
		else
			cout << strike << "스트라이크 " << ball << "볼\n";
	}

	return 0;
}
