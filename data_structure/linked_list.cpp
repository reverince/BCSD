#include <iostream>
#include <set>
using namespace std;

template <typename T>
struct Node {
    T datum;
    Node* next;

    public:

    Node(T t) : datum(t), next(NULL) { }
};

template <typename T>
class LinkedList {
    Node<T>* head;
    unsigned int size;

    void calcSize() {
        Node<T>* ptr = head;
        size = 0;
        while (ptr) {
        ++size;
        ptr = ptr->next;
        }
    }

    public:

    LinkedList() : head(NULL), size(0) { }

    unsigned int getSize() { return size; }

    void print() {
        set<Node<T>*> nodeSet;
        Node<T>* ptr = head;

        while (ptr) {
        cout << ptr->datum << ' ';
        // 순환 무한 출력 방지
        if (nodeSet.find(ptr) != nodeSet.end()) {
        cout << "...";
        break;
        }
        nodeSet.insert(ptr);
        ptr = ptr->next;
        }
        cout << '\n';
    }
};
