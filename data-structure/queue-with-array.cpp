#include <iostream>
using namespace std;

const unsigned int MAXSIZE = 10;

template <typename T>
class CircularQueue {
  T data[MAXSIZE];
  // front는 맨 앞 원소의 인덱스
  // rear는 맨 뒤 원소 다음 칸의 인덱스
  unsigned int front, rear, size;

  public:

  CircularQueue() : data(), front(0), rear(0), size(0) { }

  unsigned int getSize() { return size; }

  void print() {
    if (rear > front) {
      for (int i = front; i < rear; ++i) {
        cout << ' ' << data[i];
      }
    }
    else {
      for (int i = front; i < MAXSIZE; ++i) {
        cout << ' ' << data[i];
      }
      for (int i = 0; i < rear; ++i) {
        cout << ' ' << data[i];
      }
    }
    
    cout << '\n';
  }

  void push_back(T datum) {
    if (size < MAXSIZE) {
      ++size;
      data[rear++] = datum;
      if (rear >= MAXSIZE) rear = 0;
    }
    else throw runtime_error("Can't push to full queue!");
  }

  T pop_front() {
    if (size > 0) {
      --size;
      return data[front++];
      if (front >= MAXSIZE) front = 0;
    }
    else throw runtime_error("Can't pop from empty queue!");
  }
}; 

int main() {
  CircularQueue<int> que = CircularQueue<int>();

  //que.pop_front();
  for (int i = 0; i < 9; ++i) {
    que.push_back(i);
  }
  que.print();
  cout << "size: " << que.getSize() << '\n';
  for (int i = 0; i < 3; ++i) {
    cout << "pop: " << que.pop_front() << '\n';
  }
  que.print();
  cout << "size: " << que.getSize() << '\n';
  for (int i = 11; i < 15; ++i) {
    que.push_back(i);
  }
  que.print();
  cout << "size: " << que.getSize() << '\n';
  que.push_back(21);

  return 0;
}
