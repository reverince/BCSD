#include "pch.h"
#include <iostream>
using namespace std;

template <typename T>
class StackNode {

	T datum;
	StackNode *next;

	StackNode() { };
	~StackNode() { };

	template <typename T>
	friend class Stack;
};

template <typename T>
class Stack {

	StackNode<T> *head;
	StackNode<T> *tail;
	unsigned int size;

public:

	Stack() {
		head = new StackNode<T>;
		tail = new StackNode<T>;
		size = 0;
	};
	~Stack() {
		StackNode<T> *pNode = head;

		while (pNode) {
			StackNode<T> *pNext = pNode->next;
			delete pNode;
			pNode = pNext;
		}
	};

	bool isEmpty() { return (size == 0); }

	void push(const T &datum) {
		// head 노드 다음에 삽입
		StackNode<T> *pNode = new StackNode<T>;
		StackNode<T> *pNext = head->next;
		pNode->datum = datum;
		pNode->next = pNext;
		head->next = pNode;
		++size;
	}

	T pop() {
		if (isEmpty()) exit(-1);

		StackNode<T> *pNode = head->next;
		StackNode<T> *pNext = pNode->next;
		T datum = pNode->datum;

		head->next = pNext;

		delete pNode;
		--size;

		return datum;
	}

	T top() {
		if (isEmpty()) exit(-1);

		return head->next->datum;
	}
};

int main()
{
	Stack<int> stackInt;

	for (int i = 0; i < 10; ++i) {
		stackInt.push(i + 1);
	}

	for (int i = 0; i < 5; ++i) {
		cout << stackInt.pop() << '\n';
	}

	for (int i = 0; i < 3; ++i) {
		stackInt.push(i + 1);
	}

	while (!stackInt.isEmpty()) {
		cout << stackInt.pop() << '\n';
	}

	//stackInt.pop();

	return 0;
}
