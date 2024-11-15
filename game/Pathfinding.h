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

	float accessibility;
};

class Pathfinding
{
	float m_accessibility[10][10];
	string m_obstacles[10][10];
	vector<NODE> m_graph;

	public:
		Pathfinding(float accessibility[10][10], string obstacles[10][10]);
		int findNode(int i, int j);
		void initialize();
		void draw(CGraphics* g);
		bool dijkstra(int nStart, int nGoal, vector<int>& path);
		int findClosestNode(CVector position);
		void addWaypoints(vector<int>& path, list<CVector>& waypoints);
};