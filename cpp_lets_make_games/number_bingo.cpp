#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;

enum LINE { HORIZONTAL, VERTICAL, DIAGONAL };

const int ROW = 5;
const int COLUMN = 5;
const int NUM_MAX = ROW * COLUMN;
const int SHUFFLE_CNT = 1000;
const int CHECKED = -1;
const int BINGO_WIN = 4;

int bingo_player, bingo_AI;

void printBingo(int nums[NUM_MAX]) {
  // print
  for (int r = 0; r < ROW; ++r) {
    for (int c = 0; c < COLUMN; ++c) {
      if (nums[r * COLUMN + c] == CHECKED) {
        cout << "*\t";
        continue;
      }
      cout << nums[r * COLUMN + c] << "\t";
    }
    cout << "\n";
  }
}  // end of printBingo()

void countBingo(int nums[NUM_MAX], int& bingo) {
  bingo = 0;
  bool isBingo;
  // 가로 빙고
  for (int r = 0; r < ROW; ++r) {
    isBingo = true;
    for (int c = 0; c < COLUMN; ++c) {
      if (nums[r * COLUMN + c] != CHECKED) {
        isBingo = false;
        break;
      }
    }
    if (isBingo) ++bingo;
  }
  // 세로 빙고
  for (int c = 0; c < COLUMN; ++c) {
    isBingo = true;
    for (int r = 0; r < ROW; ++r) {
      if (nums[r * COLUMN + c] != CHECKED) {
        isBingo = false;
        break;
      }
    }
    if (isBingo) ++bingo;
  }
  // 대각선 빙고
  if (ROW == COLUMN) {
    // 좌상우하
    isBingo = true;
    for (int i = 0; i < ROW; ++i) {
      if (nums[i * COLUMN + i] != CHECKED) {
        isBingo = false;
        break;
      }
    }
    if (isBingo) ++bingo;
    // 우상좌하
    isBingo = true;
    for (int i = 0; i < ROW; ++i) {
      if (nums[i * COLUMN + ROW - 1 - i] != CHECKED) {
        isBingo = false;
        break;
      }
    }
    if (isBingo) ++bingo;
  }

  if (bingo >= BINGO_WIN) {
    cout << "빙고 " << bingo << "개를 완성했습니다!\n";
  }
  else {
    cout << "빙고 " << bingo << "개\n";
  }
}  // end of countBingo()

void checkWin() {
  if (bingo_player == bingo_AI && bingo_player >= BINGO_WIN) {
    cout << "무승부입니다.\n";
    exit(0);
  }
  if (bingo_player >= BINGO_WIN && bingo_player > bingo_AI) {
    cout << "플레이어가 이겼습니다!\n";
    exit(0);
  }
  if (bingo_AI >= BINGO_WIN) {
    cout << "컴퓨터가 이겼습니다.\n";
    exit(0);
  }
}

int main() {
  srand((unsigned int)time(0));
  
  int nums[NUM_MAX], nums_AI[NUM_MAX];
  
  // initiate
  for (int i = 0; i < NUM_MAX; ++i) {
    nums[i] = i + 1;
    nums_AI[i] = nums[i];
  }
  
  // shuffle
  int idx1, idx2;
  for (int i = 0; i < SHUFFLE_CNT; ++i) {
    idx1 = rand() % (NUM_MAX - 1);
    idx2 = rand() % (NUM_MAX - 1);
    
    swap(nums[idx1], nums[idx2]);
    
    idx1 = rand() % (NUM_MAX - 1);
    idx2 = rand() % (NUM_MAX - 1);
    
    swap(nums_AI[idx1], nums_AI[idx2]);
  }
  
  int ipt, ipt_AI=-1;
  bool isAISmart = false;
  while (true) {
    system("clear");
    
    cout << "1. RANDOM / 2. SMART\n";
    cout << "AI 모드를 선택하세요:";
    cin >> ipt;
    if (ipt == 2) isAISmart = true;
    if (ipt == 1 || ipt == 2) break;
  }
  
  // game
  while (true) {
    system("clear");
    
    cout << "=====< 플레이어 >=====\n";
    printBingo(nums);
    countBingo(nums, bingo_player);
    cout << "=====< 컴퓨터 (" << ((isAISmart) ? "SMART" : "RANDOM") << ") >=====\n";
    printBingo(nums_AI);
    countBingo(nums_AI, bingo_AI);
    checkWin();
    
    if (ipt_AI != -1)
      cout << "컴퓨터의 선택: " << ipt_AI << '\n';
    
    // player turn
    bool hasPlayed = false;
    while (!hasPlayed) {
      cout << "숫자를 입력하세요(0은 종료): ";
      cin >> ipt;
      if (ipt == 0) exit(0);
      if (ipt >= 1 || ipt <= NUM_MAX) {
        for (int i = 0; i < NUM_MAX; ++i) {
          if (nums[i] == ipt) {
            nums[i] = CHECKED;
            hasPlayed = true;
          }
          if (nums_AI[i] == ipt) nums_AI[i] = CHECKED;
        }
      }
    }
    
    system("clear");
    
    cout << "=====< 플레이어 >=====\n";
    printBingo(nums);
    countBingo(nums, bingo_player);
    cout << "=====< 컴퓨터 (" << ((isAISmart) ? "SMART" : "RANDOM") << ") >=====\n";
    printBingo(nums_AI);
    countBingo(nums_AI, bingo_AI);
    checkWin();
    
    // AI turn
    if (!isAISmart) {  // RANDOM AI
      int numsRemain[NUM_MAX] = {};
      int cntNumsRemain = 0;
      for (int i = 0; i < NUM_MAX; ++i) {
        if (nums_AI[i] != CHECKED) {
          numsRemain[cntNumsRemain] = nums_AI[i];
          ++cntNumsRemain;
        }
      }
      ipt_AI = numsRemain[rand() % cntNumsRemain];
    }
    else {  // SMART AI
      int cntRemain, minCntRemain = NUM_MAX;
      int line, lineNum;
      
      // 가로
      for (int r = 0; r < ROW; ++r) {
        cntRemain = 0;
        for (int c = 0; c < COLUMN; ++c) {
          if (nums_AI[r * COLUMN + c] != CHECKED) ++cntRemain;
        }
        if (cntRemain > 0 && cntRemain < minCntRemain) {
          minCntRemain = cntRemain;
          line = HORIZONTAL;
          lineNum = r;
        }
      }
      // 세로
      for (int c = 0; c < COLUMN; ++c) {
        cntRemain = 0;
        for (int r = 0; r < ROW; ++r) {
          if (nums_AI[r * COLUMN + c] != CHECKED) ++cntRemain;
        }
        if (cntRemain > 0 && cntRemain < minCntRemain) {
          minCntRemain = cntRemain;
          line = VERTICAL;
          lineNum = c;
        }
      }
      // 대각선
      if (ROW == COLUMN) {
        // 좌상우하
        cntRemain = 0;
        for (int i = 0; i < ROW; ++i) {
          if (nums_AI[i * COLUMN + i] != CHECKED) ++cntRemain;
        }
        if (cntRemain > 0 && cntRemain < minCntRemain) {
          minCntRemain = cntRemain;
          line = DIAGONAL;
          lineNum = 0;
        }
        // 우상좌하
        cntRemain = 0;
        for (int i = 0; i < ROW; ++i) {
          if (nums_AI[i * COLUMN + ROW - 1 - i] != CHECKED) ++cntRemain;
        }
        if (cntRemain > 0 && cntRemain < minCntRemain) {
          minCntRemain = cntRemain;
          line = DIAGONAL;
          lineNum = 1;
        }
      }
      
      // select
      if (line == HORIZONTAL) {
        for (int c = 0; c < COLUMN; ++c) {
          if (nums_AI[lineNum * COLUMN + c] != CHECKED) {
            ipt_AI = nums_AI[lineNum * COLUMN + c];
            break;
          }
        }
      }
      else if (line == VERTICAL) {
        for (int r = 0; r < ROW; ++r) {
          if (nums_AI[r * COLUMN + lineNum] != CHECKED) {
            ipt_AI = nums_AI[r * COLUMN + lineNum];
            break;
          }
        }
      }
      else {  // 대각선
        if (lineNum == 0) {  // 좌상우하
          for (int i = 0; i < ROW; ++i) {
            if (nums_AI[i * COLUMN + i] != CHECKED) {
              ipt_AI = nums_AI[i * COLUMN + i];
              break;
            }
          }
        }
        else {  // 우상좌하
          for (int i = 0; i < ROW; ++i) {
            if (nums_AI[i * COLUMN + ROW - 1 - i] != CHECKED) {
              ipt_AI = nums_AI[i * COLUMN + ROW - 1 - i];
              break;
            }
          }
        }
      }
    }  // end of SMART AI
    
    for (int i = 0; i < NUM_MAX; ++i) {
      if (nums[i] == ipt_AI) nums[i] = CHECKED;
      if (nums_AI[i] == ipt_AI) nums_AI[i] = CHECKED;
    }
    
  }  // end of game
  
  return 0;
}  // end of main()
