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
	public:
		bool m_obstacles[10][10];
		vector<NODE> m_graph;

		Pathfinding();
		void setObstacles(bool obstacle[10][10]);
		void initialize();
		void draw(CGraphics* g);
		bool dijkstra(CVector start, CVector goal, vector<CVector>& path);
};