#include "Pathfinding.h"

Pathfinding::Pathfinding()
{
}

void Pathfinding::addCarNode( float hValue, float gValue, int index, Vector2f pos, bool accessable)
{
	pair< Node*, Vector2f> tempNode;
	tempNode.first = new Node(hValue, gValue, index, accessable);
	tempNode.second = pos;
	m_carNodes.push_back(tempNode);
}

void Pathfinding::addPedNode(float hValue, float gValue, int index, Vector2f pos, bool accessable)
{
	pair< Node*, Vector2f> tempNode;
	tempNode.first = new Node(hValue, gValue, index, accessable);
	tempNode.second = pos;
	m_pedNodes.push_back(tempNode);
}


void Pathfinding::clearNodes()
{
	m_carOpenNodes.clear();
	m_carClosedNodes.clear();
	for (int i = 0; i < m_carNodes.size(); i++)
	{
		m_carNodes[i].first->ParticalReset();
	}
	
}
