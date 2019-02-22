#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;

const int NUMBER_MAX = 9;
const int NUMBER_CNT = 3;

int main() {
  srand((unsigned int)time(0));
  
  int nums[NUMBER_MAX], balls[NUMBER_CNT];
  
  // initiate
  for (int i = 0; i < NUMBER_MAX; ++i) {
    nums[i] = i + 1;
  }
  
  // shuffle
  int idx1, idx2;
  for (int i = 0; i < 1000; ++i) {
    idx1 = rand() % NUMBER_MAX;
    idx2 = rand() % NUMBER_MAX;
    
    swap(nums[idx1], nums[idx2]);
  }
  
  for (int i = 0; i < NUMBER_CNT; ++i) {
    balls[i] = nums[i];
  }
  
  int ipt[3], strike=0, ball=0, out=0;
  while (true) {
    cout << strike << "스트라이크 " << ball << "볼 " << out << "아웃\n";
    cout << "예상 숫자 세 개를 입력하세요: ";
    cin >> ipt[0] >> ipt[1] >> ipt[2];
  }
  
  return 0;
}