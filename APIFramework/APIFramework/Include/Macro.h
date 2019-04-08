#pragma once

#define CLASS_NAME L"WinAPI02"

// Ű
#define PATH_ROOT "RootPath"
#define PATH_TEXTURE "TexturePath"
#define COLORKEY_DEFAULT RGB(0, 255, 0)

// ����
#define WND_WIDTH 1600
#define WND_HEIGHT 900
#define WORLD_WIDTH 1600
#define WORLD_HEIGHT 900

#define PLAYER_WIDTH 100.f
#define PLAYER_HEIGHT PLAYER_WIDTH
#define PLAYER_RADIUS 50.f
#define PLAYER_SPEED 500.f
#define PLAYER_SPEED_SLOW PLAYER_SPEED * 0.5f
#define MINION_WIDTH 100.f
#define MINION_HEIGHT MINION_WIDTH
#define MINION_SPEED 300.f
#define BULLET_WIDTH 50.f
#define BULLET_HEIGHT BULLET_WIDTH
#define BULLET_RADIUS 25.f
#define BULLET_SPEED 1000.f

// ����
#define BACK_BUFFER_TEXTURE L"back_buffer.bmp"
#define STAGE_TEXTURE "stage1.bmp"
#define STAGE_TEXTURE_L L"stage1.bmp"
#define PLAYER_TEXTURE_NORMAL L"player_normal.bmp"
#define PLAYER_ANIM_IDLE_RIGHT L"player_idle_right.bmp"
#define PLAYER_ANIM_FIRE_RIGHT L"player_fire_right.bmp"
#define PLAYER_ANIM_HIT_RIGHT L"player_hit_right.bmp"
#define MINION_TEXTURE L"minion.bmp"
#define BULLET_TEXTURE L"bullet.bmp"

// ���
#define PI 3.141592f
#define GRAVITY 10.0f

// �Է�
#define KEYDOWN(key) InputManager::GetInst()->KeyDown(key)
#define KEYPRESS(key) InputManager::GetInst()->KeyPress(key)
#define KEYUP(key) InputManager::GetInst()->KeyUp(key)

// �޸�
#define SAFE_DELETE(p) if (p) { delete p; p = nullptr; }
#define SAFE_DELETE_ARRAY(p) if p { delete[] p; p = nullptr; }
#define SAFE_RELEASE(p) if (p) { (p)->Release(); p = nullptr; }

// �̱���
#define DECLARE_SINGLE(Type)\
private:\
	static Type * m_pInst;\
	Type();\
	~Type();\
public:\
	static Type * GetInst()\
	{\
		if (!m_pInst)\
			m_pInst = new Type;\
		return m_pInst;\
	}\
	static void DestroyInst()\
	{\
		SAFE_DELETE(m_pInst);\
	}\
private:

#define DEFINE_SINGLE(Type) Type * Type::m_pInst = nullptr
#define GET_SINGLE(Type) Type::GetInst()
#define DESTROY_SINGLE(Type) Type::DestroyInst()

#define GET_RESOLUTION Core::GetInst()->GetResolution()
