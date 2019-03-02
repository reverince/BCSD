#include "pch.h"
#include <iostream>
using namespace std;

template <typename T>
class VectorNode {
	T datum;
	int index;

	VectorNode() { };
	~VectorNode() { };

	template<typename T>
	friend class Vector;
};

template <typename T>
class Vector {
	unsigned int size;
	unsigned int capacity;
	VectorNode<T> *pNode;

public:
	// 머리 꼬리 노드를 위해 2를 더함
	Vector() : size(0), capacity(2), pNode(new VectorNode<T>[capacity + 2]) { }
	~Vector() { delete[] pNode; }

	unsigned int getSize() const { return size; }
	unsigned int getCapacity() const { return capacity; }

	bool isFull() { return size == capacity; }
	bool isEmpty() { return size == 0; }

	T operator[](int idx) {  // 인덱스 연산자 오버라이딩
		return pNode[idx + 1].datum;
	}

	void resize(int _size) {
		VectorNode<T> *pNewNode = new VectorNode<T>[_size + 2];

		// 첫 노드는 머리 노드이므로 다음 노드부터 복사
		memcpy(pNewNode + 1, pNode + 1, sizeof(VectorNode<T>) * size);

		delete[] pNode;
		pNode = pNewNode;
		capacity = _size;
	}

	void push_back(const T &datum) {
		if (isFull()) {
			resize(capacity * 2);
		}

		pNode[size + 1].datum = datum;
		// pNode 실제 데이터는 1번부터 시작이지만 index는 0부터 시작
		pNode[size + 1].index = size;
		++size;
	}

	void reserve(int _size) {
		delete[] pNode;
		pNode = new VectorNode<T>[_size + 2];
		size = 0;
		capacity = _size;
	}

	void clear() {
		delete[] pNode;
		pNode = new VectorNode<T>[capacity + 2];
		size = 0;
		capacity = 2;
	}
};

int main()
{
	Vector<int> vectorInt;

	vectorInt.reserve(50);  // 여러 번(2, 4, 8, 16, 32)의 resize 방지

	for (int i = 0; i < 50; ++i) {
		vectorInt.push_back(i + 1);
	}

	for (int i = 0; i < vectorInt.getSize(); ++i) {
		cout << vectorInt[i] << '\n';
	}

	return 0;
}
