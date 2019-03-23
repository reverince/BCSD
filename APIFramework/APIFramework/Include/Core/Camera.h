#pragma once
#include "..\Game.h"

class Camera
{
	DECLARE_SINGLE(Camera);

	POSITION m_pos;
	POSITION m_pivot;
	RESOLUTION m_rsClient;
	RESOLUTION m_rsWorld;
	class Object * m_pTarget;

public:

	void SetPos(const POSITION & pos) { m_pos = pos; }
	void SetPos(float x, float y) { m_pos = POSITION(x, y); }
	void SetPivot(const POSITION & pos) { m_pivot = pos; }
	void SetPivot(float x, float y) { m_pivot = POSITION(x, y); }
	void SetClientRS(const RESOLUTION & rs) { m_rsClient = rs; }
	void SetClientRS(UINT w, UINT h) { m_rsClient.w = w; m_rsClient.h = h; }
	void SetWorldRS(const RESOLUTION & rs) { m_rsWorld = rs; }
	void SetWorldRS(UINT w, UINT h) { m_rsWorld.w = w; m_rsWorld.h = h; }
	POSITION GetPos() const { return m_pos; }

	void SetTarget(class Object * pObj);

	bool Init(const POSITION & pos, const RESOLUTION & rsClient, const RESOLUTION & rsWorld);
	void Input(float deltaTime);
	void Update(float deltaTime);
};
