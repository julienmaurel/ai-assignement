#include "stdafx.h"
#include "Worker.h"

CWorker::CWorker(Sint16 x, Sint16 y, CGraphics* pGraphicsLeft, CGraphics* pGraphicsRight, Uint32 time) : CSprite(x, y, 0, 0, time)
{
	state = IDLE;
	LoadAnimation(pGraphicsLeft, "idleL", CSprite::Sheet(6, 6).Row(5).From(0).To(5));
	LoadAnimation(pGraphicsRight, "idleR", CSprite::Sheet(6, 6).Row(5).From(0).To(5));
	LoadAnimation(pGraphicsLeft, "walkL", CSprite::Sheet(6, 6).Row(4).From(0).To(5));
	LoadAnimation(pGraphicsRight, "walkR", CSprite::Sheet(6, 6).Row(4).From(0).To(5));
	LoadAnimation(pGraphicsRight, "cutting", CSprite::Sheet(6, 6).Row(2).From(0).To(5));
	SetAnimation("idleR");
}

CWorker::~CWorker(void)
{
}

int *CWorker::getCell(void) {
	int cell[2] = { (int)(floor(GetY() / 64.f)), (int)(floor(GetX() / 64.f)) };
	return cell;
}

void CWorker::ChangeState(STATE newState)
{
	if (newState == state)
		return;		// No state change

	state = newState;

	switch (state)
	{
	case IDLE:
		SetVelocity(0, 0);
		SetAnimation("idleR");
		break;
	case WALKING:
		break;
	case CUTTING:
		SetVelocity(0, 0);
		SetAnimation("cutting");
		break;
	}
}

void CWorker::OnUpdate(Uint32 time, Uint32 deltaTime)
{
	// State dependant actions
	switch (state)
	{
	case IDLE:
		break;
	case CUTTING:
		break;
	case WALKING:
		break;
	}

	// Transitions
	switch (state)
	{
	case IDLE:
		break;
	case CUTTING:
		break;
	case WALKING:
		break;
	}
	CSprite::OnUpdate(time, deltaTime);
}