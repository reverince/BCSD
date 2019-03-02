#include "pch.h"
#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <cstring>
#include <time.h>
using namespace std;

const char* FILE_NAME = "mazes.txt";
const int MAZE_NAME_MAX = 256;
const int ROW = 6;
const int COLUMN = 11;
const int BOMB_MAX = 3;  // 동시에 설치할 수 있는 최대 폭탄 수
const int BOMB_POWER_MAX = 5;

enum DIRECTION { NONE, NORTH, SOUTH, WEST, EAST };

struct Point {
	int y, x;
};

struct Player {
	Point pos;
	bool canPush = false;
	bool isGhost = false;
	int bombPower = 1;
};

void initMaze(char maze[ROW][COLUMN],
	Player* pPlayer, Point* pStartPos, Point* pEndPos) {
	FILE* pFile = nullptr;
	fopen_s(&pFile, "mazes.txt", "rt");
	if (pFile) {
		char ch;
		fread(&ch, 1, 1, pFile);
		int mazeCount = atoi(&ch);
		char** pMazeList = new char*[mazeCount];
		fread(&ch, 1, 1, pFile);

		for (int i = 0; i < mazeCount; ++i) {
			int nameCount = 0;

			// 파일 이름 저장 배열
			pMazeList[i] = new char[MAZE_NAME_MAX];

			while (true) {
				fread(&ch, 1, 1, pFile);

				if (ch != '\n') {
					pMazeList[i][nameCount] = ch;
					++nameCount;
				}
				else break;
			}

			// 0으로 문자열의 끝 확인
			pMazeList[i][nameCount] = 0;
		}

		fclose(pFile);

		// 미로 선택
		for (int i = 0; i < mazeCount; ++i) {
			cout << i + 1 << ". " << pMazeList[i] << "\n";
		}
		cout << "미로를 선택하세요: ";
		int ipt;
		cin >> ipt;

		fopen_s(&pFile, pMazeList[ipt - 1], "rt");
		if (pFile) {
			for (int i = 0; i < ROW; ++i) {
				fread(maze[i], 1, COLUMN - 1, pFile);

				// 입구 출구 확인
				for (int j = 0; j < COLUMN - 1; ++j) {
					if (maze[i][j] == '2') {
						pStartPos->y = i;
						pStartPos->x = j;
						pPlayer->pos = *pStartPos;
					}
					else if (maze[i][j] == '3') {
						pEndPos->y = i;
						pEndPos->x = j;
					}
				}

				// 개행문자
				fread(&ch, 1, 1, pFile);
			}
		}
	}

	// 0: 길 / 1: 벽 / 2: 입구 / 3: 출구 / 4: 폭탄
	// [아이템] 5: 파워 / 6: 벽 밀기 / 7: 유령
}

void printMaze(char maze[ROW][COLUMN], Player* pPlayer) {
	system("cls");
	for (int r = 0; r < ROW - 1; ++r) {
		for (int c = 0; c < COLUMN - 1; ++c) {
			if (pPlayer->pos.y == r && pPlayer->pos.x == c) {
				cout << "★";
				continue;
			}
			if (maze[r][c] == '0') cout << "　";
			if (maze[r][c] == '1') cout << "■";
			if (maze[r][c] == '2') cout << "☆";
			if (maze[r][c] == '3') cout << "◎";
			if (maze[r][c] == '4') cout << "♨";
			if (maze[r][c] == '5') cout << "♤";
			if (maze[r][c] == '6') cout << "♡";
			if (maze[r][c] == '7') cout << "♧";
		}
		cout << '\n';
	}
}

bool addItem(char itemType, Player* pPlayer) {
	if (itemType == '5') {
		if (pPlayer->bombPower < BOMB_POWER_MAX)
			++pPlayer->bombPower;
		return true;
	}
	if (itemType == '6') {
		pPlayer->canPush = true;
		pPlayer->isGhost = false;
		return true;
	}
	if (itemType == '7') {
		pPlayer->isGhost = true;
		pPlayer->canPush = false;
		return true;
	}

	return false;
}

void movePlayer(char maze[ROW][COLUMN], Player* pPlayer, char ipt) {
	Point targetPos = pPlayer->pos;
	ipt = tolower(ipt);
	DIRECTION dir;
	switch (ipt) {
	case 'w':
		targetPos.y -= 1;
		dir = NORTH;
		break;
	case 's':
		targetPos.y += 1;
		dir = SOUTH;
		break;
	case 'a':
		targetPos.x -= 1;
		dir = WEST;
		break;
	case 'd':
		targetPos.x += 1;
		dir = EAST;
		break;
	default:
		return;
	}

	char *tile = &maze[targetPos.y][targetPos.x];

	// 유효성 검사
	if (targetPos.y < 0 || targetPos.y >= ROW - 1 ||
		targetPos.x < 0 || targetPos.x >= COLUMN - 1)
		return;
	if (!pPlayer->canPush && !pPlayer->isGhost && (*tile == '1' || *tile == '4'))
		return;

	if (pPlayer->canPush & *tile == '1') {
		char *tileBehind = nullptr;  // 벽 너머 타일
		switch (dir) {
		case NORTH:
			if (targetPos.y == 0) return;
			tileBehind = &maze[targetPos.y - 1][targetPos.x];
			break;
		case SOUTH:
			if (targetPos.y == ROW - 2) return;
			tileBehind = &maze[targetPos.y + 1][targetPos.x];
			break;
		case WEST:
			if (targetPos.x == 0) return;
			tileBehind = &maze[targetPos.y][targetPos.x - 1];
			break;
		case EAST:
			if (targetPos.x == COLUMN - 2) return;
			tileBehind = &maze[targetPos.y][targetPos.x + 1];
			break;
		}
		// 뒤 타일 검사
		if (*tileBehind == '1' || *tileBehind == '2' || *tileBehind == '3' || *tileBehind == '4')
			return;
		// 벽 이동 (아이템 있을 시 파괴)
		*tile = '0';
		*tileBehind = '1';
	}  // end of if (pPlayer->canPush & *tile == '1')

	pPlayer->pos = targetPos;

	// 아이템 습득 후 길로 전환
	if (addItem(*tile, pPlayer))
		*tile = '0';
}

void placeBomb(char maze[ROW][COLUMN], const Player* pPlayer, int& cntBomb, Point* pBombs) {
	if (cntBomb >= BOMB_MAX) return;
	char *tile = &maze[pPlayer->pos.y][pPlayer->pos.x];
	if (*tile == '1' || *tile == '4') return;

	pBombs[cntBomb] = pPlayer->pos;
	++cntBomb;
	*tile = '4';
}

void detonateBomb(char maze[ROW][COLUMN], Player* pPlayer, const Point* pStartPos, int& cntBomb, Point* pBombs) {
	for (int b = 0; b < cntBomb; ++b) {
		Point targets[1 + BOMB_POWER_MAX * 4] = { };
		for (int t = 0; t < 1 + BOMB_POWER_MAX * 4; ++t) {
			targets[t].y = pBombs[b].y;
			targets[t].x = pBombs[b].x;
		}
		int cntTarget = 1;

		// 파워에 따른 상하좌우 타깃 추가
		for (int i = 1; i <= pPlayer->bombPower; ++i) {
			if (targets[cntTarget].y - i >= 0) {
				targets[cntTarget].y -= i;
				++cntTarget;
			}
			if (pBombs[b].y + i <= ROW - 1) {
				targets[cntTarget].y += i;
				++cntTarget;
			}
			if (pBombs[b].x - i >= 0) {
				targets[cntTarget].x -= i;
				++cntTarget;
			}
			if (pBombs[b].x + i <= COLUMN - 1) {
				targets[cntTarget].x += i;
				++cntTarget;
			}
		}

		for (int t = 0; t < cntTarget; ++t) {
			// 플레이어 폭사
			if (targets[t].y == pPlayer->pos.y && targets[t].x == pPlayer->pos.x)
				pPlayer->pos = *pStartPos;
			// 벽 또는 아이템 파괴
			char *tile = &maze[targets[t].y][targets[t].x];
			// 벽 파괴 시 아이템 랜덤 생성
			if (*tile == '1') {
				if (rand() % 100 < 20) {
					int rnd = rand() % 100;
					if (rnd < 60)  // 60%
						*tile = '5';
					else if (rnd < 80)  // 20%
						*tile = '6';
					else  // 20%
						*tile = '7';
				}
				else
					*tile = '0';
			}
			// 아이템 파괴
			else if (*tile == '5' || *tile == '6' || *tile == '7')
				*tile = '0';
			
		}

		// 폭탄 제거
		maze[pBombs[b].y][pBombs[b].x] = '0';
	}

	cntBomb = 0;
}  // end of detonateBomb()

int main() {
	srand((unsigned int)time(0));

	char maze[ROW][COLUMN];
	char ipt;
	Player player;
	Point startPos, endPos;
	int cntBomb = 0;
	Point bombs[BOMB_MAX];

	initMaze(maze, &player, &startPos, &endPos);

	while (true) {
		printMaze(maze, &player);
		if (player.pos.y == endPos.y && player.pos.x == endPos.x) {
			cout << "출구에 도착했습니다!\n";
			break;
		}
		cout << "파워: ";
		for (int i = 0; i < player.bombPower; ++i)
			cout << "■";
		for (int i = 0; i < BOMB_POWER_MAX - player.bombPower; ++i)
			cout << "□";
		cout << "\n";
		cout << "벽 밀기: " << ((player.canPush) ? "O" : "X") << " / 유령화: " << ((player.isGhost) ? "O" : "X") << "\n";
		cout << "t, u: 폭탄 설치, 폭파 / i: 벽 밀기\n";
		cout << "w, s, a, d: 상하좌우 이동 / q: 종료\n";
		ipt = _getch();
		ipt = tolower(ipt);

		if (ipt == 'q') exit(0);
		if (ipt == 't') placeBomb(maze, &player, cntBomb, bombs);
		else if (ipt == 'u') detonateBomb(maze, &player, &startPos, cntBomb, bombs);
		else movePlayer(maze, &player, ipt);
	}

	return 0;
}
