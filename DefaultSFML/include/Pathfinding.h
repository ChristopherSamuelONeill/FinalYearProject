#ifndef PATHFINDING_H
#define PATHFINDING_H

#include <iostream>
#include <SFML\Graphics.hpp>
#include <vector>

#include "Node.h"

using namespace std;
using namespace sf;

class Pathfinding
{

public:

	// \brief Default Constructor for Pathfinding class
	Pathfinding();


	// \brief Overloaded Function to add a new node to the pathfinding class
	// \param hValue , float Huesristic value of the node
	// \param gValue , float movement cost of the node
	// \param index , int the node number in the list
	void addNode( float hValue, float gValue, int index, Vector2f pos);

	// \brief Function to clear all nodes
	void clearNodes();

	

	vector<pair< Node*, Vector2f>> m_nodes; // \brief list of ALL nodes
	vector<pair< Node*, Vector2f>> m_openList; // \brief list of nodes available for checking
	vector<pair< Node*, Vector2f>> m_closedList;// \brief list of nodes NOT to be checked
	

};


#endif // !PATHFINDING_H