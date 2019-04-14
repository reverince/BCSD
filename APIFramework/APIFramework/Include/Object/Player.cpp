#include "Player.h"
#include "..\Core\Core.h"
#include "..\Core\InputManager.h"
#include "..\Collider\ColliderRect.h"
#include "..\Collider\ColliderCircle.h"
#include "..\Animation\Animation.h"
#include "Bullet.h"

Player::Player() :
	m_fireTime(0.f), m_firePeriod(0.1f), m_isFiring(false), m_isHit(false), m_dir(MD_FRONT),  m_hp(100)
{
	m_hasPhysics = true;
	m_forceOrigin = 300.f;
	m_isFalling = true;
}

Player::Player(const Player & player) :
	DynamicObject(player)
{
	m_fireTime = player.m_fireTime;
	m_firePeriod = player.m_firePeriod;
	m_isFiring = false;
	m_isHit = false;
}

Player::~Player()
{
}

void Player::Fire()
{
	if (m_fireTime <= m_firePeriod)
		return;

	m_fireTime = 0.f;
	float theta = -0.1f * PI;
	for (int i = 0; i < 3; ++i)
	{
		Object * pBullet = Object::CloneObject("Bullet", "PlayerBullet", m_pLayer);

		pBullet->AddCollisionFunc("Bullet", CS_ENTER, (Bullet *)pBullet, &Bullet::Hit);

		POSITION pos;
		pos.x = m_pos.x + m_size.x * (1.f - m_pivot.x);
		pos.y = m_pos.y + m_size.y * (0.5f - m_pivot.y);

		pBullet->SetPos(pos.x, pos.y);
		((DynamicObject *)pBullet)->SetAngle(theta);

		theta += 0.1f * PI;

		SAFE_RELEASE(pBullet);
	}
}

void Player::Hit(float deltaTime, Collider * pSrc, Collider * pDest)
{
	if (pDest->GetObj()->GetTag() == "MinionBullet")
	{
		m_pAnimation->ChangeClip("Hit");
		if (!m_isHit)
		{
			m_isHit = true;
			m_hp -= 10;
			if (m_hp <= 0)
				Die();
		}
	}
	if (pDest->GetTag() == "StageColl")
	{
		m_gravityTime = 0.f;
		JumpEnd();
		m_pos.y = pSrc->GetHitPoint().y - m_pivot.y  * m_size.y;
	}
}

void Player::HitStay(float deltaTime, Collider * pSrc, Collider * pDest)
{
	if (pDest->GetTag() == "StageColl")
	{
		m_gravityTime = 0.f;
		JumpEnd();
		m_pos.y = pSrc->GetHitPoint().y - m_pivot.y  * m_size.y;
	}
}

bool Player::Init()
{
	SetPos(100.f, 100.f);
	SetSize(PLAYER_WIDTH, PLAYER_HEIGHT);
	SetSpeed(PLAYER_SPEED);
	SetTexture("Player", PLAYER_TEXTURE_NORMAL);

	// 콜라이더
	ColliderRect * pCollRect = AddCollider<ColliderRect>("Player");
	pCollRect->SetRect(-PLAYER_WIDTH * 0.5f, -PLAYER_HEIGHT * 0.2f,
		PLAYER_WIDTH * 0.5f, PLAYER_HEIGHT * 0.5f);
	//pCollCircle->SetCircle(POSITION(0.f, 0.f), PLAYER_RADIUS);
	pCollRect->AddCollisionFunc(CS_ENTER, this, &Player::Hit);
	pCollRect->AddCollisionFunc(CS_STAY, this, &Player::HitStay);

	// 애니메이션
	Animation * pAnim = CreateAnimation("PlayerAnim");
	AddAnimationClip("Idle", AT_ATLAS, AO_LOOP, 0.7f, 0.f, 2, 1, 0, 0, 2, 1,
		"PlayerIdleRight", PLAYER_ANIM_IDLE_RIGHT);
	AddAnimationClip("Fire", AT_ATLAS, AO_LOOP, 0.3f, 0.f, 2, 1, 0, 0, 2, 1,
		"PlayerFireRight", PLAYER_ANIM_FIRE_RIGHT);
	AddAnimationClip("Hit", AT_ATLAS, AO_ONCE_RETURN, 0.5f, 0.f, 2, 1, 0, 0, 2, 1,
		"PlayerHitRight", PLAYER_ANIM_HIT_RIGHT);

	// 이하 프레임 애니메이션 구현
	/*vector<wstring> fileNames;
	for (int i = 0; i < 8; ++i)
	{
		wchar_t fileName[MAX_PATH] = { };
		wsprintf(fileName, L"player_attack_%d.bmp", i);
		fileNames.push_back(fileName);
	}
	AddAnimationClip("AttackLeft", AT_FRAME, AO_ONCE_RETURN, 0.5f, 0.f, 2, 1, 0, 0, 2, 1,
		"PlayerAttackLeft", fileNames);*/

	SAFE_RELEASE(pAnim);

	return true;
}

void Player::Input(float deltaTime)
{
	DynamicObject::Input(deltaTime);

	if (KEYPRESS("MoveUp"))
		Jump();
		//MoveY(deltaTime, MD_BACK);
	if (KEYPRESS("MoveDown")) MoveY(deltaTime, MD_FRONT);
	if (KEYPRESS("MoveLeft"))
	{
		MoveX(deltaTime, MD_BACK);
		m_dir = MD_BACK;
	}
	if (KEYPRESS("MoveRight"))
	{
		MoveX(deltaTime, MD_FRONT);
		m_dir = MD_FRONT;
	}
	if (KEYDOWN("Fire"))
	{
		m_isFiring = true;
		m_pAnimation->ChangeClip("Fire");
	}
	if (KEYPRESS("Fire"))
		Fire();
	if (KEYUP("Fire"))
		m_isFiring = false;
	if (KEYPRESS("Slow"))
		SetSpeed(PLAYER_SPEED_SLOW);
	else
		SetSpeed(PLAYER_SPEED);
}

int Player::Update(float deltaTime)
{
	DynamicObject::Update(deltaTime);

	// 이동 관련
	m_pos.x = (m_pos.x <= 0) ? 0.f : (m_pos.x >= GET_RESOLUTION.w) ? (float)GET_RESOLUTION.w : m_pos.x;
	m_pos.y = (m_pos.y <= 0) ? 0.f : (m_pos.y >= GET_RESOLUTION.h) ? (float)GET_RESOLUTION.h : m_pos.y;

	// 발사 관련
	m_fireTime += deltaTime;

	if (m_isHit && m_pAnimation->IsClipOver())
		m_isHit = false;
	if (!m_isFiring && !m_isHit)
		m_pAnimation->ReturnClip();

	return 0;
}

int Player::LateUpdate(float deltaTime)
{
	DynamicObject::LateUpdate(deltaTime);

	return 0;
}

void Player::Collision(float deltaTime)
{
	DynamicObject::Collision(deltaTime);
}

void Player::Render(HDC hDC, float deltaTime)
{
	DynamicObject::Render(hDC, deltaTime);

	wchar_t strHP[32] = { };
	wsprintf(strHP, L"HP: %d", m_hp);
	TextOut(hDC, (int)(m_pos.x - (PLAYER_WIDTH * 0.3f)), (int)(m_pos.y - (PLAYER_HEIGHT * 0.7f)), strHP, lstrlen(strHP));
}

Player * Player::Clone()
{
	return new Player(*this);
}
