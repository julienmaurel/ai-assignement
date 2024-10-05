#include "stdafx.h"
#include "Worker.h"

CWorker::CWorker(Sint16 x, Sint16 y, CGraphics* pGraphics, Uint32 time) : CSprite(x, y, 0, 0, time)
{
	LoadAnimation(pGraphics, "idle", CSprite::Sheet(6, 6).Row(5).From(0).To(5));
	SetAnimation("idle");
}

CWorker::~CWorker(void)
{
}

void CWorker::OnUpdate(Uint32 time, Uint32 deltaTime)
{
	CSprite::OnUpdate(time, deltaTime);
}