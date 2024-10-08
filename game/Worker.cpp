#include "stdafx.h"
#include "Worker.h"

CWorker::CWorker(Sint16 x, Sint16 y, CGraphics* pGraphicsLeft, CGraphics* pGraphicsRight, Uint32 time) : CSprite(x, y, 0, 0, time)
{
	LoadAnimation(pGraphicsLeft, "idleL", CSprite::Sheet(6, 6).Row(5).From(0).To(5));
	LoadAnimation(pGraphicsRight, "idleR", CSprite::Sheet(6, 6).Row(5).From(0).To(5));
	LoadAnimation(pGraphicsLeft, "walkL", CSprite::Sheet(6, 6).Row(4).From(0).To(5));
	LoadAnimation(pGraphicsRight, "walkR", CSprite::Sheet(6, 6).Row(4).From(0).To(5));
	SetAnimation("idleR");
}

CWorker::~CWorker(void)
{
}

void CWorker::OnUpdate(Uint32 time, Uint32 deltaTime)
{
	CSprite::OnUpdate(time, deltaTime);
}