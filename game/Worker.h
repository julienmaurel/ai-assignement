#pragma once

class CWorker : public CSprite
{

public:
	CWorker(Sint16 x, Sint16 y, CGraphics* pGraphicsLeft, CGraphics* pGraphicsRight, Uint32 time);
	~CWorker(void);

	int* getCell(void);

	void OnUpdate(Uint32 time, Uint32 deltaTime);
};

typedef std::_gfc_std_ext<std::list<CWorker*>> CWorkerList;
