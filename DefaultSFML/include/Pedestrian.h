#ifndef PEDESTRIAN_H
#define PEDESTRIAN_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Controller.h"

using namespace std;
using namespace sf;

class Pedestrian : public Drawable, public Controller
{
public:

	////////////////////////////////////////////////////////////
	/// \brief Default Constructor
	/// Creates an empty Pedestrian
	////////////////////////////////////////////////////////////
	Pedestrian();

	////////////////////////////////////////////////////////////
	/// \brief Overloaded Constructor
	///
	/// Creates the Pedestrian with its parameteres
	///
	/// \param Position Vector2f Position of Pedestrian
	/// \param Goal Vector2f Poistion the Pedestrian wants to reach
	/// \param size sVector2f size of the button
	/// \param Textures String Locations of the textures
	////////////////////////////////////////////////////////////
	Pedestrian(Vector2f Position, Vector2f Goal, Vector2f Size, Texture texture);
	

};
#endif // !PEDESTRIAN_H