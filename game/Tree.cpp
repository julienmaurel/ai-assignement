#include "stdafx.h"
#include "Tree.h"

CTree::CTree(Sint16 x, Sint16 y, CGraphics* pGraphics, Uint32 time) : CSprite(x, y, 0, 0, time)
{
	LoadAnimation(pGraphics, "wind", CSprite::Sheet(4, 3).Row(2).From(0).To(3));
	SetAnimation("wind");

	health = 100;
	state = GROWN;
}

CTree::~CTree(void)
{
}

void CTree::OnUpdate(Uint32 time, Uint32 deltaTime)
{
	CSprite::OnUpdate(time, deltaTime);
}
