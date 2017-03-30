#include "Pathfinding.h"

Pathfinding::Pathfinding()
{
	clearNodes();
}

void Pathfinding::addNode(bool open, float hValue, float gValue, int index)
{
	if (open)
	{
		m_openList->push_back(Node(hValue, gValue, index));
	}
	else
	{
		m_closedList->push_back(Node(hValue, gValue, index));
	}
}

void Pathfinding::clearNodes()
{
	delete(m_openList);
	m_openList = NULL;

	delete(m_closedList);
	m_closedList = NULL;

}
