#pragma once
#include "value.h"

class Core
{
	// 싱글톤 인스턴스
	static Core * pInst;
	
	// 커서 관리
	HANDLE consoleHandle;

	Core();
	~Core();

public:

	static Core * getInst() {
		if (!pInst) pInst = new Core;
		
		return pInst;
	}
	
	static void destroyInst() {
		SAFE_DELETE(pInst);
	}

	bool init();
	void run();
	void setConsolePos(int y, int x);
};
