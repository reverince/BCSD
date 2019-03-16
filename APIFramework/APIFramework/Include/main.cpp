#include "Core.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	if (!Core::GetInst()->Init(hInstance))
	{
		Core::DestroyInst();
		return 0;
	}

	int ret = Core::GetInst()->Run();

	return ret;
}
