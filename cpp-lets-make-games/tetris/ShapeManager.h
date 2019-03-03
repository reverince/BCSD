#pragma once
#include "value.h"

class ShapeManager
{
	class Shape * pCurShape;  // 현재 나온 도형
	class Shape * pNextShape;  // 다음에 나올 도형
	int speed;

	// 싱글톤 인스턴스
	static ShapeManager * pInst;

	ShapeManager();
	~ShapeManager();

public:

	static ShapeManager * getInst() {
		if (!pInst) pInst = new ShapeManager;

		return pInst;
	}
	static void destroyInst() {
		SAFE_DELETE(pInst);
	}

	bool init();
	void run();
	void update();
	void render();
	class Shape * createRandomShape();
	class Shape * createShape(SHAPE_TYPE shapeType);
};
