#include "pch.h"
#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;

const int LOTTO_MAX = 45;
const int SHUFFLE_CNT = 1000;

int main() {
	srand((unsigned int)time(0));

	int lotto[LOTTO_MAX];

	// initiate
	for (int i = 0; i < LOTTO_MAX; ++i) {
		lotto[i] = i + 1;
	}

	// shuffle
	int idx1, idx2;
	for (int i = 0; i < SHUFFLE_CNT; ++i) {
		idx1 = rand() % LOTTO_MAX;
		idx2 = rand() % LOTTO_MAX;

		swap(lotto[idx1], lotto[idx2]);
	}

	for (int i = 0; i < 5; ++i) {
		cout << lotto[i] << " ";
	}
	cout << "보너스 " << lotto[6] << '\n';

	return 0;
}
