#include "pch.h"
#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <cstring>
using namespace std;

const int ROW = 6;
const int COLUMN = 11;
const int BOMB_MAX = 3;  // 동시에 설치할 수 있는 최대 폭탄 수

struct Point {
	int y, x;
};

void initMaze(char maze[ROW][COLUMN],
	Point* pPlayerPos, Point* pStartPos, Point* pEndPos) {
	pStartPos->y = 0;
	pStartPos->x = 0;
	pEndPos->y = ROW - 2;
	pEndPos->x = COLUMN - 2;
	*pPlayerPos = *pStartPos;
	// 0: 길 / 1: 벽 / 2: 입구 / 3: 출구
	strcpy_s(maze[0], "2100010000");
	strcpy_s(maze[1], "0101111110");
	strcpy_s(maze[2], "0000100000");
	strcpy_s(maze[3], "0110101011");
	strcpy_s(maze[4], "0010001003");
}

void printMaze(char maze[ROW][COLUMN], Point* pPlayerPos) {
	system("cls");
	for (int r = 0; r < ROW; ++r) {
		for (int c = 0; c < COLUMN; ++c) {
			if (pPlayerPos->y == r && pPlayerPos->x == c) {
				cout << "★";
				continue;
			}
			if (maze[r][c] == '0') cout << "　";
			if (maze[r][c] == '1') cout << "■";
			if (maze[r][c] == '2') cout << "○";
			if (maze[r][c] == '3') cout << "◎";
			if (maze[r][c] == '4') cout << "♨";
		}
		cout << '\n';
	}
}

void movePlayer(char maze[ROW][COLUMN], Point* pPlayerPos, char ipt) {
	Point targetPos = *pPlayerPos;
	ipt = tolower(ipt);
	switch (ipt) {
	case 'w':
		targetPos.y -= 1;
		break;
	case 's':
		targetPos.y += 1;
		break;
	case 'a':
		targetPos.x -= 1;
		break;
	case 'd':
		targetPos.x += 1;
		break;
	default:
		return;
	}
	// 유효성 검사
	if (targetPos.y < 0 || targetPos.y >= ROW-1 ||
		targetPos.x < 0 || targetPos.x >= COLUMN-1 ||
		maze[targetPos.y][targetPos.x] == '1' ||
		maze[targetPos.y][targetPos.x] == '4')
		return;
	*pPlayerPos = targetPos;
}

void placeBomb(char maze[ROW][COLUMN], const Point* pPlayerPos, int& cntBomb, Point* pBombs) {
	if (cntBomb >= BOMB_MAX) return;
	if (maze[pPlayerPos->y][pPlayerPos->x] == '4') return;
	pBombs[cntBomb] = *pPlayerPos;
	++cntBomb;
	maze[pPlayerPos->y][pPlayerPos->x] = '4';
}

void detonateBomb(char maze[ROW][COLUMN], Point* pPlayerPos, const Point* pStartPos, int& cntBomb, Point* pBombs) {
	for (int b = 0; b < cntBomb; ++b) {
		Point targets[5] = { };
		for (int t = 0; t < 5; ++t) {
			targets[t].y = pBombs[b].y;
			targets[t].x = pBombs[b].x;
		}
		int cntTarget = 1;

		// 상하좌우 타깃 추가
		if (pBombs[b].y > 0) {
			--targets[cntTarget].y;
			++cntTarget;
		}
		if (pBombs[b].y < ROW - 1) {
			++targets[cntTarget].y;
			++cntTarget;
		}
		if (pBombs[b].x > 0) {
			--targets[cntTarget].x;
			++cntTarget;
		}
		if (pBombs[b].x < COLUMN - 1) {
			++targets[cntTarget].x;
			++cntTarget;
		}

		for (int t = 0; t < cntTarget; ++t) {
			// 플레이어 폭사
			if (targets[t].y == pPlayerPos->y && targets[t].x == pPlayerPos->x) {
				pPlayerPos->y = pStartPos->y;
				pPlayerPos->x = pStartPos->x;
			}
			// 벽 파괴
			if (maze[targets[t].y][targets[t].x] == '1')
				maze[targets[t].y][targets[t].x] = '0';
		}

		// 폭탄 제거
		maze[pBombs[b].y][pBombs[b].x] = '0';
	}

	cntBomb = 0;
}  // end of detonateBomb()

int main() {
	char maze[ROW][COLUMN];
	char ipt;
	Point playerPos, startPos, endPos;
	int cntBomb = 0;
	Point bombs[BOMB_MAX];

	initMaze(maze, &playerPos, &startPos, &endPos);

	while (true) {
		printMaze(maze, &playerPos);
		if (playerPos.y == endPos.y && playerPos.x == endPos.x) {
			cout << "출구에 도착했습니다!\n";
			break;
		}
		cout << "t, u: 폭탄 설치/폭파\n";
		cout << "w, s, a, d: 상하좌우 이동 / q: 종료\n";
		ipt = _getch();
		ipt = tolower(ipt);

		if (ipt == 'q') exit(0);
		if (ipt == 't') placeBomb(maze, &playerPos, cntBomb, bombs);
		else if (ipt == 'u') detonateBomb(maze, &playerPos, &startPos, cntBomb, bombs);
		else movePlayer(maze, &playerPos, ipt);
	}

	return 0;
}
