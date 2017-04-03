#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <SFML\Graphics.hpp>
#include <vector>
#include <queue>

#include "Pathfinding.h"

using namespace std;
using namespace sf;

class Controller
{

public:
	void receiveNodeData(Pathfinding *nodeData);
	queue<Vector2f> m_path; //!< Queue of positions forming a route

protected:

	Pathfinding *m_Pathfinding; // \brief Pointer to Path data
	pair< Node*, Vector2f> m_TargetNode; // \brief node of the destination
	pair< Node*, Vector2f> m_StartNode; // \brief node of the destination
	Vector2f m_sfGoal;// \brief XY of the destination
	Vector2f m_sfStart;// \brief XY of the start
	Vector2f m_sfPosition; // \brief X Y position of car
	
	int plz;
	int secPlz;

	int m_iPreviousNode;// \brief the previous node index parent
	int m_iCurrentNode;

	void generatePath();

private:
	
	pair< Node*, Vector2f> getNode(Vector2f pos); // \brief Retunrs the node at a given pos
	pair< Node*, Vector2f> getNodeFromIndex(int index); // \brief Retunrs the node from a given index
	bool nodeInList(pair< Node*, Vector2f> node1, vector<pair< Node*, Vector2f>> list);  // \brief Retunrs true if the node is i nthe list
	
	float getManhattanDistance(pair< Node*, Vector2f> node1, pair< Node*, Vector2f> node2); // \brief Retunrs X and Y combined dist (path)
	float findGValue(pair< Node*, Vector2f> node1, pair< Node*, Vector2f> node2); // \brief G values of PAth
	
	vector<pair< Node*, Vector2f>> Controller::adjacentNodes(pair< Node*, Vector2f> currentNode); // \brief Finds the surrounding 8 nodes (only returns valid ones)

	void QuePath(pair< Node*, Vector2f> node);



};


#endif // !CONTROLLER_H