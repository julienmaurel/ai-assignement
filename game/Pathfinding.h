#pragma once

#define OBSTACLE(x) m_obstacles[j][i].find(#x) == string::npos

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
		string m_obstacles[10][10];
		vector<NODE> m_graph;

		Pathfinding();
		void setObstacles(string obstacle[10][10]);
		void initialize();
		void draw(CGraphics* g);
		bool dijkstra(CVector start, CVector goal, vector<CVector>& path);
};