#include "Pathfinding.h"

Pathfinding::Pathfinding()
{
}

void Pathfinding::addNode( float hValue, float gValue, int index, Vector2f pos, bool accessable)
{
	pair< Node*, Vector2f> tempNode;
	tempNode.first = new Node(hValue, gValue, index, accessable);
	tempNode.second = pos;
	m_carNodes.push_back(tempNode);
}

void Pathfinding::clearNodes()
{
	m_carOpenNodes.clear();
	m_carClosedNodes.clear();
	m_carNodes.clear();
	m_uiNodeX = 0;
	m_uiNodeY = 0;
}
