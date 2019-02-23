#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;

const int CURSOR = -1;
const int ROW = 4;
const int COLUMN = 4;
const int NUM_MAX = ROW * COLUMN;
const int SHUFFLE_CNT = 1000;

int main() {
  srand((unsigned int)time(0));
  
  int nums[NUM_MAX], cursor;
  
  // initiate
  for (int i = 0; i < NUM_MAX; ++i) {
    nums[i] = i + 1;
  }
  cursor = NUM_MAX - 1;
  nums[cursor] = CURSOR;
  
  // shuffle
  int idx1, idx2;
  for (int i = 0; i < SHUFFLE_CNT; ++i) {
    idx1 = rand() % (NUM_MAX - 1);
    idx2 = rand() % (NUM_MAX - 1);
    
    swap(nums[idx1], nums[idx2]);
  }
  
  char ipt;
  bool isOrdered;
  while (true) {
    system("clear");
    
    // print
    for (int i = 0; i < ROW; ++i) {
      for (int j = 0; j < COLUMN; ++j) {
        if (nums[i * COLUMN + j] == CURSOR) {
          cout << "*\t";
          continue;
        }
        cout << nums[i * COLUMN + j] << "\t";
      }
      cout << "\n";
    }
    cout << "w, s, a, d: 상하좌우 이동 / q: 종료\n";
    
    // check if ordered
    isOrdered = true;
    for (int i = 0; i < NUM_MAX - 1; ++i) {
      if (nums[i] != i + 1) {
        isOrdered = false;
        break;
      }
    }
    if (isOrdered) {
      cout << "퍼즐을 완성했습니다!\n";
      break;
    }
    
    cin >> ipt;
    ipt = tolower(ipt);
    switch (ipt) {
      case 'w':
        if (cursor >= COLUMN) {
          nums[cursor] = nums[cursor - COLUMN];
          cursor -= COLUMN;
          nums[cursor] = CURSOR;
        }
        break;
      case 's':
        if (cursor < NUM_MAX - COLUMN) {
          nums[cursor] = nums[cursor + COLUMN];
          cursor += COLUMN;
          nums[cursor] = CURSOR;
        }
        break;
      case 'a':
        if (cursor % COLUMN != 0) {
          nums[cursor] = nums[cursor - 1];
          cursor -= 1;
          nums[cursor] = CURSOR;
        }
        break;
      case 'd':
        if (cursor % COLUMN != COLUMN - 1) {
          nums[cursor] = nums[cursor + 1];
          cursor += 1;
          nums[cursor] = CURSOR;
        }
        break;
      case 'q':
        cout << "게임을 종료합니다.\n";
        exit(0);
      default:
        break;
    }
  }
  
  return 0;
}
