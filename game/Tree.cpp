#include "stdafx.h"
#include "Tree.h"

CTree::CTree(Sint16 x, Sint16 y, CGraphics* pGraphics, Uint32 time) : CSprite(x, y, 0, 0, time)
{
	LoadAnimation(pGraphics, "wind", CSprite::Sheet(4, 3).Row(2).From(0).To(3));
	LoadAnimation(pGraphics, "stroke", CSprite::Sheet(4, 3).Row(1).From(1).To(0));
	SetAnimation("wind");
	m_cutImage = new CGraphics(REPOSITORY + "/game/images/assets/Resources/Trees/Tree.png", 4, 3, 0, 0);

	SetHealth(100.f);
	m_state = GROWN;
}

CTree::~CTree(void)
{
}

// Return true if the tree was cut
bool CTree::hit()
{
	if (m_state != STROKE)
	{
		changeState(STROKE);
	}
	int secondsDuration = 2;
	SetHealth(GetHealth() - (100.f / (60 * secondsDuration)));
	if (GetHealth() <= 0)
	{
		changeState(CUT);
		return true;
	}

	return false;
}

void CTree::regenerate()
{
	changeState(GROWN);
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
	else if (newState == CUT)
	{
		SetImage(m_cutImage);
	}
	else
	{
		SetAnimation("stroke", 2.8);
	}
}	

void CTree::OnUpdate(Uint32 time, Uint32 deltaTime)
{
	CSprite::OnUpdate(time, deltaTime);
}
