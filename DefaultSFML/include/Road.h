#ifndef ROAD_H
#define ROAD_H

#include <SFML\Graphics.hpp>
#include <iostream>


using namespace std;
using namespace sf;

class Road : public Drawable
{
public:
	Road(); // \breif Default constructor of road object

	// \breif Overlaoded constructor of road object
	// \param Vector 2f Position , position of the road 
	// \param Vector 2f Size , size of the road 
	// \param Float Rotation , rotation of the road 
	// \param Texture texture , texture of the road 
	Road(Vector2f Position, Vector2f Size, float Rotation, Texture texture); 

	// \breif Drawbale function to draw the road
	void draw(RenderTarget& target, RenderStates states) const;

	// \breif Update function ,
	void update();


	//setters

	// \breif void sets the type of road
	// \param String type , the type of road e.g "T - Junction"
	void setType(string type);	

	//getters 

	// \breif Vector 2f Returns the position of the road
	Vector2f getPosition();

	// \breif String Returns the type of the road
	String getType();


	// \breif Float Returns the roation of the road
	float getRotation();

	// \breif Vector 2f Returns the size of the road
	Vector2f getSize();

	// \breif Vector 2f Returns the rectangle for the road
	RectangleShape getCollisionBox();

private:
	
	//position data
	Vector2f m_sfPosition; // \breif Position of the road
	Vector2f m_sfSize; // \breif Size of the road
	float m_fRotation; // \breif Rotation of the road in degrees

	string m_sType; // \breif Name of the raod type e.g "T - Junction" used for texturing and others

	//drawbale data
	Texture m_sfTexture; // \breif Texture of the road
	RectangleShape m_sfRoadRect; // \breif Rectangle of the road;
	Sprite m_sfRoadSprite;


};
#endif