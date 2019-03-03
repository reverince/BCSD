#include "pch.h"
#include <iostream>
using namespace std;

template <typename T>
class QueueNode {

	T datum;
	QueueNode<T> *prev;
	QueueNode<T> *next;

	QueueNode() : prev(nullptr), next(nullptr) { };
	~QueueNode() { };

	template <typename T>
	friend class Queue;
};

template <typename T>
class Queue {

	QueueNode<T> *head;
	QueueNode<T> *tail;
	unsigned int size;

public:

	Queue() {
		head = new QueueNode<T>;
		tail = new QueueNode<T>;
		head->next = tail;
		tail->prev = head;
		size = 0;
	};
	~Queue() {
		QueueNode<T> *pNode = head;

		while (pNode) {
			QueueNode<T> *pNext = pNode->next;
			delete pNode;
			pNode = pNext;
		}
	};

	bool isEmpty() {
		return (size == 0);
	}

	void push(const T &datum) {
		QueueNode<T> *pNode = new QueueNode<T>;
		QueueNode<T> *pPrev = tail->prev;
		pNode->datum = datum;

		pPrev->next = pNode;
		pNode->prev = pPrev;
		pNode->next = tail;
		tail->prev = pNode;

		++size;
	}

	T pop() {
		if (isEmpty()) exit(-1);

		QueueNode<T> *pNode = head->next;
		T datum = pNode->datum;

		head->next = pNode->next;
		pNode->next->prev = head;

		delete pNode;
		--size;

		return datum;
	}

	T top() {
		if (isEmpty()) exit(-1);

		return head->next->datum;
	}
};

// 디폴트 SIZE
template <typename T, int SIZE = 100>
class CircularQueue {

	T data[SIZE];
	unsigned int head;
	unsigned int tail;
	unsigned int size;

public:

	CircularQueue() : head(0), tail(0), size(0) { };
	~CircularQueue() { };

	bool isEmpty() { return (size == 0); }
	bool isFull() { return (size == SIZE); }

	void push(const T &datum) {
		if (isFull()) exit(-1);

		// tail 순환
		int idx = (tail + 1) % (SIZE + 1);
		data[idx] = datum;
		tail = idx;
		++size;
	}

	T pop() {
		if (isEmpty()) exit(-1);

		// head 순환
		int idx = (head + 1) % (SIZE + 1);
		int datum = data[idx];
		head = idx;
		--size;

		return datum;
	}
};

int main()
{
	// Queue TEST

	Queue<int> queueInt;

	for (int i = 0; i < 10; ++i) {
		queueInt.push(i + 1);
	}

	for (int i = 0; i < 10; ++i) {
		cout << queueInt.pop() << '\n';
	}

	// CircularQueue TEST

	CircularQueue<int> circularQueueInt;

	for (int i = 0; i < 5; ++i) {
		circularQueueInt.push(i + 1);
	}

	for (int i = 0; i < 3; ++i) {
		cout << circularQueueInt.pop() << '\n';
	}

	for (int i = 0; i < 3; ++i) {
		circularQueueInt.push(i + 1);
	}

	while (!circularQueueInt.isEmpty()) {
		cout << circularQueueInt.pop() << '\n';
	}

	return 0;
}
