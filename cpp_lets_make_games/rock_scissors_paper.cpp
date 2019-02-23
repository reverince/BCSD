#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;

enum RSP {
  END, ROCK, SCISSORS, PAPER
};

int main() {
  srand((unsigned int)time(0)); // 난수 테이블 생성
  
  int player, ai, state;
  
  while (true) {
    
    cout << "0. 종료 / 1. 가위 / 2. 바위 / 3. 보\n";
    cout << "메뉴를 선택하세요: ";
    cin >> player;
    
    if (player == END) break;
    
    if (player < END || player > PAPER) {
      cout << "잘못된 값을 입력했습니다.\n";
      continue;
    }
    
    ai = rand() % 3 + ROCK;
    
    cout << "AI: ";
    switch (ai) {
      case ROCK:
        cout << "가위\n";
        break;
      case SCISSORS:
        cout << "바위\n";
        break;
      case PAPER:
        cout << "보\n";
        break;
    }
    
    state = player - ai;
    
    switch (state) {
      case 1:
      case -2:
        cout << "플레이어가 이겼습니다!\n";
        break;
      case 0:
        cout << "비겼습니다.\n";
        break;
      default:
        cout << "컴퓨터가 이겼습니다.\n";
        break;
    }
  }
  
  return 0;
}
