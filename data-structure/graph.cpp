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
class Graph {
    set<Node<T>*> nodes;

    public:

    Graph() : nodes(NULL) { }
    Graph(set<Node<T>*> e) : nodes(e) { }
};
