#include <iostream>

template <typename T>
struct BinaryTreeNode {
    T datum;
    BinaryTreeNode* left;
    BinaryTreeNode* right;

    public:

    BinaryTreeNode(T t) : datum(t) { }
};

template <typename T>
class BinaryTree {
    BinaryTreeNode<T>* root;

    public:

    BinaryTree() : root(NULL) { }
    BinaryTree(BinaryTreeNode<T>* r) : root(r) { }
};
