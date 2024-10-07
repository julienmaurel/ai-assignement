#pragma once

struct CONNECTION {
	int nEnd;
	float cost;
};

struct NODE {
	CVector pos;
	list<CONNECTION> conlist;
};

class Pathfinding
{
	bool m_obstacles[10][10];
	vector<NODE> m_graph;

	Pathfinding();
	void setObstacles(bool obstacle[10][10]);
	void initialize();
};