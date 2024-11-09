#include "stdafx.h"
#include "Tree.h"

CTree::CTree(Sint16 x, Sint16 y, CGraphics* pGraphics, Uint32 time) : CSprite(x, y, 0, 0, time)
{
	LoadAnimation(pGraphics, "wind", CSprite::Sheet(4, 3).Row(2).From(0).To(3));
	SetAnimation("wind");
	m_cutImage = new CGraphics(REPOSITORY + "/game/images/assets/Resources/Trees/Tree.png", 4, 3, 0, 0);

	SetHealth(100.f);
	m_state = GROWN;
}

CTree::~CTree(void)
{
}

void CTree::hit()
{
	SetHealth(GetHealth() - 1.f);
	if (GetHealth() <= 0)
	{
		m_state = CUT;
	}
}

void CTree::regenerate()
{
	m_state = GROWN;
	SetHealth(100.f);
}

void CTree::changeState(STATE newState)
{
	if (m_state == newState)
	{
		return;
	}

	m_state = newState;
	
	if (newState == GROWN) 
	{
		SetAnimation("wind");
	}
	else 
	{
		SetImage(m_cutImage);
	}
}

void CTree::OnUpdate(Uint32 time, Uint32 deltaTime)
{
	CSprite::OnUpdate(time, deltaTime);
}
