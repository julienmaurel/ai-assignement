#include "stdafx.h"
#include "Pathfinding.h"

Pathfinding::Pathfinding(float accessibility[10][10], string obstacles[10][10])
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
		{
			m_obstacles[i][j] = obstacles[i][j];
		}
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
		{
			m_accessibility[i][j] = accessibility[i][j];
		}
}

// Creates the graph structure with a node in the middle of each free cell (cells with no connections at all are considered obstructed).
// Connections are added according to m_obstacles.
void Pathfinding::initialize() 
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++) 
	{
		bool noObstacle = m_obstacles[j][i].find("01234567") == string::npos;
		if (noObstacle) 
		{
			NODE newNode = NODE{ i, j, CVector(32.f + j * 64.f, 32.f + i * 64.f) };
			newNode.accessibility = m_accessibility[i][j];
			m_graph.push_back(newNode);
		}
	}
	for (NODE& currentNode : m_graph)
	{
		int i = currentNode.row;
		int j = currentNode.col;
		int r = findNode(i, j + 1), ur = findNode(i + 1, j + 1), u = findNode(i + 1, j), ul = findNode(i + 1, j - 1), l = findNode(i, j - 1), bl = findNode(i - 1, j - 1), b = findNode(i - 1, j), br = findNode(i - 1, j + 1);
		if (r != -1 && !OBSTACLE(i, j, 0)) currentNode.conlist.push_back(CONNECTION{ r, Distance(currentNode.pos, m_graph[r].pos) * m_graph[r].accessibility });
		if (ur != -1 && !OBSTACLE(i, j, 1)) currentNode.conlist.push_back(CONNECTION{ ur, Distance(currentNode.pos, m_graph[ur].pos) * m_graph[ur].accessibility });
		if (u != -1 && !OBSTACLE(i, j, 2)) currentNode.conlist.push_back(CONNECTION{ u, Distance(currentNode.pos, m_graph[u].pos) * m_graph[u].accessibility });
		if (ul != -1 && !OBSTACLE(i, j, 3)) currentNode.conlist.push_back(CONNECTION{ ul, Distance(currentNode.pos, m_graph[ul].pos) * m_graph[ul].accessibility });
		if (l != -1 && !OBSTACLE(i, j, 4)) currentNode.conlist.push_back(CONNECTION{ l, Distance(currentNode.pos, m_graph[l].pos) * m_graph[l].accessibility });
		if (bl != -1 && !OBSTACLE(i, j, 5)) currentNode.conlist.push_back(CONNECTION{ bl, Distance(currentNode.pos, m_graph[bl].pos) * m_graph[bl].accessibility });
		if (b != -1 && !OBSTACLE(i, j, 6)) currentNode.conlist.push_back(CONNECTION{ b, Distance(currentNode.pos, m_graph[b].pos) * m_graph[b].accessibility });
		if (br != -1 && !OBSTACLE(i, j, 7)) currentNode.conlist.push_back(CONNECTION{ br, Distance(currentNode.pos, m_graph[br].pos) * m_graph[br].accessibility });
	}
}

// Draw the graph
void Pathfinding::draw(CGraphics* g) {
	for (NODE& n : m_graph) {

		// Draw nodes
		g->FillCircle(CVector(n.pos.GetX(), n.pos.GetY()), 5, CColor::Red());

		// Draw connections (some twice but nvm)
		for (CONNECTION& connection : n.conlist) {
			CVector target = m_graph.at(connection.nEnd).pos;
			CVector middle = CVector((n.pos.GetX() + target.GetX()) / 2, (n.pos.GetY() + target.GetY()) / 2);
			CVector direction = CVector(n.pos.GetX() + (target.GetX() - n.pos.GetX()) * 0.75, n.pos.GetY() + (target.GetY() - n.pos.GetY()) * 0.75);
			// Print weights
			// *g << font("ARIAL.ttf", 5) << color(CColor::White()) << xy(middle.GetX(), middle.GetY()) << connection.cost << endl;
			g->DrawLine(CVector(n.pos.GetX(), n.pos.GetY()), CVector(target.GetX(),target.GetY()), CColor::Red());
			g->FillCircle(CVector(direction.GetX(), direction.GetY()), 2, CColor::Red());
		}
	}
}

// Dijsktra algorithm implementation
bool Pathfinding::dijkstra(int nStart, int nGoal, vector<int>& path) {

	// Mark all nodes as unvisited
	list<int> openNodes;
	for (NODE& node : m_graph)		
		node.open = false;

	// Open the start node
	m_graph[nStart].open = true;
	m_graph[nStart].costSoFar = 0;
	m_graph[nStart].nConnection = -1;
	openNodes.push_back(nStart);
	while (openNodes.size() != 0) 
	{
		// Select the current node
		list<int>::iterator iCurrent =
			min_element(openNodes.begin(), openNodes.end(), [this](int i, int j) -> bool {
				return m_graph[i].costSoFar < m_graph[j].costSoFar;
			});
		int currentNode = *iCurrent;

		// Found the goal node ?
		if (currentNode == nGoal)
			break;
		for (CONNECTION& connection : m_graph[currentNode].conlist) 
		{
			int endNode = connection.nEnd;
			float newCostSoFar = m_graph[currentNode].costSoFar + connection.cost;

			// For open nodes, ignore if the current route is worse than the old one
			if (m_graph[endNode].open && m_graph[endNode].costSoFar <= newCostSoFar)
				continue;

			// A better route was found
			m_graph[endNode].costSoFar = newCostSoFar;
			m_graph[endNode].nConnection = currentNode;

			// If unvisited yet
			if (!m_graph[endNode].open)
			{
				m_graph[endNode].open = true;
				openNodes.push_back(endNode);
			}
		}

		// We can now close the current node
		m_graph[currentNode].closed = true;
		openNodes.erase(iCurrent);
	}

	// Collect the path
	if (openNodes.size() == 0)
		return false;
	int i = nGoal;
	while (m_graph[i].nConnection >= 0)
	{
		path.push_back(i);
		i = m_graph[i].nConnection;
	}
	path.push_back(i);
	reverse(path.begin(), path.end());
	return true;
}


int Pathfinding::findNode(int i, int j) {
	int cnt = 0;
	for (NODE& n : m_graph)
	{
		if (n.row == i && n.col == j)
			return cnt;
		cnt++;
	}
	return -1;
}

int Pathfinding::findClosestNode(CVector position) 
{
	vector<NODE>::iterator iNode =
		min_element(m_graph.begin(), m_graph.end(), [position](NODE& n1, NODE& n2) -> bool {
		return Distance(n1.pos, position) < Distance(n2.pos, position);
			});
	return iNode - m_graph.begin();
}

void Pathfinding::addWaypoints(vector<int>& path, list<CVector>& waypoints)
{
	for (int i : path)
		waypoints.push_back(m_graph[i].pos);
}