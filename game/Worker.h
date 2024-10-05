#pragma once

class CWorker : public CSprite
{
public:
	CWorker(Sint16 x, Sint16 y, char* pFileBitmap, Uint32 time);
	CWorker(Sint16 x, Sint16 y, CGraphics* pGraphics, Uint32 time);
	~CWorker(void);

	void OnUpdate(Uint32 time, Uint32 deltaTime);
};

typedef std::_gfc_std_ext<std::list<CWorker*>> CWorkerList;
