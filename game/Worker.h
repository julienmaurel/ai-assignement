#pragma once

#include "Pathfinding.h"
#include "Tree.h"

class CWorker : public CSprite
{

public:
	enum STATE { NONE, IDLE, WALKING, CUTTING };

private:
	float m_accessibilityLayout[10][10];
	string m_obstacleLayout[10][10];
	Pathfinding m_pathfinder;
	list<CVector> m_waypoints;

	STATE m_state;
	CVector m_currentDestination;
	CTree* m_pCurrentTree;
	
	CTreeList m_trees;

public:
	CWorker(Sint16 x, Sint16 y, CGraphics* pGraphicsLeft, CGraphics* pGraphicsRight, CTreeList m_trees, Uint32 time);
	~CWorker(void);

	int* getCell(void);

	void changeState(STATE newState);
	STATE getState() { return m_state; }
	Pathfinding getPathfinder();
	float getAccessibility(int i, int j);
	CVector getDestination();
	list<CVector> &getWaypoints();
	void updateDestination();

	void OnUpdate(Uint32 time, Uint32 deltaTime);
};

typedef std::_gfc_std_ext<std::list<CWorker*>> CWorkerList;
