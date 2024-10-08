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
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++) 
	{
		m_graph.push_back(NODE{ CVector(32.f + j * 64.f, 32.f + i * 64.f) });
	}
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
	{
		NODE& current_node = m_graph[i * 10 + j];
		if (i != 0 && j != 0 && i != 9 && j != 9) {
			current_node.conlist.push_back(CONNECTION{ (i + 1) * 10 + (j - 1), 1 });
			current_node.conlist.push_back(CONNECTION{ (i + 1) * 10 + j, 1 });
			current_node.conlist.push_back(CONNECTION{ (i + 1) * 10 + (j + 1), 1 });
			current_node.conlist.push_back(CONNECTION{ i * 10 + (j - 1), 1 });
			current_node.conlist.push_back(CONNECTION{ i * 10 + (j + 1), 1 });
			current_node.conlist.push_back(CONNECTION{ (i - 1) * 10 + (j - 1), 1 });
			current_node.conlist.push_back(CONNECTION{ (i - 1) * 10 + j, 1 });
			current_node.conlist.push_back(CONNECTION{ (i - 1) * 10 + (j + 1), 1 });
		} else if (i == 0 && j == 0) {
			current_node.conlist.push_back(CONNECTION{ (i + 1) * 10 + j, 1 });
			current_node.conlist.push_back(CONNECTION{ i * 10 + (j + 1), 1 });
			current_node.conlist.push_back(CONNECTION{ (i + 1) * 10 + (j + 1), 1 });
		} else if (i == 0 && j == 9) {
			current_node.conlist.push_back(CONNECTION{ (i + 1) * 10 + j, 1 });
			current_node.conlist.push_back(CONNECTION{ i * 10 + (j - 1), 1 });
			current_node.conlist.push_back(CONNECTION{ (i + 1) * 10 + (j - 1), 1 });
		} else if (i == 9 && j == 0) {
			current_node.conlist.push_back(CONNECTION{ (i - 1) * 10 + j, 1 });
			current_node.conlist.push_back(CONNECTION{ i * 10 + (j + 1), 1 });
			current_node.conlist.push_back(CONNECTION{ (i - 1) * 10 + (j + 1), 1 });
		} else if (i == 9 && j == 9) {
			current_node.conlist.push_back(CONNECTION{ (i) * 10 + (j - 1), 1 });
			current_node.conlist.push_back(CONNECTION{ (i - 1) * 10 + j, 1 });
			current_node.conlist.push_back(CONNECTION{ (i - 1) * 10 + (j - 1), 1 });
		} else if (i == 0) {
			current_node.conlist.push_back(CONNECTION{ (i + 1) * 10 + (j - 1), 1 });
			current_node.conlist.push_back(CONNECTION{ (i + 1) * 10 + j, 1 });
			current_node.conlist.push_back(CONNECTION{ (i + 1) * 10 + (j + 1), 1 });
			current_node.conlist.push_back(CONNECTION{ i * 10 + (j - 1), 1 });
			current_node.conlist.push_back(CONNECTION{ i * 10 + (j + 1), 1 });
		} else if (j == 0) {
			current_node.conlist.push_back(CONNECTION{ (i + 1) * 10 + j, 1 });
			current_node.conlist.push_back(CONNECTION{ (i + 1) * 10 + (j + 1), 1 });
			current_node.conlist.push_back(CONNECTION{ i * 10 + (j + 1), 1 });
			current_node.conlist.push_back(CONNECTION{ (i - 1) * 10 + j, 1 });
			current_node.conlist.push_back(CONNECTION{ (i - 1) * 10 + (j + 1), 1 });
		} else if (i == 9) {
			current_node.conlist.push_back(CONNECTION{ i * 10 + (j - 1), 1 });
			current_node.conlist.push_back(CONNECTION{ i * 10 + (j + 1), 1 });
			current_node.conlist.push_back(CONNECTION{ (i - 1) * 10 + (j - 1), 1 });
			current_node.conlist.push_back(CONNECTION{ (i - 1) * 10 + j, 1 });
			current_node.conlist.push_back(CONNECTION{ (i - 1) * 10 + (j + 1), 1 });
		} else if (j == 9) {
			current_node.conlist.push_back(CONNECTION{ (i + 1) * 10 + (j - 1), 1 });
			current_node.conlist.push_back(CONNECTION{ (i + 1) * 10 + j, 1 });
			current_node.conlist.push_back(CONNECTION{ i * 10 + (j - 1), 1 });
			current_node.conlist.push_back(CONNECTION{ (i - 1) * 10 + (j - 1), 1 });
			current_node.conlist.push_back(CONNECTION{ (i - 1) * 10 + j, 1 });
		}
	}
}

void Pathfinding::draw(CGraphics* g) {
	for (int i = 0; i < 100; i++) {

		// Draw nodes
		g->FillCircle(CVector(m_graph.at(i).pos.GetX(), m_graph.at(i).pos.GetY()), 5, CColor::Red());

		// Draw connections (some twice but nvm)
		for (CONNECTION& connection : m_graph.at(i).conlist) {
			CVector target = m_graph.at(connection.nEnd).pos;
			g->DrawLine(CVector(m_graph.at(i).pos.GetX(), m_graph.at(i).pos.GetY()), CVector(target.GetX(),target.GetY()), CColor::Red());
		}
	}
}