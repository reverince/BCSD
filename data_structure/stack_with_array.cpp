#include <iostream>
using namespace std;

const unsigned int MAXSIZE = 10;

template <typename T>
class Stack {
  T data[MAXSIZE];
  unsigned int size;

  public:

  Stack() : data(), size(0) { }

  unsigned int getSize() { return size; }

  void print() {
    for (int i = 0; i < size; ++i) {
      cout << ' ' << data[i];
    }
    cout << '\n';
  }

  void push_back(T datum) {
    if (size < MAXSIZE) {
      data[size++] = datum;
    }
    else throw runtime_error("Can't push to full stack!");
  }

  T pop_back() {
    if (size > 0) {
      --size;
      return data[size];
    }
    else throw runtime_error("Can't pop from empty stack!");
  }
};

int main() {
  Stack<int> stk = Stack<int>();

  //stk.pop_back();
  for (int i = 0; i < 10; ++i) {
    stk.push_back(i);
  }
  stk.print();
  cout << "size: " << stk.getSize() << '\n';
  for (int i = 0; i < 3; ++i) {
    cout << "pop: " << stk.pop_back() << '\n';
  }
  stk.print();
  cout << "size: " << stk.getSize() << '\n';
  for(int i = 10; i < 13; ++i) {
    stk.push_back(i);
  }
  stk.print();
  cout << "size: " << stk.getSize() << '\n';
  stk.push_back(21);  // ERROR

  return 0;
}
