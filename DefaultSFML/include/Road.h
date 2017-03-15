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


private:
	
	Vector2f m_sfPostion; // \breif Positio of the road

};
#endif