#ifndef COLLISIONDETECTION_H
#define COLLISIONDETECTION_H

#include <SFML\Graphics.hpp>

using namespace sf;

class CollisionDetection
{
public:
	bool Colliding(RectangleShape A, RectangleShape B) const;

};
#endif