#pragma once

class CTree : public CSprite 
{
public:
	enum STATE { GROWN, CUT, STROKE };

private:
	STATE m_state;
	CGraphics* m_cutImage;

public:
	CTree(Sint16 x, Sint16 y, char* pFileBitmap, Uint32 time);
	CTree(Sint16 x, Sint16 y, CGraphics* pGraphics, Uint32 time);
	~CTree(void);

	void changeState(STATE newState);
	STATE getState() { return m_state; }

	bool hit();
	void regenerate();

	void OnUpdate(Uint32 time, Uint32 deltaTime);
};

typedef std::_gfc_std_ext<std::list<CTree*>> CTreeList;
