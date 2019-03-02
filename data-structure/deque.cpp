#include "linked_list.cpp"

template <typename T>
class Deque {
  LinkedList<T> data;

  public:

  Deque() : data() { }

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

  void push_front(Node<T>* node) {
    if (data.head == NULL) {
      data.head = node;
    }
    else {
      node->next = data.head;
      data.head = node;
    }
    data.calcSize();
  }

  Node<T>* pop_back() {
    if (data.head == NULL) { return NULL; }

    Node<T>* res;
    if (data.size == 1) {
      res = data.head;
      data.head = NULL;
    }
    else {
    Node<T>* ptr = data.head;
    while (ptr->next->next) {
      ptr = ptr->next;
    }
    res = ptr->next;
    ptr->next = NULL;
    }
    data.calcSize();

    return res;
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
