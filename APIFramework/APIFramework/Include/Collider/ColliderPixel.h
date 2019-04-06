#pragma once
#include "Collider.h"

typedef struct Pixel
{
	UCHAR r, g, b;
} PIXEL;

class ColliderPixel : public Collider
{
	vector<PIXEL> m_pixels;

protected:
	
	ColliderPixel();
	ColliderPixel(const ColliderPixel & collider);
	virtual ~ColliderPixel();

public:

	bool SetPixel(char * pFileName, const string & pathKey = PATH_TEXTURE)
	{
		return true;
	}

	virtual bool Init();
	virtual void Input(float deltaTime);
	virtual int Update(float deltaTime);
	virtual int LateUpdate(float deltaTime);
	virtual bool Collision(Collider * pDest);
	virtual void Render(HDC hDC, float deltaTime);
	virtual ColliderPixel * Clone();
};
