#pragma once

#define OBSTACLE(i, j, x) (m_obstacles[j][i].find(#x) != string::npos)

struct CONNECTION {
	int nEnd;
	float cost;
};

struct NODE {
	int row;
	int col;
	CVector pos;
	list<CONNECTION> conlist;

	float costSoFar;
	int nConnection;
	bool open, closed;
};

class Pathfinding
{
	public:
		string m_obstacles[10][10];
		vector<NODE> m_graph;

		Pathfinding();
		int findNode(int i, int j);
		void setObstacles(string obstacle[10][10]);
		void initialize();
		void draw(CGraphics* g);
		bool dijkstra(int nStart, int nGoal, vector<int>& path);
};