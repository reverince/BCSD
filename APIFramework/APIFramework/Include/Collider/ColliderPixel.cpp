#include "ColliderPixel.h"
#include "..\Core\PathManager.h"
#include "..\Object\Object.h"
#include "ColliderCircle.h"
#include "ColliderRect.h"

ColliderPixel::ColliderPixel()
{
}

ColliderPixel::ColliderPixel(const ColliderPixel & collider) :
	Collider(collider)
{
}

ColliderPixel::~ColliderPixel()
{
}

bool ColliderPixel::Init()
{
	return true;
}

void ColliderPixel::Input(float deltaTime)
{
}

int ColliderPixel::Update(float deltaTime)
{
	return 0;
}

int ColliderPixel::LateUpdate(float deltaTime)
{
	return 0;
}

bool ColliderPixel::Collision(Collider * pDest)
{
	return false;
}

void ColliderPixel::Render(HDC hDC, float deltaTime)
{
}

ColliderPixel * ColliderPixel::Clone()
{
	return new ColliderPixel(*this);
}
