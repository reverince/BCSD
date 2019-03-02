#include "linked_list.cpp"

template <typename T>
class Queue {
  LinkedList<T> data;

  public:

  Queue() : data() { }

  unsigned int getSize() { return data.getSize(); }

  void print() { data.print(); }

  void push_back(Node<T>* node) {
    if (data.head == NULL) {
      data.head = node;
    }
    else {
      Node<T>* ptr = data.head;
      while (ptr->next) {
        ptr = ptr->next;
      }
      ptr->next = node;
    }
    data.calcSize();
  }

  Node<T>* pop_front() {
    if (data.head == NULL) { return NULL; }

    Node<T>* res = data.head;
    if (data.size > 1) {
      data.head = data.head->next;
    }

    return res;
  }
};
