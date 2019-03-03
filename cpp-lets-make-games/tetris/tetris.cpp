#include "pch.h"
#include "Core.h"

int main()
{
	if (!Core::getInst()->init()) {
		Core::destroyInst();
		return 0;
	}

	Core::getInst()->run();

	Core::destroyInst();

	return 0;
}
