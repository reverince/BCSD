#include "pch.h"
#include <iostream>
using namespace std;

void stargaze(int type) {
	if (type <= 0 || type > 4) return;
	int n;
	cout << "n을 입력하세요: ";
	while (true) {
		if (cin.fail()) {
			cin.clear();
			cin.ignore(1024, '\n');
			continue;
		}
	}
	cin >> n;

	switch (type) {
	case 1:
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n - i - 1; ++j)
				cout << ' ';
			for (int j = 0; j < i + 1; ++j)
				cout << '*';
			cout << '\n';
		}
		break;
	case 2:
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n - i - 1; ++j)
				cout << ' ';
			for (int j = 0; j < 2 * i + 1; ++j)
				cout << '*';
			cout << '\n';
		}
		for (int i = n - 2; i > -1; --i) {
			for (int j = 0; j < n - i - 1; ++j)
				cout << ' ';
			for (int j = 0; j < 2 * i + 1; ++j)
				cout << '*';
			cout << '\n';
		}
		break;
	case 3:
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < i + 1; ++j)
				cout << '*';
			for (int j = 0; j < n - i - 1; ++j)
				cout << "  ";
			for (int j = 0; j < i + 1; ++j)
				cout << '*';
			cout << '\n';
		}
		for (int i = n - 2; i > -1; --i) {
			for (int j = 0; j < i + 1; ++j)
				cout << '*';
			for (int j = 0; j < n - i - 1; ++j)
				cout << "  ";
			for (int j = 0; j < i + 1; ++j)
				cout << '*';
			cout << '\n';
		}
		break;
	case 4:
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n - i - 1; ++j)
				cout << ' ';
			for (int j = 0; j < i + 1; ++j)
				cout << "* ";
			cout << "\n";
		}
		break;
	}
}

int main() {
	int ipt;
	while (true) {
		cout << "타입을 선택하세요(1~4): ";
		cin >> ipt;

		stargaze(ipt);
	}

	return 0;
}
