#pragma once
#include "value.h"

class StageManager
{
	// ΩÃ±€≈Ê ¿ŒΩ∫≈œΩ∫
	static StageManager * pInst;

	class Stage * pCurStage;

	StageManager();
	~StageManager();

public:

	static StageManager * getInst() {
		if (!pInst) pInst = new StageManager;

		return pInst;
	}
	static void destroyInst() {
		SAFE_DELETE(pInst);
	}

	class Stage * getCurStage() const { return pCurStage; }

	bool init();
	void run();
};
