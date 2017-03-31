#include "Pathfinding.h"

Pathfinding::Pathfinding()
{
}

void Pathfinding::addNode( float hValue, float gValue, int index, Vector2f pos)
{
	pair< Node*, Vector2f> tempNode;
	tempNode.first = new Node(hValue, gValue, index);
	tempNode.second = pos;
	m_nodes.push_back(tempNode);
}

void Pathfinding::clearNodes()
{
	m_openList.clear();
	m_closedList.clear();
	m_nodes.clear();
}
