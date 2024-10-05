#pragma once

class CTree : public CSprite 
{
public:
	enum STATE { GROWN, CUT };

private:
	STATE state;
	float health;

public:
	CTree(Sint16 x, Sint16 y, char* pFileBitmap, Uint32 time);
	CTree(Sint16 x, Sint16 y, CGraphics* pGraphics, Uint32 time);
	~CTree(void);

	void OnUpdate(Uint32 time, Uint32 deltaTime);

	void ChangeState(STATE newState);
	STATE GetState() { return state; }

	float GetHealth() { return health; }
};

typedef std::_gfc_std_ext<std::list<CTree*>> CTreeList;
