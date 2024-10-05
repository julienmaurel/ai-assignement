#pragma once

class CTree : public CSprite 
{
public:
	enum STATE { GROWN, CUT };

private:
	STATE state;
	CVector position;
	float health;

public:
	CTree(Sint16 x, Sint16 y, char* pFileBitmap, Uint32 time);
	CTree(Sint16 x, Sint16 y, CGraphics* pGraphics, Uint32 time);
	~CTree(void);

	void OnAttacked();
	void OnUpdate(Uint32 time, Uint32 deltaTime);

	void ChangeState(STATE newState);
	STATE GetState() { return state; }

	float GetHealth() { return health; }

	void SetPosition(CVector v) { position = v; }
	void Attacked();
};

typedef std::_gfc_std_ext<std::list<CTree*>> CTreeList;
