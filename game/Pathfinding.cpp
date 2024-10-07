#include "stdafx.h"
#include "Pathfinding.h"

Pathfinding::Pathfinding() 
{
}

void Pathfinding::setObstacles(bool obstacles[10][10]) 
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
		{
			m_obstacles[i][j] = obstacles[i][j];
		}
}

void Pathfinding::initialize() 
{
	for (int ) 
	{
		m_graph.push_back(NODE{ CVector(32.f + i * 64.f, 32.f + j * 64.f) });
	}
	for () 
	{
		int index1 = *p[0];
		int index2 = *p[1];
		NODE& node1 = m_graph[index1];
		NODE& node2 = m_graph[index2];
		node1.conlist.push_back(CONNECTION{ index2, 1 });
		node2.conlist.push_back(CONNECTION{ index1, 1 });
	}
}