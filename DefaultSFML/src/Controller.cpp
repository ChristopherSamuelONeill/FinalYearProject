#include "Controller.h"

void Controller::generatePath()
{

	//find end node
	m_TargetNode = getNode(m_sfGoal);

	

	// Add Node at current location to closed list
	if (getNode(m_sfPosition).first != NULL)
	{

		// Add Node at your current location to closed list
		m_Pathfinding->m_carClosedNodes.push_back(getNode(m_sfStart));
		// Resets the current Node
		 m_Pathfinding->m_carClosedNodes.back().first->ResetNode();
		 m_StartNode = m_Pathfinding->m_carClosedNodes.back();
	}
	else
	{
		cout << "Error NULL node" << endl;
		return;
	}

	//calculate the path
	bool bPathFound = false; // was apath found

	while (!bPathFound)
	{
		//the current node been tested
		pair< Node*, Vector2f> CurrentNode = m_Pathfinding->m_carClosedNodes.back();

		CurrentNode.first->m_fHValue = getManhattanDistance(CurrentNode, m_TargetNode);

		if (CurrentNode == m_TargetNode)
		{
			bPathFound = true;
			return;
		}

		//find adjacent nodes
		vector<pair< Node*, Vector2f>> AdjacentNodes = adjacentNodes(CurrentNode);

		//cout << AdjacentNodes[0].first->m_bAccessable << endl;
		int lol = AdjacentNodes.size();

		//for each adjacent node
		for (int i = 0; i < AdjacentNodes.size();i++)
		{

			if (CurrentNode == AdjacentNodes[i])
			{
				cout << "DICK HEAD" << endl;
			}

			// If adjNode is inaccessible
			if (AdjacentNodes[i].first->m_bAccessable == false ) ; // ignore
			else if (AdjacentNodes[i] == m_TargetNode)
			{
				//reset the node
				AdjacentNodes[i].first->ResetNode();

				//set the parent node
				AdjacentNodes[i].first->parentNode = &CurrentNode;

				//set the H value
				AdjacentNodes[i].first->m_fHValue = getManhattanDistance(AdjacentNodes[i],m_TargetNode);

				//calculate the G value
				AdjacentNodes[i].first->m_fGValue = findGValue(CurrentNode, AdjacentNodes[i]);

				//calculate the F value
				AdjacentNodes[i].first->m_fFValue = AdjacentNodes[i].first->m_fGValue + AdjacentNodes[i].first->m_fHValue;

				

				//queue route
				QuePath(AdjacentNodes[i]);
				bPathFound = true;
				return;

			}
			else if(nodeInList(AdjacentNodes[i],m_Pathfinding->m_carOpenNodes))
			{
				//if node is in open nodes

				// Distance from the current Node and open Node
				Vector2f fDistToNode = Vector2f(CurrentNode.second.x - AdjacentNodes[i].second.x, CurrentNode.second.y - AdjacentNodes[i].second.y);

				float mag = sqrt((fDistToNode.x * fDistToNode.x) + (fDistToNode.y * fDistToNode.y));

				if (CurrentNode.first->m_fGValue + mag < AdjacentNodes[i].first->m_fGValue)
				{
					AdjacentNodes[i].first->parentNode = &CurrentNode;
				}

			}
			else if (nodeInList(AdjacentNodes[i], m_Pathfinding->m_carClosedNodes));//ignore
			else
			{
				//(AdjacentNodes[i] is accessable , not the dest , is not yet on the open or closed list
				//reset the node
				AdjacentNodes[i].first->ResetNode();

				//set the parent node
				AdjacentNodes[i].first->parentNode = &CurrentNode;

				//set the H value
				AdjacentNodes[i].first->m_fHValue = getManhattanDistance(AdjacentNodes[i], m_TargetNode);

				//calculate the G value
				AdjacentNodes[i].first->m_fGValue = findGValue(CurrentNode, AdjacentNodes[i]);

				//calculate the F value
				AdjacentNodes[i].first->m_fFValue = AdjacentNodes[i].first->m_fGValue + AdjacentNodes[i].first->m_fHValue;

				//add to open list
				m_Pathfinding->m_carOpenNodes.push_back(AdjacentNodes[i]);
				

			}

		}
		

		//find next node
	
		if (!m_Pathfinding->m_carOpenNodes.empty())
		{
			pair< Node*, Vector2f> smallestFValueNode = m_Pathfinding->m_carOpenNodes.back(); // node with the lowest cost

			for (int i = 0; i < m_Pathfinding->m_carOpenNodes.size(); i++)
			{
				if (m_Pathfinding->m_carOpenNodes[i].first->m_fFValue < smallestFValueNode.first->m_fFValue)
				{
					smallestFValueNode.swap(m_Pathfinding->m_carOpenNodes[i]);
				}
				else if (m_Pathfinding->m_carOpenNodes[i].first->m_fFValue == smallestFValueNode.first->m_fFValue)
				{
					// the node with lower H is set
					if (m_Pathfinding->m_carOpenNodes[i].first->m_fHValue < smallestFValueNode.first->m_fHValue)
					{
						smallestFValueNode.swap(m_Pathfinding->m_carOpenNodes[i]);
					}

				}
				else
				{
					// do nothing
				}
			}

			//add the lowest f vlaue to closed list
			m_Pathfinding->m_carClosedNodes.push_back(smallestFValueNode);

			//remove the node from open list
			vector<pair< Node*, Vector2f>> newOpenNodes;
			for (int i = 0; i < m_Pathfinding->m_carOpenNodes.size(); i++)
			{
				if (m_Pathfinding->m_carOpenNodes[i] != smallestFValueNode)
				{
					newOpenNodes.push_back(m_Pathfinding->m_carOpenNodes[i]);

				}
			}
			m_Pathfinding->m_carOpenNodes.swap(newOpenNodes);

		}
		else
		{
			cout << "failed to find a path" << endl;
			return;
		}

		

	}

}

pair<Node*, Vector2f> Controller::getNode(Vector2f pos)
{

	// Find the Desired mode
	RectangleShape goalRect(Vector2f(100, 100));
	RectangleShape nodeRect(Vector2f(100, 100));

	for (int i = 0; i < m_Pathfinding->m_carNodes.size(); i++)
	{
		//position rect at goal
		goalRect.setPosition(pos);
		//check rect of node
		nodeRect.setPosition(m_Pathfinding->m_carNodes[i].second);

		FloatRect Goal = goalRect.getGlobalBounds();
		FloatRect node = nodeRect.getGlobalBounds();

		//if it instersects set the goal node
		if (Goal.intersects(node))
		{
			return m_Pathfinding->m_carNodes[i];
		}

	}

	cout << "NO node was found !!" << endl;
	return pair<Node*, Vector2f>();
}

pair<Node*, Vector2f> Controller::getNodeFromIndex(int index)
{
	if (!m_Pathfinding->m_carNodes.empty())
	{
		// If index is within available range
		if ((index >= 0) && (index < m_Pathfinding->m_carNodes.size()))
		{
			// Returns Node at index
			return m_Pathfinding->m_carNodes[index];
		}
	}
	
	return pair<Node*, Vector2f>();
}
bool Controller::nodeInList(pair<Node*, Vector2f> node1, vector<pair<Node*, Vector2f>> list)
{

	if ((find(list.begin(), list.end(), node1)) != list.end())return true;
	else return false;
}
float Controller::getManhattanDistance(pair<Node*, Vector2f> node1, pair<Node*, Vector2f> node2)
{
	// Number of Nodes in x
	float fXDist = (node2.second.x - node1.second.x) / 100;

	// Number of Nodes in x
	float fYDist = (node2.second.y - node1.second.y) / 100;
	// Added x and y dist
	float fDistance = abs(fXDist) + abs(fYDist);

	// Returns the combined distances
	return fDistance;
}

float Controller::findGValue(pair<Node*, Vector2f> node1, pair<Node*, Vector2f> node2)
{
	// Distance from the current Node and open Node
	Vector2f fDistToNode = Vector2f(node2.second.x - node1.second.x, node2.second.y - node1.second.y);

	float mag = sqrt((fDistToNode.x * fDistToNode.x) + (fDistToNode.y * fDistToNode.y));

	// Returns resultant G value (distance to next Node plus current Node's G)
	return mag + node1.first->m_fGValue;
}

vector<pair<Node*, Vector2f>> Controller::adjacentNodes(pair<Node*, Vector2f> currentNode)
{
	//to be retunrned
	vector<pair< Node*, Vector2f>> AdjacentNodes;

	if (currentNode.first != NULL)
	{
		// a temporary node
		pair< Node*, Vector2f> tempNode;

		unsigned int uiIndex;

		for (int i = 0; i < 8; i++)
		{
			switch (i)
			{
			case 1:
			{
				//top left
				uiIndex = (currentNode.first->m_iIndex - 1) - m_Pathfinding->m_uiNodeX;
				tempNode = getNodeFromIndex(uiIndex);

				if (tempNode.first != NULL)
				{
					uiIndex = (currentNode.first->m_iIndex - 1);
					pair< Node*, Vector2f> node1 = getNodeFromIndex(uiIndex);
					uiIndex = (currentNode.first->m_iIndex) - m_Pathfinding->m_uiNodeX;
					pair< Node*, Vector2f> node2 = getNodeFromIndex(uiIndex);

					// If checkNode1 Node exists and is not accessible
					if (node1.first != nullptr && node1.first->m_bAccessable == false) {}

					// Else If checkNode2 Node exists and is not accessible
					else if (node2.first != nullptr && node2.first->m_bAccessable == false) {}

					// Both checkNodes exist and are accessible
					else
					{
						// Adds adjacent Node to vector
						AdjacentNodes.push_back(tempNode);
					}
				}
				break;

			}
			case 2:
			{
				//top middle
				uiIndex = currentNode.first->m_iIndex - m_Pathfinding->m_uiNodeX;
				tempNode = getNodeFromIndex(uiIndex);

				if (tempNode.first != NULL)
				{

					// Adds adjacent Node to vector
					AdjacentNodes.push_back(tempNode);
				}
				break;
			}
			case 3:
			{
				//top right
				uiIndex = (currentNode.first->m_iIndex + 1) - m_Pathfinding->m_uiNodeX;
				tempNode = getNodeFromIndex(uiIndex);

				if (tempNode.first != NULL)
				{
					uiIndex = currentNode.first->m_iIndex - m_Pathfinding->m_uiNodeX;
					pair< Node*, Vector2f> node1 = getNodeFromIndex(uiIndex);
					uiIndex = currentNode.first->m_iIndex + 1;
					pair< Node*, Vector2f> node2 = getNodeFromIndex(uiIndex);

					// If checkNode1 Node exists and is not accessible
					if (node1.first != nullptr && node1.first->m_bAccessable == false) {}

					// Else If checkNode2 Node exists and is not accessible
					else if (node2.first != nullptr && node2.first->m_bAccessable == false) {}

					// Both checkNodes exist and are accessible
					else
					{
						// Adds adjacent Node to vector
						AdjacentNodes.push_back(tempNode);
					}
				}
				break;
			}
			case 4:
			{
				//middle right
				uiIndex = currentNode.first->m_iIndex + 1;
				tempNode = getNodeFromIndex(uiIndex);

				if (tempNode.first != NULL)
				{
					// Adds adjacent Node to vector
					AdjacentNodes.push_back(tempNode);
				}
				break;
			}
			case 5:
			{
				//bottom right
				uiIndex = (currentNode.first->m_iIndex + 1) + m_Pathfinding->m_uiNodeX;
				tempNode = getNodeFromIndex(uiIndex);

				if (tempNode.first != NULL)
				{
					uiIndex = currentNode.first->m_iIndex + 1;
					pair< Node*, Vector2f> node1 = getNodeFromIndex(uiIndex);
					uiIndex = currentNode.first->m_iIndex + m_Pathfinding->m_uiNodeX;
					pair< Node*, Vector2f> node2 = getNodeFromIndex(uiIndex);

					// If checkNode1 Node exists and is not accessible
					if (node1.first != nullptr && node1.first->m_bAccessable == false) {}

					// Else If checkNode2 Node exists and is not accessible
					else if (node2.first != nullptr && node2.first->m_bAccessable == false) {}

					// Both checkNodes exist and are accessible
					else
					{
						// Adds adjacent Node to vector
						AdjacentNodes.push_back(tempNode);
					}
				}
				break;
			}
			case 6:
			{
				//btttom middle
				uiIndex = currentNode.first->m_iIndex + m_Pathfinding->m_uiNodeX;
				tempNode = getNodeFromIndex(uiIndex);

				if (tempNode.first != NULL)
				{
					// Adds adjacent Node to vector
					AdjacentNodes.push_back(tempNode);
				}
				break;
			}
			case 7:
			{
				//bottom left
				uiIndex = (currentNode.first->m_iIndex - 1) + m_Pathfinding->m_uiNodeX;
				tempNode = getNodeFromIndex(uiIndex);

				if (tempNode.first != NULL)
				{
					uiIndex = currentNode.first->m_iIndex + m_Pathfinding->m_uiNodeX;
					pair< Node*, Vector2f> node1 = getNodeFromIndex(uiIndex);
					uiIndex = currentNode.first->m_iIndex - 1;
					pair< Node*, Vector2f> node2 = getNodeFromIndex(uiIndex);

					// If checkNode1 Node exists and is not accessible
					if (node1.first != nullptr && node1.first->m_bAccessable == false) {}

					// Else If checkNode2 Node exists and is not accessible
					else if (node2.first != nullptr && node2.first->m_bAccessable == false) {}

					// Both checkNodes exist and are accessible
					else
					{
						// Adds adjacent Node to vector
						AdjacentNodes.push_back(tempNode);
					}
				}
				break;
			}
			case 8:
			{
				//btttom middle
				uiIndex = currentNode.first->m_iIndex - 1;
				tempNode = getNodeFromIndex(uiIndex);

				if (tempNode.first != NULL)
				{
					// Adds adjacent Node to vector
					AdjacentNodes.push_back(tempNode);
				}

			}
			break;
			}
		}

	}
	
	

	return AdjacentNodes;
}

void Controller::QuePath(pair<Node*, Vector2f> node)
{
	// Vector for stack of Nodes to be used in path
	vector<pair<Node*, Vector2f>> pNodes;



	// Pushes destination Node onto vector
	pNodes.push_back(node);

	m_TargetNode;
	m_StartNode;

	pair< Node*, Vector2f> test =  m_Pathfinding->m_carClosedNodes[0];

	while (node.first->parentNode->first != test.first)
	{
		// Make the Node it's Parent
		node = *node.first->parentNode;
		// Push the parent onto the path of Nodes
		pNodes.push_back(node);


	}

	while (!pNodes.empty())
	{
		// Pushes the position of node onto path
		m_path.push(pNodes.back().second);
		
		// Pops Node off Vector
		pNodes.pop_back();
	}
	


}

void Controller::receiveNodeData(Pathfinding * nodeData)
{
	m_Pathfinding = nodeData;
}
