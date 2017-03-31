#ifndef NODE_H
#define NODE_H



#include <iostream>
class Node
{

public:

	// \brief Default Constructor for node class
	Node();

	// \brief Overloaded Constructor for node class
	// \param hValue , float Huesristic value of the node
	// \param gValue , float movement cost of the node
	// \param index , int the node number in the list
	// \param Accessable , bool wheather the node is accessible or not
	Node(float hValue, float gValue, int index,bool Accessable);


	int m_iIndex;	 // \brief the node number in the list
	float m_fHValue; // \brief Huesristic value of the node
	float m_fGValue; // \brief movement cost of the node
	float m_fFValue = m_fHValue + m_fGValue; // \brief Combined value of the node
	bool m_bAccessable; // \brief wheather the node is accessible or not

	Node *parentNode; // \brief A pointer to the parent node


};


#endif // !NODE_H