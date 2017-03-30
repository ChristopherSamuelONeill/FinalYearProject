#include "Node.h"

Node::Node()
{
}

Node::Node(float hValue, float gValue, int index)
{
	m_iIndex = index;
	m_fHValue = hValue;
	m_fGValue = gValue;
	m_fFValue = m_fHValue + m_fGValue;
}
