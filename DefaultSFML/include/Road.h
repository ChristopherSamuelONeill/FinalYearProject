#ifndef ROAD_H
#define ROAD_H

#include <SFML\Graphics.hpp>
#include <iostream>
#include "Pathfinding.h"


using namespace std;
using namespace sf;

class Road : public Drawable
{
public:
	Road(); // \brief Default constructor of road object

	// \brief Overlaoded constructor of road object
	// \param Vector 2f Position , position of the road 
	// \param Vector 2f Size , size of the road 
	// \param Float Rotation , rotation of the road 
	// \param Texture texture , texture of the road 
	Road(Vector2f Position, Vector2f Size, float Rotation, Texture texture); 

	// \brief Drawbale function to draw the road
	void draw(RenderTarget& target, RenderStates states) const;

	// \brief Update function ,
	void update();


	//setters
	// \brief void sets the type of road
	// \param Pathfinding pathData , pointer to the path finding data
	void passPathfinding(Pathfinding &pathData);

	// \brief void sets the type of road
	// \param String type , the type of road e.g "T - Junction"
	void setType(string type);	

	//getters 

	// \brief Vector 2f Returns the position of the road
	Vector2f getPosition();

	// \brief String Returns the type of the road
	string getType();


	// \brief Float Returns the roation of the road
	float getRotation();

	// \brief Vector 2f Returns the size of the road
	Vector2f getSize();

	// \brief Vector 2f Returns the rectangle for the road
	RectangleShape getCollisionBox();

private:
	
	//position data
	Vector2f m_sfPosition; // \brief Position of the road
	Vector2f m_sfSize; // \brief Size of the road
	float m_fRotation; // \brief Rotation of the road in degrees

	string m_sType; // \brief Name of the raod type e.g "T - Junction" used for texturing and others

	//drawbale data
	Texture m_sfTexture; // \brief Texture of the road
	RectangleShape m_sfRoadRect; // \brief Rectangle of the road;
	Sprite m_sfRoadSprite;


};
#endif