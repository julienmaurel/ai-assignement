#include "stdafx.h"
#include "Worker.h"

CWorker::CWorker(Sint16 x, Sint16 y, CGraphics* pGraphicsLeft, CGraphics* pGraphicsRight, CTreeList m_trees, Uint32 time) : 
	CSprite(x, y, 0, 0, time),
	m_accessibilityLayout
	{
		{1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f ,1.f},
		{1.f, 1.f, 1.f, 1.f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f ,1.f},
		{1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 0.5f ,1.f},
		{1.f, 1.f, 1.f, 1.f, 0.5f, 1.f, 1.f, 1.f, 0.5f ,1.f},
		{1.f, 1.f, 1.f, 0.5f, 0.5f, 1.f, 1.f, 1.f, 0.5f ,1.f},
		{1.f, 1.f, 1.f, 0.5f, 1.f, 1.f, 1.f, 1.f, 0.5f ,1.f},
		{1.f, 1.f, 1.f, 0.5f, 1.f, 1.f, 1.f, 1.f, 0.5f ,1.f},
		{1.f, 1.f, 1.f, 0.5f, 1.f, 1.f, 1.f, 0.5f, 0.5f ,1.f},
		{1.f, 1.f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f ,1.f},
		{1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f ,1.f},
	},
	// The obstacle layout specifies the connections to remove from each cell in the pathfinding graph, the connections are removed anti-clockwise.
	// (Exemple : "03" means the first and fourth connections are removed i.e the right and upper-left-diagonal ones)
	m_obstacleLayout
	{
		{"01234567", "01234567", "01234567", "01234567", "01234567", "01234567", "01234567", "01234567", "01234567", "01234567"},
		{"01234567", "01234567", "01234567", "134567", "17", "10", "701", "701", "7", "01234567"},
		{"01234567", "01234567", "01234567", "0123567", "01234567", "3457", "13457", "012345", "567", "01234567"},
		{"01234567", "", "713", "014", "375", "137", "01234567", "123457", "567", "01234567"},
		{"01234567", "3", "01234567", "345", "1357", "01234567", "357", "123", "567", "01234567"},
		{"01234567", "", "01234567", "13", "01234567", "1357", "017", "01237", "567", "01234567"},
		{"01234567", "1", "01234567", "7", "0135", "01237", "134567", "0123457", "567", "01234567"},
		{"01234567", "", "0135", "017", "70134", "701345", "701235", "34567", "5", "01234567"},
		{"01234567", "", "34", "345", "345", "345", "345", "5", "", "01234567"},
		{"01234567", "01234567", "01234567", "01234567", "01234567", "01234567", "01234567", "01234567", "01234567", "01234567"},

	},
	m_pathfinder(m_accessibilityLayout, m_obstacleLayout),
	m_trees(m_trees)
{
	LoadAnimation(pGraphicsLeft, "idleL", CSprite::Sheet(6, 6).Row(5).From(0).To(5));
	LoadAnimation(pGraphicsRight, "idleR", CSprite::Sheet(6, 6).Row(5).From(0).To(5));
	LoadAnimation(pGraphicsLeft, "walkL", CSprite::Sheet(6, 6).Row(4).From(0).To(5));
	LoadAnimation(pGraphicsRight, "walkR", CSprite::Sheet(6, 6).Row(4).From(0).To(5));
	LoadAnimation(pGraphicsRight, "cutting", CSprite::Sheet(6, 6).Row(2).From(0).To(5));
	SetAnimation("idleR");

	m_pathfinder.initialize();
	m_speed = 250;
	m_nWood = 0;
	m_woodLimit = 5;
	m_totalWoodCount = 0;

	m_state = WALKING;
	m_pCurrentTree = NULL;
	m_currentDestination = CVector(0, 0);
	updateDestination();

	m_housePos = CVector(32.f + 2 * 64.f, 32.f + 1 * 64.f) + CVector(-20.f, 20.f);
}

CWorker::~CWorker(void)
{
}

Pathfinding CWorker::getPathfinder() 
{
	return m_pathfinder;
}

float CWorker::getAccessibility(int i, int j) {
	return m_accessibilityLayout[i][j];
}

int *CWorker::getCell(void) {
	int cell[2] = { (int)(floor(GetY() / 64.f)), (int)(floor(GetX() / 64.f)) };
	return cell;
}

CVector CWorker::getDestination()
{
	return m_currentDestination;
}

list<CVector> &CWorker::getWaypoints()
{
	return m_waypoints;
}

float CWorker::getSpeed()
{
	return m_speed;
}

int CWorker::getTotalWoodCount()
{
	return m_totalWoodCount;
}

int CWorker::getWoodCount()
{
	return m_nWood;
}

int CWorker::getWoodLimit()
{
	return m_woodLimit;
}

void CWorker::updateDestination() 
{
	// Keep the grown trees
	vector<CTree*> trees;
	for (CTree* t : m_trees)
	{
		if (t->getState() == CTree::GROWN) 
		{
			trees.push_back(t);
		}
	}

	// Decide wether to go cutting wood or dropping it in the house
	if (trees.empty() || m_nWood == m_woodLimit)
	{
		m_currentDestination = m_housePos;
		m_pCurrentTree = NULL;
	} 
	else if (!trees.empty()) 
	{
		// Find the closest tree to the worker
		vector<CTree*>::iterator iTree =
			min_element(trees.begin(), trees.end(), [this](CTree* t1, CTree* t2) -> bool {
			return Distance(t1->GetPos(), GetPos()) < Distance(t2->GetPos(), GetPos());
				});
		int iClosestTree = iTree - trees.begin();
		m_currentDestination = trees[iClosestTree]->GetPos() - CVector(32.f, 64.f);
		m_pCurrentTree = trees[iClosestTree];
	}

	// Use Dijkstra algorithm to add the waypoints
	int nFirst = m_pathfinder.findClosestNode(GetPos());
	int nLast = m_pathfinder.findClosestNode(m_currentDestination);
	vector<int> path;
	if (m_pathfinder.dijkstra(nFirst, nLast, path))
	{
		m_pathfinder.addWaypoints(path, m_waypoints);
		m_waypoints.push_back(m_currentDestination);
	}
}

void CWorker::changeState(STATE newState)
{
	if (newState == m_state)
		return;

	m_state = newState;

	switch (m_state)
	{
	case IDLE:
		m_waypoints.clear();
		SetVelocity(CVector(0, 0));
		SetAnimation("idleR");
		break;
	case WALKING:
		updateDestination();
		break;
	case CUTTING:
		SetAnimation("cutting");
		break;
	}
}

bool isSameArea(CVector c1, CVector c2) 
{
	return abs(c1.GetX() - c2.GetX()) < 5 && abs(c1.GetY() - c2.GetY()) < 5;
}

bool CWorker::isTreeAvailable()
{
	vector<CTree*> trees;
	for (CTree* t : m_trees)
	{
		if (t->getState() == CTree::GROWN)
		{
			trees.push_back(t);
		}
	}
	return !trees.empty();
}

void CWorker::OnUpdate(Uint32 time, Uint32 deltaTime)
{
	// State dependant actions
	switch (m_state)
	{
	case IDLE:
		if (m_nWood > 0 && isSameArea(GetPos(), m_housePos))
		{
			m_totalWoodCount += m_nWood;
			m_nWood = 0;
		}
		break;
	case CUTTING:
		if (m_pCurrentTree->hit())
		{
			m_nWood++;
		}
		break;
	case WALKING:
		break;
	}

	// Transitions
	switch (m_state)
	{
	case IDLE:
		if (m_pCurrentTree && isSameArea(GetPos(), m_pCurrentTree->GetPos() - CVector(32.f, 64.f)) && m_pCurrentTree->getState() == CTree::GROWN) 
		{
			changeState(CUTTING);
		}
		if (m_pCurrentTree && isSameArea(GetPos(), m_pCurrentTree->GetPos() - CVector(32.f, 64.f)) && m_pCurrentTree->getState() == CTree::CUT)
		{
			changeState(WALKING);
		}
		if (isSameArea(GetPos(), m_housePos) && m_nWood == 0 && isTreeAvailable())
		{
			changeState(WALKING);
		}
		break;
	case CUTTING:
		if (m_pCurrentTree && m_pCurrentTree->GetHealth() <= 0)
		{
			changeState(IDLE);
		}
		break;
	case WALKING:
		if (m_pCurrentTree && isSameArea(GetPos(), m_pCurrentTree->GetPos() - CVector(32.f, 64.f)) && m_pCurrentTree->getState() == CTree::GROWN)
		{
			changeState(IDLE);
		}
		if (isSameArea(GetPos(), m_housePos) && (m_nWood > 0 || !isTreeAvailable()))
		{
			changeState(IDLE);
		}
		break;
	}
	CSprite::OnUpdate(time, deltaTime);
}