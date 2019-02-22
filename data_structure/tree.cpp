#include <iostream>
#include <set>
using namespace std;

template <typename T>
struct Node {
    T datum;
    set<Node*> edges;

    public:

    Node(T t) : datum(t) { }
};

template <typename T>
class Tree {
    Node<T>* root;

    public:

    Tree() : root(NULL) { }
    Tree(Node<T>* r) : root(r) { }
};
