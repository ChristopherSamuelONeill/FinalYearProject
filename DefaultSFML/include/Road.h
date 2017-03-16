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

private:
	
	//position data
	Vector2f m_sfPosition; // \breif Position of the road
	Vector2f m_sfSize; // \breif Size of the road
	float m_fRotation; // \breif Rotation of the road in degrees 

	//drawbale data
	Texture m_sfTexture; // \breif Texture of the road
	RectangleShape m_sfRoadRect; // \breif Rectangle of the road;
	Sprite m_sfRoadSprite;


};
#endif