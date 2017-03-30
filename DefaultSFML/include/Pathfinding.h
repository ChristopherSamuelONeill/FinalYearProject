#ifndef PATHFINDING_H
#define PATHFINDING_H

#include <iostream>
#include <vector>

#include "Node.h"

using namespace std;

class Pathfinding
{

public:

	// \brief Default Constructor for Pathfinding class
	Pathfinding();


	// \brief Overloaded Function to add a new node to the pathfinding class
	// \param open   , bool true for open false for closed
	// \param hValue , float Huesristic value of the node
	// \param gValue , float movement cost of the node
	// \param index , int the node number in the list
	void addNode(bool open, float hValue, float gValue, int index);

	// \brief Function to clear all nodes
	void clearNodes();

	
	//for the cars traverling on the left side of the road
	vector<Node> *m_openList; // \brief list of nodes available for checking
	vector<Node> *m_closedList;  // \brief list of nodes NOT to be checked

};


#endif // !PATHFINDING_H