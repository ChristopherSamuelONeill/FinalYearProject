
#ifndef PAVEMENT_H
#define PAVEMENT_H

#include <SFML\Graphics.hpp>
#include <iostream>
#include "Pathfinding.h"


using namespace std;
using namespace sf;

class Pavement : public Drawable
{
public:
	Pavement(); // \brief Default constructor of Pavement object

			// \brief Overlaoded constructor of Pavement object
			// \param Vector 2f Position , position of the Pavement 
			// \param Vector 2f Size , size of the Pavement 
			// \param Float Rotation , rotation of the Pavement 
			// \param Texture texture , texture of the Pavement 
	Pavement(Vector2f Position, Vector2f Size, float Rotation, Texture texture);

	// \brief Drawbale function to draw the Pavement
	void draw(RenderTarget& target, RenderStates states) const;

	// \brief Update function ,
	void update();


	//setters
	// \brief void sets the type of Pavement
	// \param Pathfinding pathData , pointer to the path finding data
	void passPathfinding(Pathfinding &pathData);

	// \brief void sets the type of Pavement
	// \param String type , the type of Pavement e.g "T - Junction"
	void setType(string type);

	//getters 

	// \brief Vector 2f Returns the position of the Pavement
	Vector2f getPosition();

	// \brief String Returns the type of the Pavement
	string getType();


	// \brief Float Returns the roation of the Pavement
	float getRotation();

	// \brief Vector 2f Returns the size of the Pavement
	Vector2f getSize();

	// \brief Vector 2f Returns the rectangle for the Pavement
	RectangleShape getCollisionBox();

private:

	//position data
	Vector2f m_sfPosition; // \brief Position of the Pavement
	Vector2f m_sfSize; // \brief Size of the Pavement
	float m_fRotation; // \brief Rotation of the Pavement in degrees

	string m_sType; // \brief Name of the raod type e.g "T - Junction" used for texturing and others

					//drawbale data
	Texture m_sfTexture; // \brief Texture of the Pavement
	RectangleShape m_sfPavementRect; // \brief Rectangle of the Pavement;
	Sprite m_sfPavementSprite;


};
#endif